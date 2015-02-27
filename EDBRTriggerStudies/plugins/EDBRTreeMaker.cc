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

#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"      
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "TLorentzVector.h"

using namespace std;
using namespace reco;
using namespace edm;
using namespace trigger;

//
// class declaration
//

class PtGreater {
public:
  template <typename T> bool operator () (const T& i, const T& j) {
    return (i->pt() > j->pt());
  }
};

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
  double massjet1;
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
  double etSC1, etSC2;
  bool e1_isEcaldriven, e2_isEcaldriven;

  /// Parameters to steer the treeDumper
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  bool isGen_;
  //std::string hadronicVSrc_, leptonicVSrc_;
  std::string gravitonSrc_, metSrc_;

  HLTConfigProvider hltConfig_; // to get configuration for L1s/Pre
  edm::InputTag hlTriggerResults_;
  edm::InputTag hlTriggerOSA_;
  std::string triggerName_;
  edm::InputTag collectionName_;

  edm::InputTag offlineElectronsTag_;
  edm::InputTag genparticleprunedTag_;
  edm::InputTag genparticlepackedTag_;

  edm::InputTag rhoTag_;

  bool triggerfired(const edm::Event& ev, edm::Handle<edm::TriggerResults> triggerResultsHandle_, TString trigname);
  bool triggerfound(const edm::Event& ev, edm::Handle<edm::TriggerResults> triggerResultsHandle_, TString trigname);
  unsigned int triggerIndex(const edm::Event& ev, edm::Handle<edm::TriggerResults> triggerResultsHandle_, TString trigname);

  bool electroncuts(vector<pat::Electron>::const_iterator theEl,reco::VertexCollection::const_iterator goodVertex, double rhoF);

  unsigned int pathIndex;
  bool triggerFound;
  bool triggerFired;
  bool trigObjmatched;

  double maxDRmatch_;
  double maxdPTmatch_;
  int counter;
  int countInAccepted;
  int countInTriggered;
  int countRecoMatchTrig;
  int countGenMatchTrig;
  int all,off,trg, mtch, gen, trg_g, mtch_g, gent;
  int mtcht;
  Double_t ptAllRecoEl[1000];
  Double_t ptOffSelRecoEl[1000];
  Double_t ptOffSelRecoEl_trig[1000];
  Double_t ptAllMatchedEl[100];
  Double_t ptMatchedEl[100];
  double eeDeltaR_OffSel;
  double eeDeltaR_OffSel_trig;
  double eeDeltaR_OffSel_mtrig;

  Double_t genleptonPt[1000];
  Double_t genleptonEta[1000];
  Double_t genleptonPhi[1000];
  Double_t genleptonMass[1000];
  Double_t genleptonCharge[1000];
  Double_t genZcandPt[1000];

  Double_t genleptonPti[1000];
  Double_t genleptonEtai[1000];

  Double_t rho_;      // the rho variable
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

  hlTriggerResults_  = iConfig.getUntrackedParameter<edm::InputTag>("TriggerResultsTag", edm::InputTag("TriggerResults", "", "HLT"));
  hlTriggerOSA_    = iConfig.getUntrackedParameter<edm::InputTag>("TriggerOSATag", edm::InputTag("selectedPatTrigger", "", "PAT"));
  triggerName_ = iConfig.getUntrackedParameter<std::string>("PathName","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v1");

  genparticleprunedTag_    = iConfig.getUntrackedParameter<edm::InputTag>("genparticleprunedTag",edm::InputTag("prunedGenParticles","","PAT"));
  genparticlepackedTag_    = iConfig.getUntrackedParameter<edm::InputTag>("genparticlepackedTag",edm::InputTag("packedGenParticles","","PAT"));

  collectionName_ = iConfig.getUntrackedParameter<edm::InputTag>("CollectionName",edm::InputTag("hltEgammaCandidatesUnseeded","","HLT"));
  offlineElectronsTag_    = iConfig.getUntrackedParameter<edm::InputTag>("OfflineElectronsTag",edm::InputTag("slimmedElectrons","","PAT"));
  maxDRmatch_ = iConfig.getUntrackedParameter<double>("maxDRforRecoMatching",0.1);
  maxdPTmatch_ = iConfig.getUntrackedParameter<double>("maxRELdPTforRecoMatching",0.1);

  rhoTag_    = iConfig.getUntrackedParameter<edm::InputTag>("rhoTag",edm::InputTag("rho","","RECO"));

  counter = 0;
  countInAccepted = 0;
  countInTriggered = 0;
  countRecoMatchTrig = 0;
  countGenMatchTrig = 0;
  e1_isEcaldriven = false;
  e2_isEcaldriven = false;

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
  outTree_->Branch("massjet1"        ,&massjet1       ,"massjet1/D"       );
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

  outTree_->Branch("etSC1"          ,&etSC1         ,"etSC1/D"         );
  outTree_->Branch("etSC2"          ,&etSC2         ,"etSC2/D"         );

  outTree_->Branch("all",&all,"all/I");
  outTree_->Branch("off",&off,"off/I");
  outTree_->Branch("trg",&trg,"trg/I");
  outTree_->Branch("mtch",&mtch,"mtch/I");   outTree_->Branch("mtcht",&mtcht,"mtcht/I");
  outTree_->Branch("gen",&gen,"gen/I");   outTree_->Branch("gent",&gent,"gent/I");
  outTree_->Branch("trg_g",&trg_g,"trg_g/I");
  outTree_->Branch("mtch_g",&mtch_g,"mtch_g/I"); 
  outTree_->Branch("countInTriggered",&countInTriggered,"countInTriggered/I");
  outTree_->Branch("triggerFired", &triggerFired, "triggerFired/I");
  outTree_->Branch("triggerFound", &triggerFound, "triggerFound/I");
  outTree_->Branch("trigObjmatched", &trigObjmatched, "trigObjmatched/I");
  outTree_->Branch("pathIndex", &pathIndex, "pathIndex/I");
  outTree_->Branch("eeDeltaR_OffSel"        ,&eeDeltaR_OffSel       ,"eeDeltaR_OffSel/D"       );
  outTree_->Branch("eeDeltaR_OffSel_trig"        ,&eeDeltaR_OffSel_trig       ,"eeDeltaR_OffSel_trig/D"       );
  outTree_->Branch("eeDeltaR_OffSel_mtrig"        ,&eeDeltaR_OffSel_mtrig       ,"eeDeltaR_OffSel_mtrig/D"       );

  outTree_->Branch("ptAllRecoEl"          ,&ptAllRecoEl        ,"ptAllRecoEl[all]/D"         );
  outTree_->Branch("ptOffSelRecoEl"       ,&ptOffSelRecoEl     ,"ptOffSelRecoEl[off]/D"         );
  outTree_->Branch("ptOffSelRecoEl_trig"       ,&ptOffSelRecoEl_trig     ,"ptOffSelRecoEl_trig[trg]/D"         );
  outTree_->Branch("ptAllMatchedEl"          ,&ptAllMatchedEl        ,"ptAllMatchedEl[mtch]/D"         );
  outTree_->Branch("ptMatchedEl"          ,&ptMatchedEl        ,"ptMatchedEl[mtch]/D"         );

  outTree_->Branch("genleptonPt"          ,&genleptonPt        ,"genleptonPt[gen]/D"         );
  outTree_->Branch("genleptonEta"          ,&genleptonEta        ,"genleptonEta[gen]/D"         );
  outTree_->Branch("genleptonPhi"          ,&genleptonPhi        ,"genleptonPhi[gen]/D"         );
  outTree_->Branch("genleptonMass"          ,&genleptonMass        ,"genleptonMass[gen]/D"         );
  outTree_->Branch("genleptonCharge"          ,&genleptonCharge        ,"genleptonCharge[gen]/D"         );
  outTree_->Branch("genZcandPt"          ,&genZcandPt        ,"genZcandPt[gen]/D"         );

  outTree_->Branch("genleptonPti"          ,&genleptonPti        ,"genleptonPti[gent]/D"         );
  outTree_->Branch("genleptonEtai"          ,&genleptonEtai        ,"genleptonEtai[gent]/D"         );

  outTree_->Branch("rho"        ,  &rho_ , "rho/D");
}


