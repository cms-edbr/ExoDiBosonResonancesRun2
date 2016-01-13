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
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "ExoDiBosonResonances/EDBRLeptons/interface/TrackerMuonSelector.h"

#include "TTree.h"
#include "TEfficiency.h"

class EDBRGenStudies : public edm::EDAnalyzer {
   public:
      explicit EDBRGenStudies(const edm::ParameterSet&);
      ~EDBRGenStudies();

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      edm::EDGetTokenT<reco::CandidateCollection>     genZToken;
      edm::EDGetTokenT<reco::VertexCollection>      vertexToken;
      edm::EDGetTokenT<reco::CompositeCandidateView> ZcandToken;

      TTree* t; 
      double genPt1;
      double genPt2;
      double genEta1;
      double genEta2;
      int    loose1;
      int    loose2;
      int    medium1;
      int    medium2;
      int    highPt1;
      int    highPt2;
      int    tracker1;
      int    tracker2;
      double dRGenGen;
      double dRGenRec1;
      double dRGenRec2;
};


EDBRGenStudies::EDBRGenStudies(const edm::ParameterSet& iConfig)
{
   genZToken   = consumes<reco::CandidateCollection>(    edm::InputTag("leptonicDecay") );
   vertexToken = consumes<reco::VertexCollection>(       edm::InputTag("goodVertices" ) );
   ZcandToken  = consumes<reco::CompositeCandidateView>( edm::InputTag("Ztomumu"      ) );

   edm::Service<TFileService> fs;
   t = fs->make<TTree>("t","basic kinematic variables");
   t->Branch("genPt1",    &genPt1,    "genPt1/D");
   t->Branch("genPt2",    &genPt2,    "genPt2/D");
   t->Branch("genEta1",   &genEta1,   "genEta1/D");
   t->Branch("genEta2",   &genEta2,   "genEta2/D");
   t->Branch("loose1",    &loose1,    "loose1/I");
   t->Branch("loose2",    &loose2,    "loose2/I");
   t->Branch("medium1",   &medium1,   "medium1/I");
   t->Branch("medium2",   &medium2,   "medium2/I");
   t->Branch("highPt1",   &highPt1,   "highPt1/I");
   t->Branch("highPt2",   &highPt2,   "highPt2/I");
   t->Branch("tracker1",  &tracker1,  "tracker1/I");
   t->Branch("tracker2",  &tracker2,  "tracker2/I");
   t->Branch("dRGenGen",  &dRGenGen,  "dRGenGen/D");
   t->Branch("dRGenRec1", &dRGenRec1, "dRGenRec1/D");
   t->Branch("dRGenRec2", &dRGenRec2, "dRGenRec2/D");
}

EDBRGenStudies::~EDBRGenStudies()
{
}


void
EDBRGenStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<reco::CandidateCollection> genZ;
   iEvent.getByToken(genZToken, genZ);
   const reco::Candidate& G    = (*genZ)[0];
   const reco::Candidate *gen1 = (reco::Candidate*)G.daughter(0);
   const reco::Candidate *gen2 = (reco::Candidate*)G.daughter(1);
   math::XYZTLorentzVector v1  = gen1->pt() > gen2->pt() ? gen1->p4() : gen2->p4();
   math::XYZTLorentzVector v2  = gen1->pt() < gen2->pt() ? gen1->p4() : gen2->p4();
   genPt1                      = v1.pt();
   genPt2                      = v2.pt();
   genEta1                     = v1.eta();
   genEta2                     = v2.eta();
   dRGenGen                    = reco::deltaR( v1, v2 );
   bool acceptance = genPt1 > 20 and fabs(genEta1) < 2.4 and
                     genPt2 > 20 and fabs(genEta2) < 2.4;
   if( !acceptance ) return;

   // handle goodOfflinePrimaryVertex collection
   Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vertexToken, vertices);
   const reco::Vertex& vertex = (*vertices)[0];

   //****************************************************************//
   //                  loop over reco Z candidates                   //
   //****************************************************************//                                             
   Handle<reco::CompositeCandidateView> Zcands ;
   iEvent.getByToken(ZcandToken,        Zcands);
   int mult = Zcands->size();
   for( int i=0; i<mult; i++ ) {
      const reco::Candidate& Z = (*Zcands)[i];
      const reco::Muon *mu1 = (const reco::Muon*)Z.daughter(0);
      const reco::Muon *mu2 = (const reco::Muon*)Z.daughter(1);
      double  dR1 = reco::deltaR( v1, mu1->p4() );
      double  dR2 = reco::deltaR( v2, mu2->p4() );
      bool  match = dR1<0.05 and dR2<0.05;
      if ( !match ) continue;
      loose1      = (int)muon::isLooseMuon(  *mu1        );
      loose2      = (int)muon::isLooseMuon(  *mu2        );
      medium1     = (int)muon::isMediumMuon( *mu1        );  
      medium2     = (int)muon::isMediumMuon( *mu2        );  
      highPt1     = (int)muon::isHighPtMuon( *mu1, vertex);  
      highPt2     = (int)muon::isHighPtMuon( *mu2, vertex);  
      tracker1    = (int)hptm::isTrackerMuon(*mu1, vertex);  
      tracker2    = (int)hptm::isTrackerMuon(*mu2, vertex);  
      dRGenRec1   = dR1; 
      dRGenRec2   = dR2; 
      // fill tree
      t->Fill();
   }
   //****************************************************************//
   //                  End loop over pat::Muons                  //
   //****************************************************************//
}


void EDBRGenStudies::beginJob() { }

void EDBRGenStudies::endJob() { }

DEFINE_FWK_MODULE(EDBRGenStudies);
