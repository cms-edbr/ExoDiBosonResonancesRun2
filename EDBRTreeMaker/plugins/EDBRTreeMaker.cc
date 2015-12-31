// system include files
#include <iostream>
#include <memory>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "ExoDiBosonResonances/EDBRLeptons/interface/TrackerMuonSelector.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "EDBRChannels.h"
#include "TAxis.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TTree.h"

class EDBRTreeMaker : public edm::EDAnalyzer {
public:
  explicit EDBRTreeMaker(const edm::ParameterSet&);
  ~EDBRTreeMaker();
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  // Parameters to steer the treeDumper
  bool isGen_;
  bool isData_;
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  edm::FileInPath puWeights_;
  edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
  edm::EDGetTokenT<bool> elHltToken;
  edm::EDGetTokenT<bool> muHltToken;
  edm::EDGetTokenT<edm::ValueMap<bool>  >    matchElHltToken;
  edm::EDGetTokenT<edm::ValueMap<bool>  >    matchMuHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >   deltaRElHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >   deltaRMuHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >  deltaPtElHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >  deltaPtMuHltToken;
  edm::EDGetTokenT<double> rhoToken;
  edm::EDGetTokenT<reco::CompositeCandidateView> gravitonsToken;
  edm::EDGetTokenT<pat::METCollection> metToken;
  edm::EDGetTokenT<pat::ElectronCollection> electronsToken;
  edm::EDGetTokenT<pat::MuonCollection> muonsToken;
  edm::EDGetTokenT<pat::JetCollection> jetsToken;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > puInfoToken;


  //------------------------ GENERAL ----------------------------------------------
  int nVtx;
  int numCands;
  int nevent, run, lumisec;
  int channel, lep, reg;
  double triggerWeight, lumiWeight, pileupWeight;
  double totalWeight;

  //------------------------ V quantities ------------------------------------------
  double ptVlep, ptVhad, yVlep, yVhad, phiVlep, phiVhad, massVlep, massVhad, mtVlep, massVhadSD;

  //------------------------- MET ---------------------------------------------------
  double met, metPhi;

  //-----------------------MET FROM GRAVITON ----------------------------------------
  double metpt, metphi;

  //---------------------- JETS ------------------------------------------------------
  int    numjets;
  double tau1,      tau2,     tau3,       tau21;
  double etjet1,    ptjet1,   etajet1,    phijet1;
  double massjet1,  softjet1, prunedjet1;
  double rhojet1;                  // SRR : Jet Rho Ratio (m/pt*R)^2
  double nhfjet1,   chfjet1;       // neutral and charged hadron energy fraction
  double nemfjet1,  cemfjet1;      // neutral and charged EM fraction
  int    nmultjet1, cmultjet1;     // neutral and charged multiplicity
  int    nsubjets;                 // number of softdrop subjets

  //-------------------- LEPTONS -----------------------------------------------------
  double ptlep1,    ptlep2;
  double etalep1,   etalep2;
  double philep1,   philep2;
  double miniIso1,  miniIso2;
  int    charge1,   charge2;
  int    pdgId1,    pdgId2;

  //--------------------DELTAS ------------------------------------------------------- 
  double deltaRleplep, deltaRlepjet, delPhilepmet, delPhijetmet, deltaphijetmet;

  //-------------------CANDIDATES MASS -----------------------------------------------
  double candMass;
  double candTMass; // transverse mass

  //-------------------- HIGH LEVEL TRIGGER ------------------------------------------
  int    elhltbit;
  int    muhltbit;
  int    matchHlt1;
  int    matchHlt2;
  double deltaRlep1Obj;
  double deltaRlep2Obj;
  double deltaPtlep1Obj;
  double deltaPtlep2Obj;

  // Electron ID 
  double d01,              d02;
  double dz1,              dz2;
  double etel1,            etel2;
  double ptel1,            ptel2;
  double etaSC1,           etaSC2;
  double dEtaIn1,          dEtaIn2;
  double dPhiIn1,          dPhiIn2;
  double hOverE1,          hOverE2;
  double caloIso1,         caloIso2;
  double ooEmooP1,         ooEmooP2;
  double trackIso1,        trackIso2;
  double dEtaSeed1,        dEtaSeed2; 
  double sigmaIEtaIEta1,   sigmaIEtaIEta2;
  double e1x5overE5x5_1,   e1x5overE5x5_2;
  double e2x5overE5x5_1,   e2x5overE5x5_2;
  double rho; // energy density
  double eeDeltaR;
  int    barrel1,          barrel2;
  int    endcap1,          endcap2;
  int    heepV601,         heepV602;
  int    modheep1,         modheep2;
  int    ecalDriven1,      ecalDriven2;
  int    missingHits1,     missingHits2;
  int    passConVeto1,     passConVeto2;
  EffectiveAreas effectiveAreas;

  // Muon ID 
  int    highPtMu1,        highPtMu2;
  int    trackerMu1,       trackerMu2;
  int    isPFMu1,          isPFMu2;
  int    isGlobalMu1,      isGlobalMu2;
  int    isTrackerMu1,     isTrackerMu2;
  int    matchedStations1, matchedStations2;
  int    pixelHits1,       pixelHits2;
  int    trackerLayers1,   trackerLayers2;
  double relativeError1,   relativeError2;
  double dBCut1,           dBCut2;
  double longiCut1,        longiCut2;
  double relIsoR03_1,      relIsoR03_2;
  double relIsoR04_1,      relIsoR04_2;

  void setDummyValues();

  edm::Service<TFileService> fs;
  TTree* outTree_;
  //TFile *f1;
  //TH1D *h1;

};

EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig):
  isGen_           (                                   iConfig.getParameter<bool>          ( "isGen"             ) ),
  originalNEvents_ (                                   iConfig.getParameter<int>           ( "originalNEvents"   ) ),
  crossSectionPb_  (                                   iConfig.getParameter<double>        ( "crossSectionPb"    ) ),
  targetLumiInvPb_ (                                   iConfig.getParameter<double>        ( "targetLumiInvPb"   ) ),
  EDBRChannel_     (                                   iConfig.getParameter<std::string>   ( "EDBRChannel"       ) ),
  vertexToken_     ( consumes<reco::VertexCollection>( iConfig.getParameter<edm::InputTag> ( "vertex"          ) ) ),
  effectiveAreas   ( edm::FileInPath("RecoEgamma/ElectronIdentification/data/Spring15/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_25ns.txt").fullPath())
{
  using namespace edm;

  if( iConfig.existsAs<bool>("isData") )
       isData_ = iConfig.getParameter<bool> ("isData");
  else isData_ = true;

  if( iConfig.existsAs<FileInPath>("puWeights") )
       puWeights_ = iConfig.getParameter<FileInPath>("puWeights") ;

  elHltToken        = consumes<bool>(            InputTag("hltMatchingElectrons", "trigBit"   ));
  muHltToken        = consumes<bool>(            InputTag("hltMatchingMuons",     "trigBit"   ));
  matchElHltToken   = consumes<ValueMap<bool> >( InputTag("hltMatchingElectrons","matchHlt"   ));
  matchMuHltToken   = consumes<ValueMap<bool> >( InputTag("hltMatchingMuons",    "matchHlt"   ));
  deltaRElHltToken  = consumes<ValueMap<float> >(InputTag("hltMatchingElectrons","deltaR"     ));
  deltaRMuHltToken  = consumes<ValueMap<float> >(InputTag("hltMatchingMuons",    "deltaR"     ));
  deltaPtElHltToken = consumes<ValueMap<float> >(InputTag("hltMatchingElectrons","deltaPt"    ));
  deltaPtMuHltToken = consumes<ValueMap<float> >(InputTag("hltMatchingMuons",    "deltaPt"    ));
  rhoToken          = consumes<double>(          InputTag("fixedGridRhoFastjetAll"            ));
  gravitonsToken    = consumes<reco::CompositeCandidateView>(  InputTag("graviton","","TEST"  ));
  metToken          = consumes<pat::METCollection>(            InputTag("slimmedMETs"         ));
  electronsToken    = consumes<pat::ElectronCollection>(       InputTag("slimmedElectrons"    ));
  muonsToken        = consumes<pat::MuonCollection>(           InputTag("slimmedMuons"        ));
  jetsToken         = consumes<pat::JetCollection>(            InputTag("slimmedJetsAK8"      ));
  puInfoToken       = consumes<std::vector<PileupSummaryInfo>>(InputTag("slimmedAddPileupInfo"));

  if(EDBRChannel_ == "VZ_CHANNEL")
    channel=VZ_CHANNEL;
  else if(EDBRChannel_ == "VW_CHANNEL")
    channel=VW_CHANNEL;
  else if(EDBRChannel_ == "VH_CHANNEL")
    channel=VH_CHANNEL;
  else if(EDBRChannel_ == "VZnu_CHANNEL")
    channel=VZnu_CHANNEL;
  else {
    cms::Exception ex("InvalidConfiguration");
    ex << "Unknown channel " << EDBRChannel_  
       << ". Please check EDBRTreeMaker.cc for allowed values.";
    throw ex;
  }

  outTree_ = fs->make<TTree>("EDBRCandidates","EDBR Candidates");

  // Basic event quantities
  outTree_->Branch("event"            ,&nevent           ,"event/I"           );
  outTree_->Branch("run"              ,&run              ,"run/I"             );
  outTree_->Branch("lumisec"          ,&lumisec          ,"lumisec/I"         );
  outTree_->Branch("nVtx"             ,&nVtx             ,"nVtx/I"            );
  outTree_->Branch("numCands"         ,&numCands         ,"numCands/I"        );
  outTree_->Branch("ptVlep"           ,&ptVlep           ,"ptVlep/D"          );
  outTree_->Branch("ptVhad"           ,&ptVhad           ,"ptVhad/D"          );
  outTree_->Branch("yVlep"            ,&yVlep            ,"yVlep/D"           );
  outTree_->Branch("yVhad"            ,&yVhad            ,"yVhad/D"           );
  outTree_->Branch("phiVlep"          ,&phiVlep          ,"phiVlep/D"         );
  outTree_->Branch("phiVhad"          ,&phiVhad          ,"phiVhad/D"         );
  outTree_->Branch("massVlep"         ,&massVlep         ,"massVlep/D"        );
  outTree_->Branch("mtVlep"           ,&mtVlep           ,"mtVlep/D"          );
  outTree_->Branch("massVhad"         ,&massVhad         ,"massVhad/D"        );
  outTree_->Branch("massVhadSD"       ,&massVhadSD       ,"massVhadSD/D"      );
  outTree_->Branch("tau1"             ,&tau1             ,"tau1/D"            );
  outTree_->Branch("tau2"             ,&tau2             ,"tau2/D"            );
  outTree_->Branch("tau3"             ,&tau3             ,"tau3/D"            );
  outTree_->Branch("tau21"            ,&tau21            ,"tau21/D"           );
  outTree_->Branch("lep"              ,&lep              ,"lep/I"             );
  outTree_->Branch("region"           ,&reg              ,"region/I"          );
  outTree_->Branch("channel"          ,&channel          ,"channel/I"         );
  outTree_->Branch("candMass"         ,&candMass         ,"candMass/D"        );
  outTree_->Branch("candTMass"        ,&candTMass        ,"candTMass/D"       );

  // HLT info 
  outTree_->Branch("elhltbit"         ,&elhltbit         ,"elhltbit/I"        );
  outTree_->Branch("muhltbit"         ,&muhltbit         ,"muhltbit/I"        );
  outTree_->Branch("matchHlt1"        ,&matchHlt1        ,"matchHlt1/I"       );
  outTree_->Branch("matchHlt2"        ,&matchHlt2        ,"matchHlt2/I"       );
  outTree_->Branch("deltaRlep1Obj"    ,&deltaRlep1Obj    ,"deltaRlep1Obj/D"   );
  outTree_->Branch("deltaRlep2Obj"    ,&deltaRlep2Obj    ,"deltaRlep2Obj/D"   );
  outTree_->Branch("deltaPtlep1Obj"   ,&deltaPtlep1Obj   ,"deltaPtlep1Obj/D"  );
  outTree_->Branch("deltaPtlep2Obj"   ,&deltaPtlep2Obj   ,"deltaPtlep2Obj/D"  );
 
  // Muon ID quantities
  outTree_->Branch("trackerMu1"       ,&trackerMu1       ,"trackerMu1/I"      );
  outTree_->Branch("trackerMu2"       ,&trackerMu2       ,"trackerMu2/I"      );
  outTree_->Branch("highPtMu1"        ,&highPtMu1        ,"highPtMu1/I"       );
  outTree_->Branch("highPtMu2"        ,&highPtMu2        ,"highPtMu2/I"       );
  outTree_->Branch("isPFMu1"          ,&isPFMu1          ,"isPFMu1/I"         );
  outTree_->Branch("isPFMu2"          ,&isPFMu2          ,"isPFMu2/I"         );
  outTree_->Branch("isGlobalMu1"      ,&isGlobalMu1      ,"isGlobalMu1/I"     );
  outTree_->Branch("isGlobalMu2"      ,&isGlobalMu2      ,"isGlobalMu2/I"     );
  outTree_->Branch("isTrackerMu1"     ,&isTrackerMu1     ,"isTrackerMu1/I"    );
  outTree_->Branch("isTrackerMu2"     ,&isTrackerMu2     ,"isTrackerMu2/I"    );
  outTree_->Branch("matchedStations1" ,&matchedStations1 ,"matchedStations1/I");
  outTree_->Branch("matchedStations2" ,&matchedStations2 ,"matchedStations2/I");
  outTree_->Branch("pixelHits1"       ,&pixelHits1       ,"pixelHits1/I"      );
  outTree_->Branch("pixelHits2"       ,&pixelHits2       ,"pixelHits2/I"      );
  outTree_->Branch("trackerLayers1"   ,&trackerLayers1   ,"trackerLayers1/I"  );
  outTree_->Branch("trackerLayers2"   ,&trackerLayers2   ,"trackerLayers2/I"  );
  outTree_->Branch("relativeError1"   ,&relativeError1   ,"relativeError1/D"  );
  outTree_->Branch("relativeError2"   ,&relativeError2   ,"relativeError2/D"  );
  outTree_->Branch("dBCut1"           ,&dBCut1           ,"dBCut1/D"          );
  outTree_->Branch("dBCut2"           ,&dBCut2           ,"dBCut2/D"          );
  outTree_->Branch("longiCut1"        ,&longiCut1        ,"longiCut1/D"       );
  outTree_->Branch("longiCut2"        ,&longiCut2        ,"longiCut2/D"       );
  outTree_->Branch("relIsoR03_1"      ,&relIsoR03_1      ,"relIsoR03_1/D"     );
  outTree_->Branch("relIsoR03_2"      ,&relIsoR03_2      ,"relIsoR03_2/D"     );
  outTree_->Branch("relIsoR04_1"      ,&relIsoR04_1      ,"relIsoR04_1/D"     );
  outTree_->Branch("relIsoR04_2"      ,&relIsoR04_2      ,"relIsoR04_2/D"     );

  // Electron ID quantities
  outTree_->Branch("barrel1"          ,&barrel1          ,"barrel1/I"         );
  outTree_->Branch("barrel2"          ,&barrel2          ,"barrel2/I"         );
  outTree_->Branch("endcap1"          ,&endcap1          ,"endcap1/I"         );
  outTree_->Branch("endcap2"          ,&endcap2          ,"endcap2/I"         );
  outTree_->Branch("eeDeltaR"         ,&eeDeltaR         ,"eeDeltaR/D"        );
  outTree_->Branch("etel1"            ,&etel1            ,"etel1/D"           );
  outTree_->Branch("etel2"            ,&etel2            ,"etel2/D"           );
  outTree_->Branch("ptel1"            ,&ptel1            ,"ptel1/D"           );
  outTree_->Branch("ptel2"            ,&ptel2            ,"ptel2/D"           );
  outTree_->Branch("etaSC1"           ,&etaSC1           ,"etaSC1/D"          );
  outTree_->Branch("etaSC2"           ,&etaSC2           ,"etaSC2/D"          );
  outTree_->Branch("dEtaIn1"          ,&dEtaIn1          ,"dEtaIn1/D"         );
  outTree_->Branch("dEtaIn2"          ,&dEtaIn2          ,"dEtaIn2/D"         );
  outTree_->Branch("dEtaSeed1"        ,&dEtaSeed1        ,"dEtaSeed1/D"       );
  outTree_->Branch("dEtaSeed2"        ,&dEtaSeed2        ,"dEtaSeed2/D"       );
  outTree_->Branch("dPhiIn1"          ,&dPhiIn1          ,"dPhiIn1/D"         );
  outTree_->Branch("dPhiIn2"          ,&dPhiIn2          ,"dPhiIn2/D"         );
  outTree_->Branch("hOverE1"          ,&hOverE1          ,"hOverE1/D"         );
  outTree_->Branch("hOverE2"          ,&hOverE2          ,"hOverE2/D"         );
  outTree_->Branch("sigmaIEtaIEta1"   ,&sigmaIEtaIEta1   ,"sigmaIEtaIEta1/D"  );
  outTree_->Branch("sigmaIEtaIEta2"   ,&sigmaIEtaIEta2   ,"sigmaIEtaIEta2/D"  );
  outTree_->Branch("e1x5overE5x5_1"   ,&e1x5overE5x5_1   ,"e1x5overE5x5_1/D"  );
  outTree_->Branch("e1x5overE5x5_2"   ,&e1x5overE5x5_2   ,"e1x5overE5x5_2/D"  );
  outTree_->Branch("e2x5overE5x5_1"   ,&e2x5overE5x5_1   ,"e2x5overE5x5_1/D"  );
  outTree_->Branch("e2x5overE5x5_2"   ,&e2x5overE5x5_2   ,"e2x5overE5x5_2/D"  );
  outTree_->Branch("ooEmooP1"         ,&ooEmooP1         ,"ooEmooP1/D"        );
  outTree_->Branch("ooEmooP2"         ,&ooEmooP2         ,"ooEmooP2/D"        );
  outTree_->Branch("d01"              ,&d01              ,"d01/D"             );
  outTree_->Branch("d02"              ,&d02              ,"d02/D"             );
  outTree_->Branch("dz1"              ,&dz1              ,"dz1/D"             );
  outTree_->Branch("dz2"              ,&dz2              ,"dz2/D"             );
  outTree_->Branch("caloIso1"         ,&caloIso1         ,"caloIso1/D"        );
  outTree_->Branch("caloIso2"         ,&caloIso2         ,"caloIso2/D"        );
  outTree_->Branch("trackIso1"        ,&trackIso1        ,"trackIso1/D"       );
  outTree_->Branch("trackIso2"        ,&trackIso2        ,"trackIso2/D"       );
  outTree_->Branch("rho"              ,&rho              ,"rho/D"             );
  outTree_->Branch("ecalDriven1"      ,&ecalDriven1      ,"ecalDriven1/I"     );
  outTree_->Branch("ecalDriven2"      ,&ecalDriven2      ,"ecalDriven2/I"     );
  outTree_->Branch("missingHits1"     ,&missingHits1     ,"missingHits1/I"    );
  outTree_->Branch("missingHits2"     ,&missingHits2     ,"missingHits2/I"    );
  outTree_->Branch("passConVeto1"     ,&passConVeto1     ,"passConVeto1/I"    );
  outTree_->Branch("passConVeto2"     ,&passConVeto2     ,"passConVeto2/I"    );
  outTree_->Branch("heepV601"         ,&heepV601         ,"heepV601/I"        );
  outTree_->Branch("heepV602"         ,&heepV602         ,"heepV602/I"        );
  outTree_->Branch("modheep1"         ,&modheep1         ,"modheep1/I"        );
  outTree_->Branch("modheep2"         ,&modheep2         ,"modheep2/I"        );

  // mini isolation for leptons
  outTree_->Branch("miniIso1"         ,&miniIso1         ,"miniIso1/D"        );
  outTree_->Branch("miniIso2"         ,&miniIso2         ,"miniIso2/D"        );
  
  // Jet ID quantities
  outTree_->Branch("nhfjet1"          ,&nhfjet1          ,"nhfjet1/D"         );
  outTree_->Branch("chfjet1"          ,&chfjet1          ,"chfjet1/D"         );
  outTree_->Branch("nemfjet1"         ,&nemfjet1         ,"nemfjet1/D"        );
  outTree_->Branch("cemfjet1"         ,&cemfjet1         ,"cemfjet1/D"        );
  outTree_->Branch("nmultjet1"        ,&nmultjet1        ,"nmultjet1/I"       );
  outTree_->Branch("cmultjet1"        ,&cmultjet1        ,"cmultjet1/I"       );

  // Generic kinematic quantities
  outTree_->Branch("nsubjets"         ,&nsubjets         ,"nsubjets/I"        );
  outTree_->Branch("numjets"          ,&numjets          ,"numjets/I"         );
  outTree_->Branch("ptlep1"           ,&ptlep1           ,"ptlep1/D"          );
  outTree_->Branch("ptlep2"           ,&ptlep2           ,"ptlep2/D"          );
  outTree_->Branch("ptjet1"           ,&ptjet1           ,"ptjet1/D"          );
  outTree_->Branch("etjet1"           ,&etjet1           ,"etjet1/D"          );
  outTree_->Branch("rhojet1"          ,&rhojet1          ,"rhojet1/D"         );
  outTree_->Branch("etalep1"          ,&etalep1          ,"etalep1/D"         );
  outTree_->Branch("etalep2"          ,&etalep2          ,"etalep2/D"         );
  outTree_->Branch("etajet1"          ,&etajet1          ,"etajet1/D"         );
  outTree_->Branch("philep1"          ,&philep1          ,"philep1/D"         );
  outTree_->Branch("philep2"          ,&philep2          ,"philep2/D"         );
  outTree_->Branch("charge1"          ,&charge1          ,"charge1/I"         );
  outTree_->Branch("charge2"          ,&charge2          ,"charge2/I"         );
  outTree_->Branch("pdgId1"           ,&pdgId1           ,"pdgId1/I"          );
  outTree_->Branch("pdgId2"           ,&pdgId2           ,"pdgId2/I"          );
  outTree_->Branch("phijet1"          ,&phijet1          ,"phijet1/D"         );
  outTree_->Branch("massjet1"         ,&massjet1         ,"massjet1/D"        );
  outTree_->Branch("softjet1"         ,&softjet1         ,"softjet1/D"        );
  outTree_->Branch("prunedjet1"       ,&prunedjet1       ,"prunedjet1/D"      );
  outTree_->Branch("met"              ,&met              ,"met/D"             );
  outTree_->Branch("metpt"            ,&metpt            ,"metpt/D"           );
  outTree_->Branch("metPhi"           ,&metPhi           ,"metPhi/D"          );
  
  // Other quantities
  outTree_->Branch("triggerWeight"    ,&triggerWeight    ,"triggerWeight/D"   );
  outTree_->Branch("lumiWeight"       ,&lumiWeight       ,"lumiWeight/D"      );
  outTree_->Branch("pileupWeight"     ,&pileupWeight     ,"pileupWeight/D"    );
  outTree_->Branch("totalWeight"      ,&totalWeight      ,"totalWeight/D"     );
  outTree_->Branch("deltaRleplep"     ,&deltaRleplep     ,"deltaRleplep/D"    );
  outTree_->Branch("delPhilepmet"     ,&delPhilepmet     ,"delPhilepmet/D"    );
  outTree_->Branch("deltaRlepjet"     ,&deltaRlepjet     ,"deltaRlepjet/D"    );
  outTree_->Branch("delPhijetmet"     ,&delPhijetmet     ,"delPhijetmet/D"    );
  outTree_->Branch("deltaphijetmet"   ,&deltaphijetmet   ,"deltaphijetmet/D"  );
}