EDBRTreeMaker::~EDBRTreeMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

/*double EDBRTreeMaker::dEtaInSeed(const pat::Electron& el){
    return el->superCluster().isNonnull() && el->superCluster()->seed().isNonnull() ? 
      el->deltaEtaSuperClusterTrackAtVtx() - el->superCluster()->eta() + el->superCluster()->seed()->eta() : std::numeric_limits<float>::max();
      }*/

bool EDBRTreeMaker::electroncuts(vector<pat::Electron>::const_iterator theEl, reco::VertexCollection::const_iterator goodVertex, double rhoF){
  double pt = theEl->pt();
  double eta = theEl->superCluster()->eta();
  double etSC = theEl->caloEnergy()*sin(theEl->p4().theta());
  bool isEcal = theEl->ecalDriven();
  double dEtaIn = theEl->superCluster().isNonnull() && theEl->superCluster()->seed().isNonnull() ?
    theEl->deltaEtaSuperClusterTrackAtVtx() - theEl->superCluster()->eta() + theEl->superCluster()->seed()->eta() : std::numeric_limits<float>::max();
  double dPhiIn = theEl->deltaPhiSuperClusterTrackAtVtx();
  double hOverE = theEl->hcalOverEcal();
  double sigmaIetaIeta = theEl->full5x5_sigmaIetaIeta();
  double fraction = theEl->e2x5Max()/theEl->e5x5();
  double dxy = theEl->gsfTrack()->dxy(goodVertex->position());
  int hits = theEl->gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
  double caloIso = theEl->dr03EcalRecHitSumEt()+theEl->dr03HcalDepth1TowerSumEt(); 
  double reltrackIso = theEl->dr03TkSumPt()/theEl->gsfTrack()->pt(); 

  if(pt < 40 || fabs(eta) > 2.4) return false; 
  if(etSC < 35) return false;
  if(fabs(eta) > 1.4442 && fabs(eta) < 1.566) return false;
  if(!isEcal) return false;
  if(hits > 1) return false;
  if(fabs(dPhiIn) > 0.06) return false; // barrel & endcaps same
  if(reltrackIso > 5.0) return false;
  if(fabs(eta) < 1.4442){
    if(hOverE > (0.05 + (2.0/theEl->energy()))) return false;
    if(fabs(dEtaIn) > 0.004) return false;
    if(fabs(dxy) > 0.02) return false;
    if(fraction < 0.94) return false; 
    if(caloIso > (2.0 + 0.03*pt + 0.28*rhoF)) return false;
  }
  if(fabs(eta) > 1.566 && fabs(eta) < 2.5){
    if(hOverE > (0.05 + (12.5/theEl->energy()))) return false;
    if(fabs(dEtaIn) > 0.006) return false;
    if(sigmaIetaIeta > 0.03) return false;
    if(fabs(dxy) > 0.05) return false;
    if(pt < 50.0){
      if(caloIso > (2.5 + 0.28*rhoF)) return false;
    }
    else{
      if(caloIso > (2.5 + 0.03*(pt-50.0) + 0.28*rhoF)) return false;
    }
  }  
  return true;
}

