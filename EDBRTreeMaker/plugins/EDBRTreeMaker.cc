// system include files
#include <iostream>
#include <memory>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "ExoDiBosonResonances/EDBRLeptons/interface/TrackerMuonSelector.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

#include "EDBRChannels.h"
#include "TAxis.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TTree.h"

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

  virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
  virtual void endRun(const edm::Run&, const edm::EventSetup&) override;
  

//******************************************************************
//************************* MEMBER DATA ****************************
//******************************************************************
  edm::Service<TFileService> fs;
  TTree* outTree_;

  //------------------------ GENERAL ----------------------------------------------
  int nVtx;
  int numCands;
  int nevent, run, ls;
  int channel, lep, reg;
  double triggerWeight, lumiWeight, pileupWeight;

  //------------------------ V quantities ------------------------------------------
  double ptVlep, ptVhad, yVlep, yVhad, phiVlep, phiVhad, massVlep, massVhad, mtVlep;

  //------------------------- MET ---------------------------------------------------
  double met, metPhi;

  //-----------------------MET FROM GRAVITON ----------------------------------------
  double metpt, metphi;

  //---------------------- JETS ------------------------------------------------------
  int numjets;
  double tau1, tau2, tau3, tau21;
  double ptjet1,   etajet1,  phijet1;
  double massjet1, softjet1, prunedjet1;

  //-------------------- LEPTONS -----------------------------------------------------
  double ptlep1,   ptlep2;
  double etalep1,  etalep2;
  double philep1,  philep2;
  double miniIso1, miniIso2;

  //--------------------DELTAS ------------------------------------------------------- 
  double deltaRleplep, deltaRlepjet, delPhilepmet, delPhijetmet, deltaphijetmet;

  //-------------------CANDIDATES MASS -----------------------------------------------
  double candMass;
  double candTMass; // transverse mass

  /// Parameters to steer the treeDumper
  bool isGen_;
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  std::string gravitonSrc_, metSrc_;

  //High Level Trigger
  int    numhltObjs;
  int    elhltbit;
  int    muhltbit;
  double deltaRlep1Obj;
  double deltaRlep2Obj;
  HLTConfigProvider hltConfig;
  std::vector<float>  pthltObjs;
  std::vector<float> etahltObjs;
  std::vector<float> phihltObjs;
  std::vector<std::string> elPaths;
  std::vector<std::string> muPaths;
  std::vector<std::string> elPaths_;
  std::vector<std::string> muPaths_;
  edm::EDGetTokenT<edm::TriggerResults> hltToken_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> hltObjects_;

  // Vertex collection
  edm::EDGetTokenT<reco::VertexCollection> vertexToken_;

  // Electron ID 
  double d01,            d02;
  double dz1,            dz2;
  double etel1,          etel2;
  double ptel1,          ptel2;
  double etaSC1,         etaSC2;
  double dEtaIn1,        dEtaIn2;
  double dPhiIn1,        dPhiIn2;
  double hOverE1,        hOverE2;
  double relIso1,        relIso2;
  double caloIso1,       caloIso2;
  double ooEmooP1,       ooEmooP2;
  double trackIso1,      trackIso2;
  double dEtaSeed1,      dEtaSeed2; 
  double sigmaIEtaIEta1, sigmaIEtaIEta2;
  double e1x5overE5x5_1, e1x5overE5x5_2;
  double e2x5overE5x5_1, e2x5overE5x5_2;
  double rho; // energy density
  double eeDeltaR;
  int    barrel1,        barrel2;
  int    endcap1,        endcap2;
  int    heepV60ID1,     heepV60ID2;
  int    modheepID1,     modheepID2;
  int    eltightID1,     eltightID2;
  int    elmediumID1,    elmediumID2;
  int    ecalDriven1,    ecalDriven2;
  int    missingHits1,   missingHits2;
  int    passConVeto1,   passConVeto2;
  edm::EDGetTokenT<edm::ValueMap<bool> > heepV60IDToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > modheepIDToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > eltightIDToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > elmediumIDToken_;

  // Muon ID 
  int    muhighPtID1,    muhighPtID2;
  int    mutrackerID1,   mutrackerID2;

  void setDummyValues();
};