EDBRTreeMaker::~EDBRTreeMaker() {}

void EDBRTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   nevent  = iEvent.eventAuxiliary().event();
   run     = iEvent.eventAuxiliary().run();
   lumisec = iEvent.eventAuxiliary().luminosityBlock();
                   
   // ------ analize trigger results ----------//
   Handle<bool> elHlt_handle;
   Handle<bool> muHlt_handle;
   Handle<ValueMap<bool> > matchHlt_handle;
   Handle<ValueMap<float> > deltaPt_handle;
   Handle<ValueMap<float> >  deltaR_handle;
   iEvent.getByToken(elHltToken, elHlt_handle);
   iEvent.getByToken(muHltToken, muHlt_handle);
   elhltbit = (int)(*elHlt_handle);
   muhltbit = (int)(*muHlt_handle);

   setDummyValues(); //Initalize variables with dummy values

   Handle<reco::CompositeCandidateView > gravitons;
   iEvent.getByToken(gravitonsToken, gravitons);
   numCands = gravitons->size();
   if(numCands != 0 ) {
       const reco::Candidate& graviton  = gravitons->at(0);
       const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));

       // met
       Handle<pat::METCollection> metHandle;
       iEvent.getByToken(metToken, metHandle);
       const pat::MET& metCand = metHandle->at(0);
       
       // All the quantities which depend on RECO could go here
       if(not isGen_) {
           // electrons and muons
           Handle<pat::ElectronCollection>   electrons;
           Handle<pat::MuonCollection>           muons;
           iEvent.getByToken(electronsToken, electrons);
           iEvent.getByToken(muonsToken,         muons);

           // number of jets
           Handle<pat::JetCollection>    jets;
           iEvent.getByToken(jetsToken,  jets);
           numjets = jets->size();
           met     = metCand.pt();
           metPhi  = metCand.phi();

           // handle goodOfflinePrimaryVertex collection
           Handle<reco::VertexCollection> vertices;
           iEvent.getByToken(vertexToken_, vertices);
           nVtx = vertices->size();
           const reco::Vertex& vertex = (*vertices)[0];
  
           // Energy density
           Handle< double > rhoHandle;
           iEvent.getByToken(rhoToken, rhoHandle);
           rho = (float)(*rhoHandle);

           //we put the definitions inside the channel
           switch(channel){
               case VZ_CHANNEL:{
                   //**************DEFINITIONS *********************************** 
                   const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
                   // candidate
                   candMass       = graviton.mass();
                   // leptons
                   ptVlep         = leptonicV.pt();
                   yVlep          = leptonicV.eta();
                   phiVlep        = leptonicV.phi();
                   massVlep       = leptonicV.mass();
                   mtVlep         = leptonicV.mt();
                   int leading    = leptonicV.daughter(0)->pt() > leptonicV.daughter(1)->pt() ? 0 : 1; 
                   const reco::Candidate *lepton1 = leptonicV.daughter(      leading);
                   const reco::Candidate *lepton2 = leptonicV.daughter((int)!leading);
                   ptlep1         = lepton1->pt();
                   ptlep2         = lepton2->pt();
                   etalep1        = lepton1->eta();
                   etalep2        = lepton2->eta();
                   philep1        = lepton1->phi();
                   philep2        = lepton2->phi();
                   charge1        = lepton1->charge();
                   charge2        = lepton2->charge();
                   pdgId1         = lepton1->pdgId();
                   pdgId2         = lepton2->pdgId();
                   lep        = abs(lepton1->pdgId());
                   // hadrons
                   ptVhad         = hadronicV.pt();
                   yVhad          = hadronicV.eta();
                   phiVhad        = hadronicV.phi();
                   tau1           = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2           = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3           = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21          = tau2/tau1;
                   etjet1         = hadronicV.et();
                   ptjet1         = hadronicV.pt();
                   etajet1        = hadronicV.eta();
                   phijet1        = hadronicV.phi();
                   massjet1       = hadronicV.mass();
                   softjet1       = hadronicV.userFloat("ak8PFJetsCHSSoftDropMass");
                   prunedjet1     = hadronicV.userFloat("ak8PFJetsCHSPrunedMass");
                   massVhad       = hadronicV.userFloat("ak8PFJetsCHSCorrPrunedMass");
		   // SRR : get rho ratio. This assumes the subjets are corrected to L2L3.
		   // If not, they must be done on-the-fly with a separate jet corrector. 
		   auto subjetsSD = hadronicV.subjets("SoftDrop");
                   nsubjets       = subjetsSD.size();
		   if ( nsubjets >= 2 ) {
		     auto groomedJet = subjetsSD[0]->p4() + subjetsSD[1]->p4();
		     rhojet1 = std::pow( groomedJet.mass() / (groomedJet.pt() * 0.8), 2.0);
		     massVhadSD     = hadronicV.mass();
		   }

                   //*****************************************************************//
                   //***************************** Jet ID ****************************//
                   //*****************************************************************//
                   nhfjet1        = hadronicV.neutralHadronEnergyFraction();
                   chfjet1        = hadronicV.chargedHadronEnergyFraction();
                   nemfjet1       = hadronicV.neutralEmEnergyFraction();
                   cemfjet1       = hadronicV.chargedEmEnergyFraction();
                   nmultjet1      = hadronicV.neutralMultiplicity();
                   cmultjet1      = hadronicV.chargedMultiplicity();
                   // deltas
                   deltaRleplep   = deltaR(etalep1,philep1,etalep2,philep2);
                   double drl1j   = deltaR(etalep1,philep1,etajet1,phijet1);
                   double drl2j   = deltaR(etalep2,philep2,etajet1,phijet1);
                   deltaRlepjet   = std::min(drl1j,drl2j);
                   delPhilepmet   = deltaPhi(philep1, metPhi);
                   delPhijetmet   = deltaPhi(phijet1, metPhi);
                   //*****************************************************************//
                   //************************* ID for muons **************************//
                   //*****************************************************************//
                   if ( leptonicV.daughter(0)->isMuon() && 
                        leptonicV.daughter(1)->isMuon()    ) {
                        int temp = leptonicV.daughter(0)->pt() > leptonicV.daughter(1)->pt() ? 0 : 1; 
                        const pat::Muon *mu1 = (pat::Muon*)leptonicV.daughter(      temp);
                        const pat::Muon *mu2 = (pat::Muon*)leptonicV.daughter((int)!temp);
                        const Ptr<pat::Muon> mu1Ptr(muons, mu1->userInt("slimmedIndex") );
                        const Ptr<pat::Muon> mu2Ptr(muons, mu2->userInt("slimmedIndex") );
                        iEvent.getByToken(deltaRMuHltToken,   deltaR_handle);
                        iEvent.getByToken(deltaPtMuHltToken,  deltaPt_handle);
                        iEvent.getByToken(matchMuHltToken, matchHlt_handle);
                        deltaRlep1Obj    =      (*deltaR_handle)[mu1Ptr];
                        deltaRlep2Obj    =      (*deltaR_handle)[mu2Ptr];
                        deltaPtlep1Obj   =      (*deltaPt_handle)[mu1Ptr];
                        deltaPtlep2Obj   =      (*deltaPt_handle)[mu2Ptr];
                        matchHlt1        = (int)(*matchHlt_handle)[mu1Ptr]; 
                        matchHlt2        = (int)(*matchHlt_handle)[mu2Ptr]; 
                        reco::MuonPFIsolation pfIsoR03_1 = mu1->pfIsolationR03();
                        reco::MuonPFIsolation pfIsoR03_2 = mu2->pfIsolationR03();
                        reco::MuonPFIsolation pfIsoR04_1 = mu1->pfIsolationR04();
                        reco::MuonPFIsolation pfIsoR04_2 = mu2->pfIsolationR04();
                        // isolation wi  th delta beta correction
                        double absisoR03_1 = pfIsoR03_1.sumChargedHadronPt + std::max(0.0,  pfIsoR03_1.sumNeutralHadronEt + pfIsoR03_1.sumPhotonEt - 0.5*pfIsoR03_1.sumPUPt );
                        double absisoR03_2 = pfIsoR03_2.sumChargedHadronPt + std::max(0.0,  pfIsoR03_2.sumNeutralHadronEt + pfIsoR03_2.sumPhotonEt - 0.5*pfIsoR03_2.sumPUPt );
                        double absisoR04_1 = pfIsoR04_1.sumChargedHadronPt + std::max(0.0,  pfIsoR04_1.sumNeutralHadronEt + pfIsoR04_1.sumPhotonEt - 0.5*pfIsoR04_1.sumPUPt );
                        double absisoR04_2 = pfIsoR04_2.sumChargedHadronPt + std::max(0.0,  pfIsoR04_2.sumNeutralHadronEt + pfIsoR04_2.sumPhotonEt - 0.5*pfIsoR04_2.sumPUPt );
                        relIsoR03_1      = absisoR03_1/mu1->pt();
                        relIsoR03_2      = absisoR03_2/mu2->pt();
                        relIsoR04_1      = absisoR04_1/mu1->pt();
                        relIsoR04_2      = absisoR04_2/mu2->pt();
                        trackerMu1       = (int)hptm::isTrackerMuon(*mu1, vertex);
                        trackerMu2       = (int)hptm::isTrackerMuon(*mu2, vertex);
                        highPtMu1        = (int)muon::isHighPtMuon( *mu1, vertex);
                        highPtMu2        = (int)muon::isHighPtMuon( *mu2, vertex);
                        isPFMu1          = mu1->isPFMuon();
                        isPFMu2          = mu2->isPFMuon();
                        isGlobalMu1      = mu1->isGlobalMuon();
                        isGlobalMu2      = mu2->isGlobalMuon();
                        isTrackerMu1     = mu1->isTrackerMuon();
                        isTrackerMu2     = mu2->isTrackerMuon();
                        matchedStations1 = mu1->numberOfMatchedStations();
                        matchedStations2 = mu2->numberOfMatchedStations();
                        if ( mu1->innerTrack().isNonnull() ){
                           pixelHits1     = mu1->innerTrack()->hitPattern().numberOfValidPixelHits();
                           trackerLayers1 = mu1->innerTrack()->hitPattern().trackerLayersWithMeasurement();
                        }
                        if ( mu2->innerTrack().isNonnull() ){
                           pixelHits2     = mu2->innerTrack()->hitPattern().numberOfValidPixelHits();
                           trackerLayers2 = mu2->innerTrack()->hitPattern().trackerLayersWithMeasurement();
                        }
                        if ( mu1->muonBestTrack().isNonnull() ){
                           relativeError1 = mu1->muonBestTrack()->ptError()/mu1->muonBestTrack()->pt();
                           dBCut1         = fabs(mu1->muonBestTrack()->dxy(vertex.position()));
                           longiCut1      = fabs(mu1->muonBestTrack()->dz( vertex.position()));
                        }
                        if ( mu2->muonBestTrack().isNonnull() ){
                           relativeError2 = mu2->muonBestTrack()->ptError()/mu2->muonBestTrack()->pt();
                           dBCut2         = fabs(mu2->muonBestTrack()->dxy(vertex.position()));
                           longiCut2      = fabs(mu2->muonBestTrack()->dz( vertex.position()));
                        }
                        // relative mini-isolation
                        miniIso1         = mu1->userFloat("miniIso");
                        miniIso2         = mu2->userFloat("miniIso");
                        // tracker-based relative isolation
                        trackIso1        = mu1->isolationR03().sumPt/mu1->pt();
                        trackIso2        = mu2->isolationR03().sumPt/mu2->pt();
                   }
                   //*****************************************************************//
                   //************************* ID for electrons **********************//
                   //*****************************************************************//
                   else if ( leptonicV.daughter(0)->isElectron() && 
                             leptonicV.daughter(1)->isElectron()    ) {
                        int temp = leptonicV.daughter(0)->pt() > leptonicV.daughter(1)->pt() ? 0 : 1; 
                        const pat::Electron *el1 = (pat::Electron*)leptonicV.daughter(      temp);
                        const pat::Electron *el2 = (pat::Electron*)leptonicV.daughter((int)!temp);
                        const Ptr<pat::Electron> el1Ptr(electrons, el1->userInt("slimmedIndex") );
                        const Ptr<pat::Electron> el2Ptr(electrons, el2->userInt("slimmedIndex") );
                        iEvent.getByToken(deltaRElHltToken,   deltaR_handle);
                        iEvent.getByToken(deltaPtElHltToken,  deltaPt_handle);
                        iEvent.getByToken(matchElHltToken, matchHlt_handle);
                        deltaRlep1Obj  =      (*deltaR_handle)[el1Ptr];
                        deltaRlep2Obj  =      (*deltaR_handle)[el2Ptr];
                        deltaPtlep1Obj =      (*deltaPt_handle)[el1Ptr];
                        deltaPtlep2Obj =      (*deltaPt_handle)[el2Ptr];
                        matchHlt1      = (int)(*matchHlt_handle)[el1Ptr]; 
                        matchHlt2      = (int)(*matchHlt_handle)[el2Ptr]; 
                        eeDeltaR       = reco::deltaR(el1->p4(),el2->p4());
                        ptel1          = el1->pt();
                        ptel2          = el2->pt();
                        etel1          = el1->superCluster()->energy();
                        etel2          = el2->superCluster()->energy();
                        etaSC1         = el1->superCluster()->eta();
                        etaSC2         = el2->superCluster()->eta();
                        barrel1        = fabs(etaSC1)<1.4442 ? 1:0;
                        barrel2        = fabs(etaSC2)<1.4442 ? 1:0;
                        endcap1        = fabs(etaSC1)>1.566 && fabs(etaSC1)<2.5 ? 1:0;
                        endcap2        = fabs(etaSC2)>1.566 && fabs(etaSC2)<2.5 ? 1:0;
                        // isolation with effective area correction
                        reco::GsfElectron::PflowIsolationVariables pfIso1 = el1->pfIsolationVariables();
                        reco::GsfElectron::PflowIsolationVariables pfIso2 = el2->pfIsolationVariables();
                        double     eA1 = effectiveAreas.getEffectiveArea( etaSC1 );
                        double     eA2 = effectiveAreas.getEffectiveArea( etaSC2 );
                        double absiso1 = pfIso1.sumChargedHadronPt + std::max(0.0, pfIso1.sumNeutralHadronEt + pfIso1.sumPhotonEt - rho*eA1 );
                        double absiso2 = pfIso2.sumChargedHadronPt + std::max(0.0, pfIso2.sumNeutralHadronEt + pfIso2.sumPhotonEt - rho*eA2 );
                        relIsoR03_1    = absiso1/el1->pt();
                        relIsoR03_2    = absiso2/el2->pt();
                        caloIso1       = el1->dr03EcalRecHitSumEt() + el1->dr03HcalDepth1TowerSumEt();
                        caloIso2       = el2->dr03EcalRecHitSumEt() + el2->dr03HcalDepth1TowerSumEt();
                        trackIso1      = el1->dr03TkSumPt();
                        trackIso2      = el2->dr03TkSumPt();
                        // retrieve mini isolation
                        miniIso1       = el1->userFloat("miniIso");
                        miniIso2       = el2->userFloat("miniIso");
                        // heepV60
                        heepV601       = el1->userInt("heepV60"); 
                        heepV602       = el1->userInt("heepV60"); 
                        modheep1       = el1->userInt("heepV60_noiso"); 
                        modheep2       = el1->userInt("heepV60_noiso"); 
                        // shower shapes
                        sigmaIEtaIEta1 = el1->full5x5_sigmaIetaIeta();
                        sigmaIEtaIEta2 = el2->full5x5_sigmaIetaIeta();
                        double e5x5_1  = el1->full5x5_e5x5(); 
                        double e5x5_2  = el2->full5x5_e5x5(); 
                        e1x5overE5x5_1 = e5x5_1!=0 ? el1->full5x5_e1x5()/e5x5_1    : 0; 
                        e1x5overE5x5_2 = e5x5_2!=0 ? el2->full5x5_e1x5()/e5x5_2    : 0; 
                        e2x5overE5x5_1 = e5x5_1!=0 ? el1->full5x5_e2x5Max()/e5x5_1 : 0; 
                        e2x5overE5x5_2 = e5x5_2!=0 ? el2->full5x5_e2x5Max()/e5x5_2 : 0; 
                        // more electron ID variables
                        dEtaIn1        = el1->deltaEtaSuperClusterTrackAtVtx();
                        dEtaIn2        = el2->deltaEtaSuperClusterTrackAtVtx();
                        dPhiIn1        = el1->deltaPhiSuperClusterTrackAtVtx();
                        dPhiIn2        = el2->deltaPhiSuperClusterTrackAtVtx();
                        dEtaSeed1      = el1->deltaEtaSeedClusterTrackAtVtx();
                        dEtaSeed2      = el2->deltaEtaSeedClusterTrackAtVtx();
                        hOverE1        = el1->hadronicOverEm();
                        hOverE2        = el2->hadronicOverEm();
                        ooEmooP1       = el1->ecalEnergy() && std::isfinite(el1->ecalEnergy()) ? 
                                         fabs(1.0/el1->ecalEnergy() - el1->eSuperClusterOverP()/el1->ecalEnergy() ) : 1e9;
                        ooEmooP2       = el2->ecalEnergy() && std::isfinite(el2->ecalEnergy()) ? 
                                         fabs(1.0/el2->ecalEnergy() - el2->eSuperClusterOverP()/el2->ecalEnergy() ) : 1e9;
                        ecalDriven1    = el1->ecalDriven();
                        ecalDriven2    = el2->ecalDriven();
                        passConVeto1   = el1->passConversionVeto();
                        passConVeto2   = el2->passConversionVeto();
                        if (el1->gsfTrack().isNonnull() && 
                            el2->gsfTrack().isNonnull()    ){
                            d01          = (-1)*el1->gsfTrack()->dxy(vertex.position());   
                            d02          = (-1)*el2->gsfTrack()->dxy(vertex.position());  
                            dz1          = el1->gsfTrack()->dz(vertex.position());
                            dz2          = el2->gsfTrack()->dz(vertex.position());
                            missingHits1 = el1->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                            missingHits2 = el2->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                        }
                   }
                   break;}
               case VW_CHANNEL:{
                   const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
                   //*****************DEFINITIONS *************************************
                   //candidate
                   candMass  = graviton.mass();
                   //leptons
                   ptVlep = leptonicV.pt();
                   yVlep  = leptonicV.eta();
                   phiVlep = leptonicV.phi();
                   massVlep = leptonicV.mass();
                   mtVlep  = leptonicV.mt();
                   ptlep1 = leptonicV.daughter(0)->pt();
                   etalep1 = leptonicV.daughter(0)->eta();
                   philep1 = leptonicV.daughter(0)->phi();
                   lep = abs(leptonicV.daughter(0)->pdgId());
                   //met
                   met = metCand.pt();
                   metPhi = metCand.phi();  
                   //hadrons
                   ptVhad = hadronicV.pt();
                   yVhad  = hadronicV.eta();
                   phiVhad = hadronicV.phi();
                   tau1 = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2 = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3 = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21 = tau2/tau1;
                   etjet1 = hadronicV.et();
                   ptjet1 = hadronicV.pt();
                   etajet1 = hadronicV.eta();
                   phijet1 = hadronicV.phi();
                   massjet1 = hadronicV.mass();
                   //deltas
                   deltaRleplep = deltaR(etalep1,philep1,etalep2,philep2);
                   double drl1j = deltaR(etalep1,philep1,etajet1,phijet1);
                   double drl2j = deltaR(etalep2,philep2,etajet1,phijet1);
                   deltaRlepjet = std::min(drl1j,drl2j);
                   delPhilepmet = deltaPhi(philep1, metPhi);
                   delPhijetmet = deltaPhi(phijet1, metPhi);
                   break;}
               case VZnu_CHANNEL:{
                   const pat::MET& goodMET =dynamic_cast<const pat::MET&> (*graviton.daughter("goodMET"));
                   //*************** DEFINITIONS ***************************************** 
                   //hadrons
                   ptVhad = hadronicV.pt();
                   yVhad  = hadronicV.eta();
                   phiVhad = hadronicV.phi();
                   tau1 = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2 = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3 = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21 = tau2/tau1;
                   ptjet1 = hadronicV.pt();
                   etajet1 = hadronicV.eta();
                   phijet1 = hadronicV.phi();
                   massjet1 = hadronicV.mass();                       
                   // MET FROM GRAVITON
                   metpt = goodMET.pt();
                   metphi = goodMET.phi();
                   // delta Phi between jet and met(from graviton) 
                   deltaphijetmet = deltaPhi(phijet1, metphi);
                   // transverse candidate mass for JET + MET
                   candTMass    = sqrt(abs(2*ptjet1*metpt*(1-cos(deltaphijetmet))));                     
                   break;}
               case VH_CHANNEL: // This channel needs to be implemented 
                   break;

           }// close switch


       }// close not isGen
       
       if(isGen_) {
	   massVhad = hadronicV.userFloat("ak8GenJetsSoftDropMass");
	   massVhadSD = massVhad;
	   nVtx = 0;
       }

       /// For data, all weights are equal to 1.
       triggerWeight = 1.0;
       pileupWeight  = 1.0;
       lumiWeight    = 1.0;
       if( !isData_ ) {
           // pileup reweight
           //Handle<std::vector< PileupSummaryInfo > >  puInfo;
           //iEvent.getByToken(puInfoToken, puInfo);
           //std::vector<PileupSummaryInfo>::const_iterator PVI;
           //for(PVI = puInfo->begin(); PVI != puInfo->end(); ++PVI) {
           //     int BX = PVI->getBunchCrossing();
           //     if( BX == 0 ){
           //          int  bin     = h1->FindBin(PVI->getTrueNumInteractions());
           //          pileupWeight = h1->GetBinContent(bin);
           //          continue;
           //     }
           //}
           // lumi weight
           double targetEvents = targetLumiInvPb_*crossSectionPb_;
           lumiWeight = targetEvents/originalNEvents_;
       }
       totalWeight = triggerWeight*pileupWeight*lumiWeight;

       // Enumarate regions
       enum {
           excluded = -1,
           lowerSB,
           lowerSIG,
           upperSIG,
           upperSB,
       }; 

       if( massVhad < 40. )
	   reg = excluded;
       if( massVhad > 40.  and  massVhad < 65.  )
	   reg = lowerSB;
       if( massVhad > 65.  and  massVhad < 105. )
	   reg = lowerSIG;
       if( massVhad > 105. and  massVhad < 135. )
	   reg = upperSIG;
       if( massVhad > 135. )
	   reg = upperSB;
   
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
     nVtx             = -1e4;
     triggerWeight    = -1e4;
     pileupWeight     = -1e4;
     lumiWeight       = -1e4;
     totalWeight      = -1e4;
     candMass         = -1e4;
     ptVlep           = -1e4;
     ptVhad           = -1e4;
     yVlep            = -1e4;
     yVhad            = -1e4;
     phiVlep          = -1e4;
     phiVhad          = -1e4;
     massVlep         = -1e4;
     massVhad         = -1e4;
     massVhadSD       = -1e4;
     mtVlep           = -1e4;
     tau1             = -1e4;
     tau2             = -1e4;
     tau3             = -1e4;
     tau21            = -1e4;
     ptlep1           = -1e4;
     ptlep2           = -1e4;
     etalep1          = -1e4;
     etalep2          = -1e4;
     philep1          = -1e4;
     philep2          = -1e4;
     charge1          = -1e4;
     charge2          = -1e4;
     pdgId1           = -1e4;
     pdgId2           = -1e4;
     miniIso1         = -1e4;
     miniIso2         = -1e4;
     nsubjets         = -1e4; 
     numjets          = -1e4; 
     etjet1           = -1e4;
     ptjet1           = -1e4;
     etajet1          = -1e4;
     phijet1          = -1e4;
     massjet1         = -1e4;
     softjet1         = -1e4;
     prunedjet1       = -1e4;
     rhojet1          = -1e4;
     nhfjet1          = -1e4;
     chfjet1          = -1e4;
     nemfjet1         = -1e4;
     cemfjet1         = -1e4;
     nmultjet1        = -1e4;
     cmultjet1        = -1e4;
     met              = -1e4;
     metPhi           = -1e4;
     metpt            = -1e4;
     metphi           = -1e4;
     matchHlt1        = -1e4;
     matchHlt2        = -1e4;
     deltaRlep1Obj    = -1e4;
     deltaRlep2Obj    = -1e4;
     deltaPtlep1Obj   = -1e4;
     deltaPtlep2Obj   = -1e4;
     deltaRleplep     = -1e4;
     deltaRlepjet     = -1e4;
     delPhilepmet     = -1e4;
     delPhijetmet     = -1e4;
     deltaphijetmet   = -1e4; 
     lep              = -1e4;
     reg              = -1e4;
     rho              = -1e4;
     barrel1          = -1e4;
     barrel2          = -1e4;
     endcap1          = -1e4;
     endcap2          = -1e4;
     eeDeltaR         = -1e4;
     etel1            = -1e4;
     ptel1            = -1e4;
     etaSC1           = -1e4;
     dEtaIn1          = -1e4;
     dPhiIn1          = -1e4;
     hOverE1          = -1e4;
     sigmaIEtaIEta1   = -1e4;
     e1x5overE5x5_1   = -1e4;
     e2x5overE5x5_1   = -1e4;
     ooEmooP1         = -1e4;
     d01              = -1e4;
     dz1              = -1e4;
     caloIso1         = -1e4;
     trackIso1        = -1e4;
     ecalDriven1      = -1e4;
     missingHits1     = -1e4; 
     passConVeto1     = -1e4;
     heepV601         = -1e4;
     modheep1         = -1e4;
     etel2            = -1e4;
     ptel2            = -1e4;
     etaSC2           = -1e4;
     dEtaIn2          = -1e4;
     dPhiIn2          = -1e4;
     hOverE2          = -1e4;
     sigmaIEtaIEta2   = -1e4;
     e1x5overE5x5_2   = -1e4;
     e2x5overE5x5_2   = -1e4;
     ooEmooP2         = -1e4;
     d02              = -1e4;
     dz2              = -1e4;
     caloIso2         = -1e4;
     trackIso2        = -1e4;
     ecalDriven2      = -1e4;
     missingHits2     = -1e4; 
     passConVeto2     = -1e4;
     heepV602         = -1e4; 
     modheep2         = -1e4; 
     trackerMu1       = -1e4;
     trackerMu2       = -1e4;
     highPtMu1        = -1e4;
     highPtMu2        = -1e4;
     isPFMu1          = -1e4;
     isPFMu2          = -1e4;
     isGlobalMu1      = -1e4;
     isGlobalMu2      = -1e4;
     isTrackerMu1     = -1e4;
     isTrackerMu2     = -1e4;
     matchedStations1 = -1e4;
     matchedStations2 = -1e4;
     pixelHits1       = -1e4;
     pixelHits2       = -1e4;
     trackerLayers1   = -1e4;
     trackerLayers2   = -1e4;
     relativeError1   = -1e4;
     relativeError2   = -1e4;
     dBCut1           = -1e4;
     dBCut2           = -1e4;
     longiCut1        = -1e4;
     longiCut2        = -1e4;
     relIsoR03_1      = -1e4;
     relIsoR03_2      = -1e4;
     relIsoR04_1      = -1e4;
     relIsoR04_2      = -1e4;
}

void EDBRTreeMaker::beginJob(){ 
     //if ( !isData_ ){
     //   f1 = new TFile( puWeights_.fullPath().c_str() );
     //   h1 = (TH1D*)f1->Get("pileupWeights");
     //}
}

void EDBRTreeMaker::endJob(){ }

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