bool EDBRTreeMaker::triggerfired(const edm::Event& ev, edm::Handle<edm::TriggerResults> triggerResultsHandle_, TString trigname){
  const edm::TriggerNames TrigNames_ = ev.triggerNames(*triggerResultsHandle_);
  const unsigned int ntrigs = triggerResultsHandle_->size();
  int trig = 0;
  for (unsigned int itr=0; itr<ntrigs; itr++){
    TString trigName=TrigNames_.triggerName(itr); 
    //if (!triggerResultsHandle_->accept(itr)) continue;    
    if (triggerResultsHandle_->accept(itr)){  trig++; 
    if(trigName.Contains(trigname)) return true;
    }
  } 
  return false;
}

bool EDBRTreeMaker::triggerfound(const edm::Event& ev, edm::Handle<edm::TriggerResults> triggerResultsHandle_, TString trigname){
  const edm::TriggerNames TrigNames_ = ev.triggerNames(*triggerResultsHandle_);
  const unsigned int ntrigs = triggerResultsHandle_->size(); 
  for (unsigned int itr=0; itr<ntrigs; itr++){
    TString trigName=TrigNames_.triggerName(itr); 
    if(trigName.Contains(trigname)) return true;
  }
  return false;
}

unsigned int EDBRTreeMaker::triggerIndex(const edm::Event& ev, edm::Handle<edm::TriggerResults> triggerResultsHandle_, TString trigname){
  const edm::TriggerNames TrigNames_ = ev.triggerNames(*triggerResultsHandle_);
  const unsigned int ntrigs = triggerResultsHandle_->size();
  unsigned int itr;
  for (itr=0; itr<ntrigs; itr++){
    TString trigName=TrigNames_.triggerName(itr);
    if(trigName.Contains(trigname))      return itr;
  }
  return itr;
}

