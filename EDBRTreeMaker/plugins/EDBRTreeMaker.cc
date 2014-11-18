// system include files
#include <iostream>
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "EDBRChannels.h"
#include "TTree.h"
#include "TFile.h"

//
// class declaration
//

class EDBRTreeMaker : public edm::EDAnalyzer {
public:
  explicit EDBRTreeMaker(const edm::ParameterSet&);
  ~EDBRTreeMaker();
  //static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
  TTree* outTree_;

  int nevent, run, ls;
  int nVtx;
  int numCands;
  double ptVlep, ptVhad, yVlep, yVhad, phiVlep, phiVhad, massVlep, massVhad;
  double met, metPhi, mtVlep;
  double tau1, tau2, tau3, tau21;
  double ptlep1, ptlep2, ptjet1;
  double etalep1, etalep2, etajet1;
  double philep1, philep2, phijet1;
  double triggerWeight, lumiWeight, pileupWeight;
  int channel, lep, reg;
  double deltaRleplep, deltaRlepjet, delPhilepmet, delPhijetmet;
  double candMass;

  // Electron ID 
  double eeDeltaR;
  double ptel1, ptel2;
  double etaSC1, etaSC2;
  double dEtaIn1, dEtaIn2;
  double dPhiIn1, dPhiIn2;
  double hOverE1, hOverE2;
  double full5x5_sigma1, full5x5_sigma2;
  double ooEmooP1, ooEmooP2;
  double d01, d02;
  double dz1, dz2;
  double relIso1, relIso2;
  int missingHits1, missingHits2;
  int passConVeto1, passConVeto2;
  int el1passID, el2passID;
  edm::InputTag electronIdTag_;
  void setDummyValues();

  /// Parameters to steer the treeDumper
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  bool isGen_;
  //std::string hadronicVSrc_, leptonicVSrc_;
  std::string gravitonSrc_, metSrc_;
};

//
// constructors and destructor
//
EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig)

