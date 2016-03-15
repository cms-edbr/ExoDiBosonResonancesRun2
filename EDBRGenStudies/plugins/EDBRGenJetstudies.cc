// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "TTree.h"

class EDBRGenJetstudies : public edm::EDAnalyzer {
   public:
      explicit EDBRGenJetstudies(const edm::ParameterSet&);
      ~EDBRGenJetstudies();

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      edm::EDGetTokenT<reco::CandidateCollection>           genZToken;
      edm::EDGetTokenT<reco::VertexCollection>            vertexToken;
      edm::EDGetTokenT<pat::JetCollection>              corrJetsToken;
      edm::EDGetTokenT<std::vector<PileupSummaryInfo> >   puInfoToken;

      TTree* t; 
      int    nevent, run, lumi;
      int    njets;
      double et;
      double etres;
      double pt;
      double ptres;
      double eta;
      double mass;
      double massres;
      double soft;
      double pruned;
      double tau21;
      double genEt;
      double genPt;
      double genEta;
      double genMass;
      double dRGenRec;
      int    match;
      int    nVtx;
      double pileupWeight;
      edm::FileInPath puWeights_;
      TFile *f1;
      TH1D *h1;
};


EDBRGenJetstudies::EDBRGenJetstudies(const edm::ParameterSet& iConfig)
{
   vertexToken   = consumes<reco::VertexCollection>(        edm::InputTag("offlineSlimmedPrimaryVertices") );
   genZToken     = consumes<reco::CandidateCollection>(     edm::InputTag("hadronicDecay") );
   corrJetsToken = consumes<pat::JetCollection>(            edm::InputTag("corrJetsProducer:corrJets") );
   puInfoToken   = consumes<std::vector<PileupSummaryInfo>>(edm::InputTag("slimmedAddPileupInfo"));
   puWeights_    = iConfig.getParameter<edm::FileInPath>("puWeights") ;
   edm::Service<TFileService> fs;
   t = fs->make<TTree>("t","basic kinematic variables");
   t->Branch("nevent",       &nevent,              "nevent/I");
   t->Branch("run",          &run,                    "run/I");
   t->Branch("lumi",         &lumi,                  "lumi/I");
   t->Branch("njets",        &njets,                "njets/I");
   t->Branch("et",           &et,                      "et/D");
   t->Branch("etres",        &etres,                "etres/D");
   t->Branch("pt",           &pt,                      "pt/D");
   t->Branch("ptres",        &ptres,                "ptres/D");
   t->Branch("eta",          &eta,                    "eta/D");
   t->Branch("mass",         &mass,                  "mass/D");
   t->Branch("massres",      &massres,            "massres/D");
   t->Branch("soft",         &soft,                  "soft/D");
   t->Branch("pruned",       &pruned,              "pruned/D");
   t->Branch("tau21",        &tau21,                "tau21/D");
   t->Branch("genEt",        &genEt,                "genEt/D");
   t->Branch("genPt",        &genPt,                "genPt/D");
   t->Branch("genEta",       &genEta,              "genEta/D");
   t->Branch("genMass",      &genMass,            "genMass/D");
   t->Branch("dRGenRec",     &dRGenRec,          "dRGenRec/D");
   t->Branch("match",        &match,                "match/I");
   t->Branch("nVtx",         &nVtx,                  "nVtx/I");
   t->Branch("pileupWeight", &pileupWeight,  "pileupWeight/D");
}

EDBRGenJetstudies::~EDBRGenJetstudies(){ }

void
EDBRGenJetstudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   nevent  = iEvent.eventAuxiliary().event();
   run     = iEvent.eventAuxiliary().run();
   lumi    = iEvent.eventAuxiliary().luminosityBlock();

   Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vertexToken, vertices);
   nVtx = vertices->size();

   //****************************************************************//
   //                       GEN Z candidate                          //
   //****************************************************************//                                             
   Handle<reco::CandidateCollection> genZ;
   iEvent.getByToken(genZToken,      genZ);
   const reco::Candidate& G    = (*genZ)[0];
   genEt   = G.et();
   genPt   = G.pt();
   genEta  = G.eta();
   genMass = G.mass();
   bool acceptance = genPt>170. and fabs(genEta)<2.4;
   if( !acceptance ) return;
   //****************************************************************//
   //                       Reco Z candidate                         //
   //****************************************************************//                                             

   Handle<pat::JetCollection>       jets;
   iEvent.getByToken(corrJetsToken, jets);
   njets = jets->size();
   int best=0;
   for(int i=1; i<njets; i++){
      const pat::Jet& j0 = jets->at(best);
      const pat::Jet& j1 = jets->at(i);
      double dR0 = deltaR(G.p4(),j0.p4());
      double dR1 = deltaR(G.p4(),j1.p4());
      best = dR0<dR1 ? best : i;
   }
   const pat::Jet& Z = jets->at(best);
   et         = Z.et();
   pt         = Z.pt();
   eta        = Z.eta();
   mass       = Z.userFloat("ak8PFJetsCHSCorrPrunedMass");
   soft       = Z.userFloat("ak8PFJetsCHSSoftDropMass");
   pruned     = Z.userFloat("ak8PFJetsCHSPrunedMass");
   tau21      = Z.userFloat("NjettinessAK8:tau2")/Z.userFloat("NjettinessAK8:tau1");
   dRGenRec   = deltaR(G.p4(),Z.p4());
   match      = dRGenRec<0.05 ? 1 : 0;
   if( !match ) return;
   // Resolution
   etres      = (genEt-et)/genEt;
   ptres      = (genPt-pt)/genPt;
   massres    = (genMass-mass)/genMass;

   // pileup reweight
   Handle<std::vector< PileupSummaryInfo > >  puInfo;
   iEvent.getByToken(puInfoToken, puInfo);
   std::vector<PileupSummaryInfo>::const_iterator PVI;
   for(PVI = puInfo->begin(); PVI != puInfo->end(); ++PVI) {
        int BX = PVI->getBunchCrossing();
        if( BX == 0 ){
             int  bin     = h1->FindBin(PVI->getTrueNumInteractions());
             pileupWeight = h1->GetBinContent(bin);
             continue;
        }
   }

   // fill tree
   t->Fill();
}

void EDBRGenJetstudies::beginJob() {
   f1 = new TFile( puWeights_.fullPath().c_str() );
   h1 = (TH1D*)f1->Get("pileupWeights");
}

void EDBRGenJetstudies::endJob() { }

DEFINE_FWK_MODULE(EDBRGenJetstudies);