//
// member functions
//

// ------------ method called for each event  ------------
void
EDBRTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  counter++;

  using namespace edm;
  using namespace std;
  using namespace reco;
  
  float elemass = 0.00511;
  
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
   
   // *** get Handle to the TriggerObjectStandAlone
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerOSA_;
   iEvent.getByLabel(hlTriggerOSA_,triggerOSA_);
   if (!triggerOSA_.isValid()) {
     cout << "Error in getting TriggerObjectStandAlone product from Event!" << endl;
     return;
   }
   
   // *** get Handle to the TriggerResults
   edm::Handle<TriggerResults> HLTR; 
   iEvent.getByLabel(hlTriggerResults_, HLTR);
   if (!HLTR.isValid()) {
     cout << "HLT TriggerResults with label " << hlTriggerResults_ << " not found!";
     return;
   }

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

   // Get rho
   edm::Handle< double > rhoH;
   iEvent.getByLabel(rhoTag_,rhoH);
   rho_ = *rhoH; //cout<<"rho = "<<rho_<<endl;

   //////////TRIGGER DECISIONS///////
   triggerFound = triggerfound(iEvent,HLTR,triggerName_);
   if (triggerFound) countInAccepted++; 
   triggerFired = triggerfired(iEvent,HLTR,triggerName_); 
   
   const unsigned int numberOfHltPaths = HLTR->size();
   //const unsigned int numberOfHltFilters = triggerEventHandle_->sizeFilters();
   
   pathIndex = triggerIndex(iEvent,HLTR,triggerName_);
   if (pathIndex>=numberOfHltPaths) {
     cout << " WARNING: path " << triggerName_ << " out of range in TriggerResults" << endl;
     return;
   }
   
   if (HLTR->wasrun(pathIndex)) {
     if (!triggerFound) cout << " WARNING: path exists in HLTR but not found in TriggerResults" << endl;
   }
   else {
     if (triggerFound) cout << " WARNING: path found in TriggerResults but it does not exist in HLTR" << endl;
   }	  
   
   const edm::TriggerNames &names = iEvent.triggerNames(*HLTR);
   vector<TLorentzVector> trigobjs;
   
   if (triggerFired) {
     countInTriggered++;
     //vector<TLorentzVector> trigobjs;
     for (pat::TriggerObjectStandAlone obj : *triggerOSA_) {
       obj.unpackPathNames(names);
       if (obj.hasCollection(collectionName_) ) {
	 TLorentzVector elec_4mom(0., 0., 0., 0.);      
	 elec_4mom.SetPtEtaPhiM(obj.pt(), obj.eta(), obj.phi(), obj.mass());
	 if ((obj.id(81) && obj.id(92)) && obj.pt()!=0){ 
	   std::vector<std::string> pathNamesAll  = obj.pathNames(false);   
	   for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
	     bool isLast = obj.hasPathName( pathNamesAll[h], true, true ); //checks if object is associated to last filter (true) & L3 filter (true)
	     if ( isLast ){ 
	       TLorentzVector el=TLorentzVector(0.,0.,0.,0.); 
	       el.SetPtEtaPhiM(obj.pt(),obj.eta(),obj.phi(),elemass);
	       trigobjs.push_back(el);
	       break;
	     }
	   }
	 }
       }
     }
   }

   edm::Handle<std::vector<pat::Electron>> elecs;
   iEvent.getByLabel(offlineElectronsTag_,elecs); 

   edm::Handle<std::vector<reco::GenParticle> > pruned;
   iEvent.getByLabel(genparticleprunedTag_,pruned);

   edm::Handle<std::vector<pat::PackedGenParticle>> packed;
   iEvent.getByLabel(genparticlepackedTag_,packed);

   // matching offline reco to trigger
   int recomatch[2]={-1,-1}; 
   int it=-1;
   int ir=-1;    
   all = 0; off = 0; trg = 0, mtch = 0, mtcht = 0;
   Double_t ptAllMatchedEl[100];
   vector<TLorentzVector> matchedReco;
   vector<vector<pat::Electron>::const_iterator> matched_ptrs;
   //   std::cout<<"--"<<matchedReco.size()<<" / "<<matched_ptrs.size()<<std::endl;
   TLorentzVector offobj(0,0,0,0);  
   vector<pat::Electron>::const_iterator ele; 
   vector<pat::Electron>::const_iterator e1; 
   vector<pat::Electron>::const_iterator e2; 

   for (vector<pat::Electron>::const_iterator recoE = elecs->begin(); recoE!=elecs->end(); ++recoE){
     ptAllRecoEl[all] = recoE->pt(); 
     all++;    
     if (!electroncuts(recoE,firstGoodVertex,rho_)) continue; 
     ir++; ptOffSelRecoEl[off] = recoE->pt(); off++;    
     TLorentzVector offobj2(0,0,0,0);
     offobj2.SetPtEtaPhiM(recoE->pt(),recoE->eta(),recoE->phi(),elemass); 
     if (ir == 0) e1 = recoE; 
     if (ir == 1) e2 = recoE;   
     if(triggerFired) { 
       ptOffSelRecoEl_trig[trg] = recoE->pt(); trg++;
       for (vector<TLorentzVector>::const_iterator trigobj = trigobjs.begin(); trigobj!=trigobjs.end(); ++trigobj){
	 vector<TLorentzVector>::const_iterator tobj;
	 it++;
	 double bestDR=maxDRmatch_;      
	 //double bestRELdPT=maxdPTmatch_; 
	 double dr=trigobj->DeltaR(offobj2);
	 //double reldpt = (abs(trigobj->Pt() - recoE->pt())/recoE->pt());   
	 //	 if (dr<bestDR && reldpt<bestRELdPT && (it!=recomatch[ir])){
	 if (dr<bestDR && (it!=recomatch[ir])){
	   bestDR=dr;
	   //bestRELdPT=reldpt;
	   recomatch[ir]=it;
	   tobj=trigobj;
	   ele=recoE; 
	   offobj=offobj2;
	 }
       } //cout<<"recomatch[ir] = "<<ir<<" / "<<recomatch[ir]<<endl;
       if (recomatch[ir]!=-1){   mtcht++; //cout<<"mtcht = "<<mtcht<<endl;
	 matchedReco.push_back(offobj);
	 matched_ptrs.push_back(ele); 
       }
       ptAllMatchedEl[mtch] = offobj.Pt(); mtch++;// cout<<"mtch = "<<mtch<<endl;
     }
   }

   if(triggerFired){    
     if (matched_ptrs.size()==2) {  
       trigObjmatched = true;
       for (int itr=0; itr<2; itr++){
	 //cout<<" ---> Matched L3 Electron:";
	 //trigobjs[itr].Print();
	 //cout<<"      with RECO Electron:";
	 //matchedReco[itr].Print();
	 ptMatchedEl[itr] = ptAllMatchedEl[itr];
       }
       countRecoMatchTrig++; 
     }//   std::cout<<"decision match = "<<trigObjmatched<<std::endl;
   }

   if(off >= 2){ 
     eeDeltaR_OffSel       = reco::deltaR(e1->p4(),e2->p4()); 
     //     if(triggerFired){ 
     if(trg >= 2){
       eeDeltaR_OffSel_trig = reco::deltaR(e1->p4(),e2->p4()); 
       //       if(trigObjmatched){
       if(mtcht >= 2){
	 eeDeltaR_OffSel_mtrig = reco::deltaR(e1->p4(),e2->p4()); 
       }
     }
   }

   ////GENERATOR matching from here ---- still working on it ----

   //   const reco::GenParticle* genColl= &(*pruned); //method 0
   //std::sort(genColl->begin(),genColl->end(),PtGreater());
   //   std::vector<reco::GenParticle> sorted(*genColl); //method 1
   //std::sort(sorted.begin(), sorted.end(), PtGreater());
   gen = 0;
   int genmatch[2]={-1,-1}; 
   int itg=-1;   
   int ig=-1;    
   vector<TLorentzVector> matchedGen;
   vector<vector<pat::PackedGenParticle>::const_iterator> matchedgen_ptrs;
   TLorentzVector genobj(0,0,0,0);  
   //   const reco::GenParticle ele;

   std::vector<const pat::PackedGenParticle *> sortedPtrs; //method 2
   sortedPtrs.reserve(packed->size());
   for (const pat::PackedGenParticle &g : *packed) {
     sortedPtrs.push_back(&g); }
   std::sort(sortedPtrs.begin(), sortedPtrs.end(), PtGreater());
   //   reco::GenParticle::const_iterator genE;
   /*   for (auto genE = sortedPtrs.begin(); genE!=sortedPtrs.end(); genE++){
     if(genE.pdgId() == 11 && genE.status() == 1){
       cout<<"sorted1 = "<<genE.pt()<<endl;
     }
     }*/

   trg_g = 0, mtch_g = 0;
   for (auto const & genPtr : sortedPtrs) {
     auto const & genE = *genPtr;
     if(genE.pdgId() == 11 && genE.status() == 1){ //cout<<"sorted = "<<genE.pt()<<" / "<<genE.eta()<<endl;
       if(genE.pt() < 40 || fabs(genE.eta()) > 2.5) continue;
       if(fabs(genE.eta()) > 1.442 && fabs(genE.eta()) < 1.556) continue;
       genleptonPt[gen] = genE.pt();  //cout<<"accepted"<<endl;
       genleptonEta[gen] = genE.eta();
       genleptonPhi[gen] = genE.phi();
       genleptonMass[gen] = genE.mass();
       genleptonCharge[gen] = genE.charge();
       const Candidate * mom = genE.mother(0);
       genZcandPt[gen] = mom->pt(); gen++; //cout<<"sorted2 = "<<genE.pt()<<endl;       
       ig++;
       TLorentzVector genobj2(0,0,0,0);
       genobj2.SetPtEtaPhiM(genE.pt(),genE.eta(),genE.phi(),elemass);
       if(triggerFired){ trg_g++;
	 for (vector<TLorentzVector>::const_iterator trigobj = trigobjs.begin(); trigobj!=trigobjs.end(); ++trigobj){
	   vector<TLorentzVector>::const_iterator tobj;
	   itg++;
	   double bestDR_g=maxDRmatch_;
	   //double bestRELdPT_g=maxdPTmatch_;
	   double dr_g=trigobj->DeltaR(genobj); //cout<<"dr = "<<dr_g<<endl;
	   // double reldpt_g = (abs(trigobj->Pt() - genE.pt())/genE.pt());//cout<<"dpt = "<<reldpt_g<<endl;
	   //   if (dr_g<bestDR_g && reldpt_g<bestRELdPT_g && (itg!=genmatch[ig])){
	   if (dr_g<bestDR_g && (itg!=genmatch[ig])){
	     bestDR_g=dr_g; 
	     //	     bestRELdPT_g=reldpt_g;
	     genmatch[ig]=itg;
	     tobj=trigobj;
	     //	     ele=genE;
	     genobj=genobj2;
	   }
	 }
	 if (genmatch[ig]!=-1){ mtch_g++;
	   matchedGen.push_back(genobj);
	   //	   matchedgen_ptrs.push_back(ele);
	 }
       }
     }
   }

   if(triggerFired){
     if (matchedGen.size()==2) {
       //   trigObjmatched = true;
       for (int itr=0; itr<2; itr++){
	 cout<<" ---> Matched L3 Electron:";                                                                                                               
	 trigobjs[itr].Print();                                                                                                                          
	 cout<<"      with GEN Electron:";                                                                                                      
	 matchedGen[itr].Print();                                                                                                                     
       }
       countGenMatchTrig++;
     }
   }


   gent = 0;
   for (std::vector<pat::PackedGenParticle>::const_iterator genP = packed->begin(); genP!=packed->end(); ++genP){
     //   for(size_t i = 0; i < genParticle->size(); ++i){ const GenParticle & g = (*genParticle)[i];
        if(genP->pdgId() == 11 && genP->status() == 1){
       genleptonPti[gent] = genP->pt(); 
       genleptonEtai[gent] = genP->eta(); 
       /*  genleptonPhi[gent] = genE->phi(); 
       genleptonMass[gent] = genE->mass(); 
       genleptonCharge[gent] = genE->charge(); 
       const Candidate * mom = genE->mother();
       genZcandPt[gent] = mom->pt();*/
       gent++;
     }
	//ADD matching here and check...
   }

   ////EDBR analyzer from here...
   if(numCands != 0 ) {
     const reco::Candidate& graviton  = gravitons->at(0);
     //const pat::Jet& hadronicV = hadronicVs->at(0);
     //const reco::Candidate& leptonicV = leptonicVs->at(0);
     const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
     const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));
     const reco::Candidate& metCand = metHandle->at(0);
     
     /// All the quantities which depend on RECO could go here
     if(not isGen_) {      
       
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
			//etSC1         = el1->superCluster()->etSC();   etSC2         = el2->superCluster()->etSC();
			etSC1         = el1->caloEnergy()*sin(el1->p4().theta());
			etSC2         = el2->caloEnergy()*sin(el2->p4().theta());
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
			e1_isEcaldriven = el1->ecalDriven();
			e2_isEcaldriven = el2->ecalDriven();
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
   
       tau1         = hadronicV.userFloat("NjettinessAK8:tau1");
       tau2         = hadronicV.userFloat("NjettinessAK8:tau2");
       tau3         = hadronicV.userFloat("NjettinessAK8:tau3");
       tau21        = tau2/tau1;

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
       massjet1     = hadronicV.mass();

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
     massjet1       = -1e9;
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

     etSC1         = -1e9;
     etSC2         = -1e9;

     for(int i = 0; i < 1000; i++){
       ptAllRecoEl[i] = {-999.0};
       ptOffSelRecoEl[i] = {-999.0}; 
       ptOffSelRecoEl_trig[i] = {-999.0}; 
       genleptonPt[i] = {-999.0};
       genleptonEta[i] = {-999.0};
       genleptonPhi[i] = {-999.0};
       genleptonMass[i] = {-999.0};
       genleptonCharge[i] = {-999.0};
       genZcandPt[i] = {-999.0};
       genleptonPti[i] = {-999.0};
       genleptonEtai[i] = {-999.0};
     }
     for(int i = 0; i < 100; i++){     
       ptAllMatchedEl[i] = {-999.0};
       ptMatchedEl[i] = {-999.0};
     }
     eeDeltaR_OffSel       = -1e9;
     eeDeltaR_OffSel_trig  = -1e9;
     eeDeltaR_OffSel_mtrig  = -1e9;

     trigObjmatched = false;

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
  std::cout << "Total # events: " << counter << std::endl;
  std::cout << "Total # events accepted" << countInAccepted << std::endl;
  std::cout << "Total # events triggered by " << triggerName_ << " : " << countInTriggered << std::endl;
  std::cout << "Total # events triggered by " << triggerName_ << " with offline/l3 electron matchings: " << countRecoMatchTrig << std::endl;
  std::cout << "Total # events triggered by " << triggerName_ << " with gen/l3 electron matchings: " << countGenMatchTrig << std::endl;
  std::cout << "Fraction of " << triggerName_ << " : " << double(countInTriggered)/double(countInAccepted) << std::endl;

}

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