{
  originalNEvents_ = iConfig.getParameter<int>("originalNEvents");
  crossSectionPb_  = iConfig.getParameter<double>("crossSectionPb");
  targetLumiInvPb_ = iConfig.getParameter<double>("targetLumiInvPb");
  EDBRChannel_     = iConfig.getParameter<std::string>("EDBRChannel");
  isGen_           = iConfig.getParameter<bool>("isGen");
  // Sources
  //hadronicVSrc_ = iConfig.getParameter<std::string>("hadronicVSrc");
  //leptonicVSrc_ = iConfig.getParameter<std::string>("leptonicVSrc");
  gravitonSrc_     = iConfig.getParameter<std::string>("gravitonSrc");
  metSrc_          = iConfig.getParameter<std::string>("metSrc");
  electronIdTag_   = iConfig.getParameter<edm::InputTag>("electronIDs");

  if(EDBRChannel_ == "VZ_CHANNEL")
    channel=VZ_CHANNEL;
  else if(EDBRChannel_ == "VW_CHANNEL")
    channel=VW_CHANNEL;
  else if(EDBRChannel_ == "VH_CHANNEL")
    channel=VH_CHANNEL;
  else {
    cms::Exception ex("InvalidConfiguration");
    ex << "Unknown channel " << EDBRChannel_  
       << ". Please check EDBRTreeMaker.cc for allowed values.";
    throw ex;
  }
  
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  outTree_ = fs->make<TTree>("EDBRCandidates","EDBR Candidates");

  /// Basic event quantities
  outTree_->Branch("event"           ,&nevent         ,"event/I"          );
  outTree_->Branch("nVtx"            ,&nVtx           ,"nVtx/I"           );
  outTree_->Branch("numCands"        ,&numCands       ,"numCands/I"       );
  outTree_->Branch("ptVlep"          ,&ptVlep         ,"ptVlep/D"         );
  outTree_->Branch("ptVhad"          ,&ptVhad         ,"ptVhad/D"         );
  outTree_->Branch("yVlep"           ,&yVlep          ,"yVlep/D"          );
  outTree_->Branch("yVhad"           ,&yVhad          ,"yVhad/D"          );
  outTree_->Branch("phiVlep"         ,&phiVlep        ,"phiVlep/D"        );
  outTree_->Branch("phiVhad"         ,&phiVhad        ,"phiVhad/D"        );
  outTree_->Branch("massVlep"        ,&massVlep       ,"massVlep/D"       );
  outTree_->Branch("mtVlep"          ,&mtVlep         ,"mtVlep/D"         );
  outTree_->Branch("massVhad"        ,&massVhad       ,"massVhad/D"       );
  outTree_->Branch("tau1"            ,&tau1           ,"tau1/D"           );
  outTree_->Branch("tau2"            ,&tau2           ,"tau2/D"           );
  outTree_->Branch("tau3"            ,&tau3           ,"tau3/D"           );
  outTree_->Branch("tau21"           ,&tau21          ,"tau21/D"          );
  outTree_->Branch("lep"             ,&lep            ,"lep/I"            );
  outTree_->Branch("region"          ,&reg            ,"region/I"         );
  outTree_->Branch("channel"         ,&channel        ,"channel/I"        );
  outTree_->Branch("candMass"        ,&candMass       ,"candMass/D"       );

  /// Electron ID quantities
  outTree_->Branch("eeDeltaR"        ,&eeDeltaR       ,"eeDeltaR/D"       );
  outTree_->Branch("ptel1"           ,&ptel1          ,"ptel1/D"          );
  outTree_->Branch("ptel2"           ,&ptel2          ,"ptel2/D"          );
  outTree_->Branch("etaSC1"          ,&etaSC1         ,"etaSC1/D"         );
  outTree_->Branch("etaSC2"          ,&etaSC2         ,"etaSC2/D"         );
  outTree_->Branch("dEtaIn1"         ,&dEtaIn1        ,"dEtaIn1/D"        );
  outTree_->Branch("dEtaIn2"         ,&dEtaIn2        ,"dEtaIn2/D"        );
  outTree_->Branch("dPhiIn1"         ,&dPhiIn1        ,"dPhiIn1/D"        );
  outTree_->Branch("dPhiIn2"         ,&dPhiIn2        ,"dPhiIn2/D"        );
  outTree_->Branch("hOverE1"         ,&hOverE1        ,"hOverE1/D"        );
  outTree_->Branch("hOverE2"         ,&hOverE2        ,"hOverE2/D"        );
  outTree_->Branch("full5x5_sigma1"  ,&full5x5_sigma1 ,"full5x5_sigma1/D" );
  outTree_->Branch("full5x5_sigma2"  ,&full5x5_sigma2 ,"full5x5_sigma2/D" );
  outTree_->Branch("ooEmooP1"        ,&ooEmooP1       ,"ooEmooP1/D"       );
  outTree_->Branch("ooEmooP2"        ,&ooEmooP2       ,"ooEmooP2/D"       );
  outTree_->Branch("d01"             ,&d01            ,"d01/D"            );
  outTree_->Branch("d02"             ,&d02            ,"d02/D"            );
  outTree_->Branch("dz1"             ,&dz1            ,"dz1/D"            );
  outTree_->Branch("dz2"             ,&dz2            ,"dz2/D"            );
  outTree_->Branch("relIso1"         ,&relIso1        ,"relIso1/D"        );
  outTree_->Branch("relIso2"         ,&relIso2        ,"relIso2/D"        );
  outTree_->Branch("missingHits1"    ,&missingHits1   ,"missingHits1/I"   );
  outTree_->Branch("missingHits2"    ,&missingHits2   ,"missingHits2/I"   );
  outTree_->Branch("passConVeto1"    ,&passConVeto1   ,"passConVeto1/I"   );
  outTree_->Branch("passConVeto2"    ,&passConVeto2   ,"passConVeto2/I"   );
  outTree_->Branch("el1passID"       ,&el1passID      ,"el1passID/I"      );
  outTree_->Branch("el2passID"       ,&el2passID      ,"el2passID/I"      );
  
  /// Generic kinematic quantities
  outTree_->Branch("ptlep1"          ,&ptlep1         ,"ptlep1/D"         );
  outTree_->Branch("ptlep2"          ,&ptlep2         ,"ptlep2/D"         );
  outTree_->Branch("ptjet1"          ,&ptjet1         ,"ptjet1/D"         );
  outTree_->Branch("etalep1"         ,&etalep1        ,"etalep1/D"        );
  outTree_->Branch("etalep2"         ,&etalep2        ,"etalep2/D"        );
  outTree_->Branch("etajet1"         ,&etajet1        ,"etajet1/D"        );
  outTree_->Branch("philep1"         ,&philep1        ,"philep1/D"        );
  outTree_->Branch("philep2"         ,&philep2        ,"philep2/D"        );
  outTree_->Branch("phijet1"         ,&phijet1        ,"phijet1/D"        );
  outTree_->Branch("met"             ,&met            ,"met/D"            );
  outTree_->Branch("metPhi"          ,&metPhi         ,"metPhi/D"         );

  /// Other quantities
  outTree_->Branch("triggerWeight"   ,&triggerWeight  ,"triggerWeight/D"  );
  outTree_->Branch("lumiWeight"      ,&lumiWeight     ,"lumiWeight/D"     );
  outTree_->Branch("pileupWeight"    ,&pileupWeight   ,"pileupWeight/D"   );
  outTree_->Branch("deltaRleplep"    ,&deltaRleplep   ,"deltaRleplep/D"   );
  outTree_->Branch("delPhilepmet"    ,&delPhilepmet   ,"delPhilepmet/D"   );
  outTree_->Branch("deltaRlepjet"    ,&deltaRlepjet   ,"deltaRlepjet/D"   );
  outTree_->Branch("delPhijetmet"    ,&delPhijetmet   ,"delPhijetmet/D"   );
}