//
// constructors and destructor
//
EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig):
  isGen_          (                                                   iConfig.getParameter<bool>                    ( "isGen"           ) ),
  originalNEvents_(                                                   iConfig.getParameter<int>                     ( "originalNEvents" ) ),
  crossSectionPb_ (                                                   iConfig.getParameter<double>                  ( "crossSectionPb"  ) ),
  targetLumiInvPb_(                                                   iConfig.getParameter<double>                  ( "targetLumiInvPb" ) ),
  EDBRChannel_    (                                                   iConfig.getParameter<std::string>             ( "EDBRChannel"     ) ),
  gravitonSrc_    (                                                   iConfig.getParameter<std::string>             ( "gravitonSrc"     ) ),
  metSrc_         (                                                   iConfig.getParameter<std::string>             ( "metSrc"          ) ),
  elPaths_        (                                                   iConfig.getParameter<std::vector<std::string>>( "elPaths"         ) ),
  muPaths_        (                                                   iConfig.getParameter<std::vector<std::string>>( "muPaths"         ) ), 
  hltToken_       ( consumes<edm::TriggerResults>                   ( iConfig.getParameter<edm::InputTag>           ( "hltToken"      ) ) ),
  hltObjects_     ( consumes<pat::TriggerObjectStandAloneCollection>( iConfig.getParameter<edm::InputTag>           ( "hltObjects"    ) ) ),
  vertexToken_    ( consumes<reco::VertexCollection>                ( iConfig.getParameter<edm::InputTag>           ( "vertex"        ) ) ),
  heepV60IDToken_ ( consumes<edm::ValueMap<bool> >                  ( iConfig.getParameter<edm::InputTag>           ( "heepV60ID"     ) ) ),
  modheepIDToken_ ( consumes<edm::ValueMap<bool> >                  ( iConfig.getParameter<edm::InputTag>           ( "modheepID"     ) ) ),
  eltightIDToken_ ( consumes<edm::ValueMap<bool> >                  ( iConfig.getParameter<edm::InputTag>           ( "eltightID"     ) ) ),
  elmediumIDToken_( consumes<edm::ValueMap<bool> >                  ( iConfig.getParameter<edm::InputTag>           ( "elmediumID"    ) ) )
{
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
  
  //now do what ever initialization is needed
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
  outTree_->Branch("candTMass"       ,&candTMass      ,"candTMass/D"      );

  /// HLT bits
  outTree_->Branch("elhltbit"        ,&elhltbit       ,"elhltbit/I"       );
  outTree_->Branch("muhltbit"        ,&muhltbit       ,"muhltbit/I"       );
  
  /// HLT objets
  outTree_->Branch( "pthltObjs"      ,&pthltObjs                          );
  outTree_->Branch("etahltObjs"      ,&etahltObjs                         );
  outTree_->Branch("phihltObjs"      ,&phihltObjs                         );
  outTree_->Branch("numhltObjs"      ,&numhltObjs     ,"numhltObjs/I"     );
  outTree_->Branch("deltaRlep1Obj"   ,&deltaRlep1Obj  ,"deltaRlep1Obj/D"  );
  outTree_->Branch("deltaRlep2Obj"   ,&deltaRlep2Obj  ,"deltaRlep2Obj/D"  );
 
  /// Muon ID quantities ID quantities
  outTree_->Branch("mutrackerID1"    ,&mutrackerID1   ,"mutrackerID1/I"   );
  outTree_->Branch("mutrackerID2"    ,&mutrackerID2   ,"mutrackerID2/I"   );
  outTree_->Branch("muhighPtID1"     ,&muhighPtID1    ,"muhighPtID1/I"    );
  outTree_->Branch("muhighPtID2"     ,&muhighPtID2    ,"muhighPtID2/I"    );

  /// Electron ID quantities
  outTree_->Branch("barrel1"         ,&barrel1        ,"barrel1/I"        );
  outTree_->Branch("barrel2"         ,&barrel2        ,"barrel2/I"        );
  outTree_->Branch("endcap1"         ,&endcap1        ,"endcap1/I"        );
  outTree_->Branch("endcap2"         ,&endcap2        ,"endcap2/I"        );
  outTree_->Branch("eeDeltaR"        ,&eeDeltaR       ,"eeDeltaR/D"       );
  outTree_->Branch("etel1"           ,&etel1          ,"etel1/D"          );
  outTree_->Branch("etel2"           ,&etel2          ,"etel2/D"          );
  outTree_->Branch("ptel1"           ,&ptel1          ,"ptel1/D"          );
  outTree_->Branch("ptel2"           ,&ptel2          ,"ptel2/D"          );
  outTree_->Branch("etaSC1"          ,&etaSC1         ,"etaSC1/D"         );
  outTree_->Branch("etaSC2"          ,&etaSC2         ,"etaSC2/D"         );
  outTree_->Branch("dEtaIn1"         ,&dEtaIn1        ,"dEtaIn1/D"        );
  outTree_->Branch("dEtaIn2"         ,&dEtaIn2        ,"dEtaIn2/D"        );
  outTree_->Branch("dEtaSeed1"       ,&dEtaSeed1      ,"dEtaSeed1/D"      );
  outTree_->Branch("dEtaSeed2"       ,&dEtaSeed2      ,"dEtaSeed2/D"      );
  outTree_->Branch("dPhiIn1"         ,&dPhiIn1        ,"dPhiIn1/D"        );
  outTree_->Branch("dPhiIn2"         ,&dPhiIn2        ,"dPhiIn2/D"        );
  outTree_->Branch("hOverE1"         ,&hOverE1        ,"hOverE1/D"        );
  outTree_->Branch("hOverE2"         ,&hOverE2        ,"hOverE2/D"        );
  outTree_->Branch("sigmaIEtaIEta1"  ,&sigmaIEtaIEta1 ,"sigmaIEtaIEta1/D" );
  outTree_->Branch("sigmaIEtaIEta2"  ,&sigmaIEtaIEta2 ,"sigmaIEtaIEta2/D" );
  outTree_->Branch("e1x5overE5x5_1"  ,&e1x5overE5x5_1 ,"e1x5overE5x5_1/D" );
  outTree_->Branch("e1x5overE5x5_2"  ,&e1x5overE5x5_2 ,"e1x5overE5x5_2/D" );
  outTree_->Branch("e2x5overE5x5_1"  ,&e2x5overE5x5_1 ,"e2x5overE5x5_1/D" );
  outTree_->Branch("e2x5overE5x5_2"  ,&e2x5overE5x5_2 ,"e2x5overE5x5_2/D" );
  outTree_->Branch("ooEmooP1"        ,&ooEmooP1       ,"ooEmooP1/D"       );
  outTree_->Branch("ooEmooP2"        ,&ooEmooP2       ,"ooEmooP2/D"       );
  outTree_->Branch("d01"             ,&d01            ,"d01/D"            );
  outTree_->Branch("d02"             ,&d02            ,"d02/D"            );
  outTree_->Branch("dz1"             ,&dz1            ,"dz1/D"            );
  outTree_->Branch("dz2"             ,&dz2            ,"dz2/D"            );
  outTree_->Branch("relIso1"         ,&relIso1        ,"relIso1/D"        );
  outTree_->Branch("relIso2"         ,&relIso2        ,"relIso2/D"        );
  outTree_->Branch("caloIso1"        ,&caloIso1       ,"caloIso1/D"       );
  outTree_->Branch("caloIso2"        ,&caloIso2       ,"caloIso2/D"       );
  outTree_->Branch("trackIso1"       ,&trackIso1      ,"trackIso1/D"      );
  outTree_->Branch("trackIso2"       ,&trackIso2      ,"trackIso2/D"      );
  outTree_->Branch("rho"             ,&rho            ,"rho/D"            );
  outTree_->Branch("ecalDriven1"     ,&ecalDriven1    ,"ecalDriven1/I"    );
  outTree_->Branch("ecalDriven2"     ,&ecalDriven2    ,"ecalDriven2/I"    );
  outTree_->Branch("missingHits1"    ,&missingHits1   ,"missingHits1/I"   );
  outTree_->Branch("missingHits2"    ,&missingHits2   ,"missingHits2/I"   );
  outTree_->Branch("passConVeto1"    ,&passConVeto1   ,"passConVeto1/I"   );
  outTree_->Branch("passConVeto2"    ,&passConVeto2   ,"passConVeto2/I"   );
  outTree_->Branch("elmediumID1"     ,&elmediumID1    ,"elmediumID1/I"    );
  outTree_->Branch("elmediumID2"     ,&elmediumID2    ,"elmediumID2/I"    );
  outTree_->Branch("eltightID1"      ,&eltightID1     ,"eltightID1/I"     );
  outTree_->Branch("eltightID2"      ,&eltightID2     ,"eltightID2/I"     );
  outTree_->Branch("heepV60ID1"      ,&heepV60ID1     ,"heepV60ID1/I"     );
  outTree_->Branch("heepV60ID2"      ,&heepV60ID2     ,"heepV60ID2/I"     );
  outTree_->Branch("modheepID1"      ,&modheepID1     ,"modheepID1/I"     );
  outTree_->Branch("modheepID2"      ,&modheepID2     ,"modheepID2/I"     );

  // mini isolation for leptons
  outTree_->Branch("miniIso1"        ,&miniIso1       ,"miniIso1/D"       );
  outTree_->Branch("miniIso2"        ,&miniIso2       ,"miniIso2/D"       );
  
  /// Generic kinematic quantities
  outTree_->Branch("numjets"         ,&numjets        ,"numjets/I"        );
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
  outTree_->Branch("softjet1"        ,&softjet1       ,"softjet1/D"       );
  outTree_->Branch("prunedjet1"      ,&prunedjet1     ,"prunedjet1/D"     );
  outTree_->Branch("met"             ,&met            ,"met/D"            );
  outTree_->Branch("metpt"           ,&metpt          ,"metpt/D"          );
  outTree_->Branch("metPhi"          ,&metPhi         ,"metPhi/D"         );

  /// Other quantities
  outTree_->Branch("triggerWeight"   ,&triggerWeight  ,"triggerWeight/D"  );
  outTree_->Branch("lumiWeight"      ,&lumiWeight     ,"lumiWeight/D"     );
  outTree_->Branch("pileupWeight"    ,&pileupWeight   ,"pileupWeight/D"   );
  outTree_->Branch("deltaRleplep"    ,&deltaRleplep   ,"deltaRleplep/D"   );
  outTree_->Branch("delPhilepmet"    ,&delPhilepmet   ,"delPhilepmet/D"   );
  outTree_->Branch("deltaRlepjet"    ,&deltaRlepjet   ,"deltaRlepjet/D"   );
  outTree_->Branch("delPhijetmet"    ,&delPhijetmet   ,"delPhijetmet/D"   );
  outTree_->Branch("deltaphijetmet"  ,&deltaphijetmet ,"deltaphijetmet/D" );
}