EDBRTreeMaker::~EDBRTreeMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
EDBRTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   nevent = iEvent.eventAuxiliary().event();
   run    = iEvent.eventAuxiliary().run();
   ls     = iEvent.eventAuxiliary().luminosityBlock();

   //edm::Handle<edm::View<pat::Jet> > hadronicVs;
   //iEvent.getByLabel(hadronicVSrc_.c_str(), hadronicVs);
   
   //edm::Handle<edm::View<reco::Candidate> > leptonicVs;
   //iEvent.getByLabel(leptonicVSrc_.c_str(), leptonicVs);
   
   edm::Handle<edm::View<reco::Candidate> > gravitons;
   iEvent.getByLabel(gravitonSrc_.c_str(), gravitons);

   edm::Handle<edm::View<reco::Candidate> > metHandle;
   iEvent.getByLabel(metSrc_.c_str(), metHandle);
   
   /// How should we choose the correct graviton candidate?
   numCands = gravitons->size();

   //StringCutObjectSelector<T>
   
   setDummyValues(); //Initalize variables with dummy values
   
   if(numCands != 0 ) {
       const reco::Candidate& graviton  = gravitons->at(0);
       //const pat::Jet& hadronicV = hadronicVs->at(0);
       //const reco::Candidate& leptonicV = leptonicVs->at(0);
       const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
       const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));
       const reco::Candidate& metCand = metHandle->at(0);
       
       /// All the quantities which depend on RECO could go here
       if(not isGen_) {
           edm::Handle<reco::VertexCollection> vertices;
           iEvent.getByLabel("offlineSlimmedPrimaryVertices", vertices);
           if (vertices->empty()) return; // skip the event if no PV found
	   nVtx = vertices->size();
           reco::VertexCollection::const_iterator firstGoodVertex = vertices->end();
           for (reco::VertexCollection::const_iterator vtx = vertices->begin(); vtx != vertices->end(); ++vtx) {
               // Replace isFake() for miniAOD because it requires tracks and miniAOD vertices don't have tracks:
               // Vertex.h: bool isFake() const {return (chi2_==0 && ndof_==0 && tracks_.empty());}
               if (  /*!vtx->isFake() &&*/ 
                     !(vtx->chi2()==0 && vtx->ndof()==0) 
	             &&  vtx->ndof()>=4. && vtx->position().Rho()<=2.0
	             && fabs(vtx->position().Z())<=24.0) {
                  firstGoodVertex = vtx;
                  break;
               }           
           }
           if ( firstGoodVertex==vertices->end() ) return; // skip event if there are no good PVs

           //*****************************************************************//
           //************************* ID for electrons **********************//
           //*****************************************************************//
           switch(channel){
              case VZ_CHANNEL:
                 if(leptonicV.daughter(0)->isElectron() && 
                    leptonicV.daughter(1)->isElectron()    ) {
                    const pat::Electron *el1 = (pat::Electron*)leptonicV.daughter(0);
                    const pat::Electron *el2 = (pat::Electron*)leptonicV.daughter(1);
                    if (el1->gsfTrack().isNonnull() && 
                        el2->gsfTrack().isNonnull()    ){
                        reco::GsfElectron::PflowIsolationVariables pfIso1 = el1->pfIsolationVariables();
                        reco::GsfElectron::PflowIsolationVariables pfIso2 = el2->pfIsolationVariables();
                        eeDeltaR       = reco::deltaR(el1->p4(),el2->p4());
                        ptel1          = el1->pt();
                        ptel2          = el2->pt();
                        etaSC1         = el1->superCluster()->eta();
                        etaSC2         = el2->superCluster()->eta();
                        dEtaIn1        = el1->deltaEtaSuperClusterTrackAtVtx();
                        dEtaIn2        = el2->deltaEtaSuperClusterTrackAtVtx();
                        dPhiIn1        = el1->deltaPhiSuperClusterTrackAtVtx();
                        dPhiIn2        = el2->deltaPhiSuperClusterTrackAtVtx();
                        hOverE1        = el1->hcalOverEcal();
                        hOverE2        = el2->hcalOverEcal();
                        full5x5_sigma1 = el1->full5x5_sigmaIetaIeta();
                        full5x5_sigma2 = el2->full5x5_sigmaIetaIeta();
                        ooEmooP1       = el1->ecalEnergy() && std::isfinite(el1->ecalEnergy()) ? 
                                         fabs(1.0/el1->ecalEnergy() - el1->eSuperClusterOverP()/el1->ecalEnergy() ) : 1e9;
                        ooEmooP2       = el2->ecalEnergy() && std::isfinite(el2->ecalEnergy()) ? 
                                         fabs(1.0/el2->ecalEnergy() - el2->eSuperClusterOverP()/el2->ecalEnergy() ) : 1e9;
                        double absiso1 = pfIso1.sumChargedHadronPt + std::max(0.0, pfIso1.sumNeutralHadronEt + pfIso1.sumPhotonEt - 0.5*pfIso1.sumPUPt );
                        double absiso2 = pfIso2.sumChargedHadronPt + std::max(0.0, pfIso2.sumNeutralHadronEt + pfIso2.sumPhotonEt - 0.5*pfIso2.sumPUPt );
                        relIso1        = absiso1/el1->pt();
                        relIso2        = absiso2/el2->pt();
                        d01            = (-1)*el1->gsfTrack()->dxy(firstGoodVertex->position());   
                        dz1            = el1->gsfTrack()->dz(firstGoodVertex->position());
                        missingHits1   = el1->gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
                        d02            = (-1)*el2->gsfTrack()->dxy(firstGoodVertex->position());  
                        dz2            = el2->gsfTrack()->dz(firstGoodVertex->position());
                        missingHits2   = el2->gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
                        passConVeto1   = el1->passConversionVeto();
                        passConVeto2   = el2->passConversionVeto();
                        el1passID      = ( el1->electronID(electronIdTag_.encode())>0.5 );
                        el2passID      = ( el2->electronID(electronIdTag_.encode())>0.5 );
                    }
                 }
                 break;
              case VW_CHANNEL:
                 if( leptonicV.daughter(0)->isElectron()||leptonicV.daughter(1)->isElectron() ) {
                       const pat::Electron *el1 = leptonicV.daughter(0)->isElectron() ? 
                                                  (pat::Electron*)leptonicV.daughter(0):
                                                  (pat::Electron*)leptonicV.daughter(1);
                    if (el1->gsfTrack().isNonnull()){
                        reco::GsfElectron::PflowIsolationVariables pfIso1 = el1->pfIsolationVariables();
                        ptel1          = el1->pt();
                        etaSC1         = el1->superCluster()->eta();
                        dEtaIn1        = el1->deltaEtaSuperClusterTrackAtVtx();
                        dPhiIn1        = el1->deltaPhiSuperClusterTrackAtVtx();
                        hOverE1        = el1->hcalOverEcal();
                        full5x5_sigma1 = el1->full5x5_sigmaIetaIeta();
                        ooEmooP1       = el1->ecalEnergy() && std::isfinite(el1->ecalEnergy()) ? 
                                         fabs(1.0/el1->ecalEnergy() - el1->eSuperClusterOverP()/el1->ecalEnergy() ) : 1e9;
                        double absiso1 = pfIso1.sumChargedHadronPt + std::max(0.0, pfIso1.sumNeutralHadronEt + pfIso1.sumPhotonEt - 0.5*pfIso1.sumPUPt );
                        relIso1        = absiso1/el1->pt();
                        d01            = (-1)*el1->gsfTrack()->dxy(firstGoodVertex->position());   
                        dz1            = el1->gsfTrack()->dz(firstGoodVertex->position());
                        missingHits1   = el1->gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
            	        passConVeto1   = el1->passConversionVeto();
                        el1passID      = ( el1->electronID(electronIdTag_.encode())>0.5 );
                    }
                 }
                 break;
              case VH_CHANNEL: // This channel needs to be implemented 
                 break;
           }
           //*****************************************************************//
           //********************* close ID for electrons ********************//
           //*****************************************************************//
           massVhad     = hadronicV.userFloat("ak8PFJetsCHSPrunedLinks");
       }
       
       if(isGen_) {
	   massVhad = hadronicV.userFloat("ak8GenJetsPrunedLinks");
	   nVtx = 0;
       }

       /// For the time being, set these to 1
       triggerWeight=1.0;
       pileupWeight=1.0;

       double targetEvents = targetLumiInvPb_*crossSectionPb_;
       lumiWeight = targetEvents/originalNEvents_;

       candMass     = graviton.mass();
   
       ptVlep       = leptonicV.pt();
       ptVhad       = hadronicV.pt();
       yVlep        = leptonicV.eta();
       yVhad        = hadronicV.eta();
       phiVlep      = leptonicV.phi();
       phiVhad      = hadronicV.phi();
       massVlep     = leptonicV.mass();
       mtVlep       = leptonicV.mt();
   
       tau1         = hadronicV.userFloat("tau1");
       tau2         = hadronicV.userFloat("tau2");
       tau3         = hadronicV.userFloat("tau3");
       tau21        = hadronicV.userFloat("tau21");

       // Kinematics of leptons and jets
       ptlep1       = leptonicV.daughter(0)->pt();
       ptlep2       = leptonicV.daughter(1)->pt();
       etalep1      = leptonicV.daughter(0)->eta();
       etalep2      = leptonicV.daughter(1)->eta();
       philep1      = leptonicV.daughter(0)->phi();
       philep2      = leptonicV.daughter(1)->phi();
       ptjet1       = hadronicV.pt();
       etajet1      = hadronicV.eta();
       phijet1      = hadronicV.phi();

       met          = metCand.pt();
       metPhi       = metCand.phi();

       deltaRleplep = deltaR(etalep1,philep1,etalep2,philep2);
       double drl1j = deltaR(etalep1,philep1,etajet1,phijet1); 
       double drl2j = deltaR(etalep2,philep2,etajet1,phijet1); 
       deltaRlepjet = std::min(drl1j,drl2j);

       delPhilepmet = deltaPhi(philep1, metPhi);
       delPhijetmet = deltaPhi(phijet1, metPhi);

       lep          = abs(leptonicV.daughter(0)->pdgId());

       /// FIXME: these should NOT be hardcoded
       if(massVhad < 50 or massVhad > 110)
	   reg = -1;
       if(massVhad > 50 and massVhad < 70)
	   reg = 0;
       if(massVhad > 70 and massVhad < 110)
	   reg = 1;
   
       outTree_->Fill();
   }
   else {
       /// If we arrive here, that means we have NOT found a resonance candidate,
       /// i.e. numCands == 0.
       outTree_->Fill();
       //return; // skip event if there is no resonance candidate
   }
}