EDBRTreeMaker::~EDBRTreeMaker() {}

// ------------ method called for each event  ------------
void
EDBRTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   nevent = iEvent.eventAuxiliary().event();
   run    = iEvent.eventAuxiliary().run();
   ls     = iEvent.eventAuxiliary().luminosityBlock();

   setDummyValues(); //Initalize variables with dummy values

   // ------ analize trigger results ----------//
   Handle<TriggerResults> trigRes;
   iEvent.getByToken(hltToken_, trigRes);
   elhltbit = (int)trigRes->accept(hltConfig.triggerIndex(elPaths[0]));
   muhltbit = (int)trigRes->accept(hltConfig.triggerIndex(muPaths[0]));
   // translate indices in names
   const TriggerNames &names = iEvent.triggerNames(*trigRes);
   // ------ handle trigger objects ----------//
   Handle<pat::TriggerObjectStandAloneCollection> hltObjects;
   iEvent.getByToken(hltObjects_, hltObjects);
   numhltObjs=0;
   for (pat::TriggerObjectStandAlone obj : *hltObjects) {
       obj.unpackPathNames(names);
       bool isElObj = obj.hasPathName(elPaths[0], true, true);
       bool isMuObj = obj.hasPathName(muPaths[0], true, true);
       if ( isElObj or isMuObj ) {
           pthltObjs.push_back(  obj.pt()  );
           etahltObjs.push_back( obj.eta() );
           phihltObjs.push_back( obj.phi() );
           numhltObjs++;
       }
   }

   Handle<View<reco::Candidate> > gravitons;
   iEvent.getByLabel(gravitonSrc_.c_str(), gravitons);
   numCands = gravitons->size();

   if(numCands != 0 ) {
       int G_index=0;
       for( int i=1; i<numCands; i++ ){
           // Pick index of the candidate with lowest pt
           int temp = gravitons->at(G_index).pt() < gravitons->at(i).pt() ? G_index : i ;
           G_index = temp;
       }
       const reco::Candidate& graviton  = gravitons->at(G_index);
       const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));

       // met
       Handle<View<reco::Candidate> > metHandle;
       iEvent.getByLabel(metSrc_.c_str(), metHandle);
       const reco::Candidate& metCand = metHandle->at(0);
       
       /// All the quantities which depend on RECO could go here
       if(not isGen_) {
           // number of jets
           Handle<std::vector<pat::Jet>> jets;
           iEvent.getByLabel("slimmedJetsAK8", jets);
           numjets = jets->size();

           // handle goodOfflinePrimaryVertex collection
           Handle<reco::VertexCollection> vertices;
           iEvent.getByToken(vertexToken_, vertices);
           const reco::Vertex& vertex = (*vertices)[0];
  
           // Effective area constants
           EffectiveAreas _effectiveAreas( FileInPath("RecoEgamma/ElectronIdentification/data/PHYS14/effAreaElectrons_cone03_pfNeuHadronsAndPhotons.txt").fullPath()  );
           // The rho
           Handle< double > rhoHandle;
           iEvent.getByLabel("fixedGridRhoFastjetAll", rhoHandle);
           rho = (float)(*rhoHandle);

           met = metCand.pt();
           metPhi = metCand.phi();
 
           //we put the definitions inside the channel
           switch(channel){
               case VZ_CHANNEL:{
                   const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
                   //**************DEFINITIONS *********************************** 
                   // candidate
                   candMass  = graviton.mass();
                   // leptons
                   ptVlep   = leptonicV.pt();
                   yVlep    = leptonicV.eta();
                   phiVlep  = leptonicV.phi();
                   massVlep = leptonicV.mass();
                   mtVlep   = leptonicV.mt();
                   ptlep1   = leptonicV.daughter(0)->pt();
                   ptlep2   = leptonicV.daughter(1)->pt();
                   etalep1  = leptonicV.daughter(0)->eta();
                   etalep2  = leptonicV.daughter(1)->eta();
                   philep1  = leptonicV.daughter(0)->phi();
                   philep2  = leptonicV.daughter(1)->phi();
                   lep  = abs(leptonicV.daughter(0)->pdgId());

                   // hlt matching
                   if ( numhltObjs ){
                       int closest1=0, closest2=0;
                       for(int i=1; i<numhltObjs; i++){
                           int temp1 = deltaR(etalep1,philep1,etahltObjs[closest1],phihltObjs[closest1])<
                                       deltaR(etalep1,philep1,etahltObjs[i],phihltObjs[i]) ? closest1 : i;
                           int temp2 = deltaR(etalep2,philep2,etahltObjs[closest2],phihltObjs[closest2])<
                                       deltaR(etalep2,philep2,etahltObjs[i],phihltObjs[i]) ? closest2 : i;
                           closest1  = temp1;
                           closest2  = temp2;
                       }
                       deltaRlep1Obj = deltaR(etalep1,philep1,etahltObjs[closest1],phihltObjs[closest1]);
                       deltaRlep2Obj = deltaR(etalep2,philep2,etahltObjs[closest2],phihltObjs[closest2]);
                   }

                   // hadrons
                   ptVhad       = hadronicV.pt();
                   yVhad        = hadronicV.eta();
                   phiVhad      = hadronicV.phi();
                   tau1         = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2         = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3         = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21        = tau2/tau1;
                   ptjet1       = hadronicV.pt();
                   etajet1      = hadronicV.eta();
                   phijet1      = hadronicV.phi();
                   massjet1     = hadronicV.mass();
                   softjet1     = hadronicV.userFloat("ak8PFJetsCHSSoftDropMass");
                   prunedjet1   = hadronicV.userFloat("ak8PFJetsCHSPrunedMass");
                   // deltas
                   deltaRleplep = deltaR(etalep1,philep1,etalep2,philep2);
                   double drl1j = deltaR(etalep1,philep1,etajet1,phijet1);
                   double drl2j = deltaR(etalep2,philep2,etajet1,phijet1);
                   deltaRlepjet = std::min(drl1j,drl2j);
                   delPhilepmet = deltaPhi(philep1, metPhi);
                   delPhijetmet = deltaPhi(phijet1, metPhi);
                   //*****************************************************************//
                   //************************* ID for muons **************************//
                   //*****************************************************************//
                   if ( leptonicV.daughter(0)->isMuon() && 
                        leptonicV.daughter(1)->isMuon()    ) {
                        const pat::Muon *mu1 = (pat::Muon*)leptonicV.daughter(0);
                        const pat::Muon *mu2 = (pat::Muon*)leptonicV.daughter(1);
                        reco::MuonPFIsolation pfIso1  = mu1->pfIsolationR03();
                        reco::MuonPFIsolation pfIso2  = mu2->pfIsolationR03();
                        // isolation with delta beta correction
                        double absiso1  =  pfIso1.sumChargedHadronPt + std::max(0.0,  pfIso1.sumNeutralHadronEt +  pfIso1.sumPhotonEt -  0.5*pfIso1.sumPUPt );
                        double absiso2  =  pfIso2.sumChargedHadronPt + std::max(0.0,  pfIso2.sumNeutralHadronEt +  pfIso2.sumPhotonEt -  0.5*pfIso2.sumPUPt );
                        relIso1         = absiso1 /mu1->pt();
                        relIso2         = absiso2 /mu2->pt();
                        mutrackerID1    = (int)hptm::isTrackerMuon(*mu1,vertex);
                        mutrackerID2    = (int)hptm::isTrackerMuon(*mu2,vertex);
                        muhighPtID1     = (int)muon::isHighPtMuon( *mu1,vertex);
                        muhighPtID2     = (int)muon::isHighPtMuon( *mu2,vertex);
                        // retrieve mini isolation
                        miniIso1        = mu1->userFloat("miniIso");
                        miniIso2        = mu2->userFloat("miniIso");
                   }
                   //*****************************************************************//
                   //************************* ID for electrons **********************//
                   //*****************************************************************//
                   if ( leptonicV.daughter(0)->isElectron() && 
                        leptonicV.daughter(1)->isElectron()    ) {
                        const pat::Electron *el1 = (pat::Electron*)leptonicV.daughter(0);
                        const pat::Electron *el2 = (pat::Electron*)leptonicV.daughter(1);
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
                        double     eA1 = _effectiveAreas.getEffectiveArea( etaSC1 );
                        double     eA2 = _effectiveAreas.getEffectiveArea( etaSC2 );
                        double absiso1 = pfIso1.sumChargedHadronPt + std::max(0.0, pfIso1.sumNeutralHadronEt + pfIso1.sumPhotonEt - rho*eA1 );
                        double absiso2 = pfIso2.sumChargedHadronPt + std::max(0.0, pfIso2.sumNeutralHadronEt + pfIso2.sumPhotonEt - rho*eA2 );
                        relIso1        = absiso1/el1->pt();
                        relIso2        = absiso2/el2->pt();
                        caloIso1       = el1->dr03EcalRecHitSumEt() + el1->dr03HcalDepth1TowerSumEt();
                        caloIso2       = el2->dr03EcalRecHitSumEt() + el2->dr03HcalDepth1TowerSumEt();
                        trackIso1      = el1->dr03TkSumPt();
                        trackIso2      = el2->dr03TkSumPt();
                        // retrieve mini isolation
                        miniIso1       = el1->userFloat("miniIso");
                        miniIso2       = el2->userFloat("miniIso");
                        // retrieve electron IDs
                        Handle<View<pat::Electron> > electrons;
                        iEvent.getByLabel("slimmedElectrons", electrons);
                        const Ptr<pat::Electron> el1Ptr(electrons, el1->userInt("slimmedIndex") );
                        const Ptr<pat::Electron> el2Ptr(electrons, el2->userInt("slimmedIndex") );
                        Handle<ValueMap<bool> >  elmediumID_handle;
                        Handle<ValueMap<bool> >  eltightID_handle;
                        Handle<ValueMap<bool> >  heepV60ID_handle;
                        Handle<ValueMap<bool> >  modheepID_handle;
                        iEvent.getByToken(elmediumIDToken_,  elmediumID_handle);
                        iEvent.getByToken(eltightIDToken_,   eltightID_handle);
                        iEvent.getByToken(heepV60IDToken_,    heepV60ID_handle);
                        iEvent.getByToken(modheepIDToken_,   modheepID_handle);
                        elmediumID1  = (*elmediumID_handle)[  el1Ptr ];
                        elmediumID2  = (*elmediumID_handle)[  el2Ptr ];
                        eltightID1   = (*eltightID_handle)[   el1Ptr ];
                        eltightID2   = (*eltightID_handle)[   el2Ptr ];
                        heepV60ID1   = (*heepV60ID_handle)[   el1Ptr ];
                        heepV60ID2   = (*heepV60ID_handle)[   el2Ptr ];
                        modheepID1   = (*modheepID_handle)[   el1Ptr ];
                        modheepID2   = (*modheepID_handle)[   el2Ptr ];
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
                            d01            = (-1)*el1->gsfTrack()->dxy(vertex.position());   
                            d02            = (-1)*el2->gsfTrack()->dxy(vertex.position());  
                            dz1            = el1->gsfTrack()->dz(vertex.position());
                            dz2            = el2->gsfTrack()->dz(vertex.position());
                            missingHits1   = el1->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                            missingHits2   = el2->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
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

           massVhad     = hadronicV.userFloat("ak8PFJetsCHSSoftDropMass");

       }// close not isGen
       
       if(isGen_) {
	   massVhad = hadronicV.userFloat("ak8GenJetsSoftDropMass");
	   nVtx = 0;
       }

       /// For the time being, set these to 1
       triggerWeight=1.0;
       pileupWeight=1.0;

       double targetEvents = targetLumiInvPb_*crossSectionPb_;
       lumiWeight = targetEvents/originalNEvents_;

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
     miniIso1       = -1e9;
     miniIso2       = -1e9;
     numjets        = -1e9; 
     ptjet1         = -1e9;
     etajet1        = -1e9;
     phijet1        = -1e9;
     massjet1       = -1e9;
     softjet1       = -1e9;
     prunedjet1     = -1e9;
     met            = -1e9;
     metPhi         = -1e9;
     metpt          = -1e9;
     metphi         = -1e9;
     deltaRlep1Obj  = -1e9;
     deltaRlep2Obj  = -1e9;
     deltaRleplep   = -1e9;
     deltaRlepjet   = -1e9;
     delPhilepmet   = -1e9;
     delPhijetmet   = -1e9;
     deltaphijetmet = -1e9; 
     lep            = -1e9;
     reg            = -1e9;
     rho            = -1e9;
     barrel1        = -1e9;
     barrel2        = -1e9;
     endcap1        = -1e9;
     endcap2        = -1e9;
     eeDeltaR       = -1e9;
     etel1          = -1e9;
     ptel1          = -1e9;
     etaSC1         = -1e9;
     dEtaIn1        = -1e9;
     dPhiIn1        = -1e9;
     hOverE1        = -1e9;
     sigmaIEtaIEta1 = -1e9;
     e1x5overE5x5_1 = -1e9;
     e2x5overE5x5_1 = -1e9;
     ooEmooP1       = -1e9;
     d01            = -1e9;
     dz1            = -1e9;
     relIso1        = -1e9;
     caloIso1       = -1e9;
     trackIso1      = -1e9;
     ecalDriven1    = -1e9;
     missingHits1   = -1e9; 
     passConVeto1   = -1e9;
     elmediumID1    = -1e9;
     eltightID1     = -1e9;
     heepV60ID1     = -1e9;
     modheepID1     = -1e9;
     etel2          = -1e9;
     ptel2          = -1e9;
     etaSC2         = -1e9;
     dEtaIn2        = -1e9;
     dPhiIn2        = -1e9;
     hOverE2        = -1e9;
     sigmaIEtaIEta2 = -1e9;
     e1x5overE5x5_2 = -1e9;
     e2x5overE5x5_2 = -1e9;
     ooEmooP2       = -1e9;
     d02            = -1e9;
     dz2            = -1e9;
     relIso2        = -1e9;
     caloIso2       = -1e9;
     trackIso2      = -1e9;
     ecalDriven2    = -1e9;
     missingHits2   = -1e9; 
     passConVeto2   = -1e9;
     elmediumID2    = -1e9; 
     eltightID2     = -1e9; 
     heepV60ID2     = -1e9; 
     modheepID2     = -1e9; 
     mutrackerID1   = -1e9;
     mutrackerID2   = -1e9;
     muhighPtID1    = -1e9;
     muhighPtID2    = -1e9;
     //clear vectors
      pthltObjs.clear();
     etahltObjs.clear();
     phihltObjs.clear();
}

// ------------ method called once each job just before starting event loop  ------------
void EDBRTreeMaker::beginJob()
{
}

void EDBRTreeMaker::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
   bool changed;
   if ( !hltConfig.init(iRun, iSetup, "HLT", changed) ) {
     edm::LogError("HltAnalysis") << "Initialization of HLTConfigProvider failed!!";
     return;
   }
   elPaths.clear(), muPaths.clear();
   for (size_t i = 0; i < elPaths_.size(); i++) {
      std::vector<std::string> foundPaths = hltConfig.matched( hltConfig.triggerNames(), elPaths_[i] );
      while ( !foundPaths.empty() ){
         elPaths.push_back( foundPaths.back() );
         foundPaths.pop_back();
      }
   }
   for (size_t i = 0; i < muPaths_.size(); i++) {
      std::vector<std::string> foundPaths = hltConfig.matched( hltConfig.triggerNames(), muPaths_[i] );
      while ( !foundPaths.empty() ){
         muPaths.push_back( foundPaths.back() );
         foundPaths.pop_back();
      }
   }

   std::cout<<"\n************** HLT Information **************\n";
   std::cout<<"\n Run number: " << iRun.run() << std::endl;
   for (size_t i=0; i < elPaths.size(); i++) std::cout << "\n Electron paths: " << elPaths[i].c_str() << std::endl;
   for (size_t i=0; i < muPaths.size(); i++) std::cout << "\n Muon paths    : " << muPaths[i].c_str() << std::endl;
   std::cout<<"\n*********************************************\n\n";

}

void EDBRTreeMaker::endRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void EDBRTreeMaker::endJob() {
  std::cout << "EDBRTreeMaker endJob()..." << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