void EDBRTreeMaker::setDummyValues() {
     nVtx           = -1e9;
     triggerWeight  = -1e9;
     pileupWeight   = -1e9;
     lumiWeight     = -1e9;
     candMass       = -1e9;
     ptVlep         = -1e9;
     ptVhad         = -1e9;
     yVlep          = -1e9;
     yVhad          = -1e9;
     phiVlep        = -1e9;
     phiVhad        = -1e9;
     massVlep       = -1e9;
     massVhad       = -1e9;
     mtVlep         = -1e9;
     tau1           = -1e9;
     tau2           = -1e9;
     tau3           = -1e9;
     tau21          = -1e9;
     ptlep1         = -1e9;
     ptlep2         = -1e9;
     etalep1        = -1e9;
     etalep2        = -1e9;
     philep1        = -1e9;
     philep2        = -1e9;
     ptjet1         = -1e9;
     etajet1        = -1e9;
     phijet1        = -1e9;
     met            = -1e9;
     metPhi         = -1e9;
     deltaRleplep   = -1e9;
     deltaRlepjet   = -1e9;
     delPhilepmet   = -1e9;
     delPhijetmet   = -1e9;
     lep            = -1e9;
     reg            = -1e9;
     eeDeltaR       = -1e9;
     ptel1          = -1e9;
     etaSC1         = -1e9;
     dEtaIn1        = -1e9;
     dPhiIn1        = -1e9;
     hOverE1        = -1e9;
     full5x5_sigma1 = -1e9;
     ooEmooP1       = -1e9;
     d01            = -1e9;
     dz1            = -1e9;
     relIso1        = -1e9;
     missingHits1   = -1e9; 
     passConVeto1   = -1e9;
     el1passID      = -1e9;
     ptel2          = -1e9;
     etaSC2         = -1e9;
     dEtaIn2        = -1e9;
     dPhiIn2        = -1e9;
     hOverE2        = -1e9;
     full5x5_sigma2 = -1e9;
     ooEmooP2       = -1e9;
     d02            = -1e9;
     dz2            = -1e9;
     relIso2        = -1e9;
     missingHits2   = -1e9; 
     passConVeto2   = -1e9;
     el2passID      = -1e9; 
}

// ------------ method called once each job just before starting event loop  ------------
void 
EDBRTreeMaker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
EDBRTreeMaker::endJob() {
  std::cout << "EDBRTreeMaker endJob()..." << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
