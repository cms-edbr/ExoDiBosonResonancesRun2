// system include files
#include <iostream>
#include <memory>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
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

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"

#include "PhysicsTools/PatAlgos/plugins/JetCorrFactorsProducer.h"

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
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

//******************************************************************
//************************* MEMBER DATA ****************************
//******************************************************************

  // Parameters to steer the treeDumper
  bool isGen_;
  bool isData_;
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  std::string gravitonSrc_, metSrc_;
  edm::EDGetTokenT<reco::VertexCollection> vertexToken_;

  //------------------------ GENERAL ----------------------------------------------
  int nVtx;
  int numCands;
  int nevent, run, lumisec;
  int channel, lep, reg;
  double triggerWeight, lumiWeight, pileupWeight;

  //------------------------ V quantities ------------------------------------------
  double ptVlep, ptVhad, yVlep, yVhad, phiVlep, phiVhad, massVlep, massVhad, mtVlep;

  //------------------------- MET ---------------------------------------------------
  double met, metPhi;

  //-----------------------MET FROM GRAVITON ----------------------------------------
  double metpt, metphi;

  //---------------------- JETS ------------------------------------------------------
  int    numjets;
  double tau1,      tau2,     tau3,       tau21;
  double etjet1,    ptjet1,   etajet1,    phijet1;
  double massjet1,  softjet1, prunedjet1;
  double nhfjet1,   chfjet1;       // neutral and charged hadron energy fraction
  double nemfjet1,  cemfjet1;      // neutral and charged EM fraction
  int    nmultjet1, cmultjet1;     // neutral and charged multiplicity

  //Recipe to apply JEC to the pruned jet mass:
  //https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging#Recipes_to_apply_JEC_on_the_prun
  std::string payload_;
  double prunedMassCorrection( double, double, const pat::Jet&, edm::ESHandle<JetCorrectorParametersCollection> ); 

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
  int    heepV601,       heepV602;
  int    modheep1,       modheep2;
  int    ecalDriven1,    ecalDriven2;
  int    missingHits1,   missingHits2;
  int    passConVeto1,   passConVeto2;

  // Muon ID 
  int    highPtMu1,      highPtMu2;
  int    trackerMu1,     trackerMu2;

  void setDummyValues();

  edm::Service<TFileService> fs;
  TTree* outTree_;

};

EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig):
  isGen_             (                                   iConfig.getParameter<bool>          ( "isGen"                ) ),
  isData_            (                                   iConfig.getParameter<bool>          ( "isData"               ) ),
  originalNEvents_   (                                   iConfig.getParameter<int>           ( "originalNEvents"      ) ),
  crossSectionPb_    (                                   iConfig.getParameter<double>        ( "crossSectionPb"       ) ),
  targetLumiInvPb_   (                                   iConfig.getParameter<double>        ( "targetLumiInvPb"      ) ),
  EDBRChannel_       (                                   iConfig.getParameter<std::string>   ( "EDBRChannel"          ) ),
  gravitonSrc_       (                                   iConfig.getParameter<std::string>   ( "gravitonSrc"          ) ),
  metSrc_            (                                   iConfig.getParameter<std::string>   ( "metSrc"               ) ),
  vertexToken_       ( consumes<reco::VertexCollection>( iConfig.getParameter<edm::InputTag> ( "vertex"             ) ) ),
  payload_           (                                   iConfig.getParameter<std::string>   ( "payload"              ) )
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

  outTree_ = fs->make<TTree>("EDBRCandidates","EDBR Candidates");

  // Basic event quantities
  outTree_->Branch("event"           ,&nevent         ,"event/I"          );
  outTree_->Branch("run"             ,&run            ,"run/I"            );
  outTree_->Branch("lumisec"         ,&lumisec        ,"lumisec/I"        );
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

  // HLT info 
  outTree_->Branch("elhltbit"        ,&elhltbit       ,"elhltbit/I"       );
  outTree_->Branch("muhltbit"        ,&muhltbit       ,"muhltbit/I"       );
  outTree_->Branch("matchHlt1"       ,&matchHlt1      ,"matchHlt1/I"      );
  outTree_->Branch("matchHlt2"       ,&matchHlt2      ,"matchHlt2/I"      );
  outTree_->Branch("deltaRlep1Obj"   ,&deltaRlep1Obj  ,"deltaRlep1Obj/D"  );
  outTree_->Branch("deltaRlep2Obj"   ,&deltaRlep2Obj  ,"deltaRlep2Obj/D"  );
  outTree_->Branch("deltaPtlep1Obj"  ,&deltaPtlep1Obj ,"deltaPtlep1Obj/D" );
  outTree_->Branch("deltaPtlep2Obj"  ,&deltaPtlep2Obj ,"deltaPtlep2Obj/D" );
 
  // Muon ID quantities
  outTree_->Branch("trackerMu1"      ,&trackerMu1     ,"trackerMu1/I"     );
  outTree_->Branch("trackerMu2"      ,&trackerMu2     ,"trackerMu2/I"     );
  outTree_->Branch("highPtMu1"       ,&highPtMu1      ,"highPtMu1/I"      );
  outTree_->Branch("highPtMu2"       ,&highPtMu2      ,"highPtMu2/I"      );

  // Electron ID quantities
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
  outTree_->Branch("heepV601"        ,&heepV601       ,"heepV601/I"       );
  outTree_->Branch("heepV602"        ,&heepV602       ,"heepV602/I"       );
  outTree_->Branch("modheep1"        ,&modheep1       ,"modheep1/I"       );
  outTree_->Branch("modheep2"        ,&modheep2       ,"modheep2/I"       );

  // mini isolation for leptons
  outTree_->Branch("miniIso1"        ,&miniIso1       ,"miniIso1/D"       );
  outTree_->Branch("miniIso2"        ,&miniIso2       ,"miniIso2/D"       );
  
  // Jet ID quantities
  outTree_->Branch("nhfjet1"         ,&nhfjet1        ,"nhfjet1/D"        );
  outTree_->Branch("chfjet1"         ,&chfjet1        ,"chfjet1/D"        );
  outTree_->Branch("nemfjet1"        ,&nemfjet1       ,"nemfjet1/D"       );
  outTree_->Branch("cemfjet1"        ,&cemfjet1       ,"cemfjet1/D"       );
  outTree_->Branch("nmultjet1"       ,&nmultjet1      ,"nmultjet1/I"      );
  outTree_->Branch("cmultjet1"       ,&cmultjet1      ,"cmultjet1/I"      );

  // Generic kinematic quantities
  outTree_->Branch("numjets"         ,&numjets        ,"numjets/I"        );
  outTree_->Branch("ptlep1"          ,&ptlep1         ,"ptlep1/D"         );
  outTree_->Branch("ptlep2"          ,&ptlep2         ,"ptlep2/D"         );
  outTree_->Branch("ptjet1"          ,&ptjet1         ,"ptjet1/D"         );
  outTree_->Branch("etjet1"          ,&etjet1         ,"etjet1/D"         );
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

  // Other quantities
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

   nevent  = iEvent.eventAuxiliary().event();
   run     = iEvent.eventAuxiliary().run();
   lumisec = iEvent.eventAuxiliary().luminosityBlock();

   setDummyValues(); //Initalize variables with dummy values

   Handle<View<reco::Candidate> > gravitons;
   iEvent.getByLabel(gravitonSrc_.c_str(), gravitons);
   numCands = gravitons->size();
   if(numCands != 0 ) {
       const reco::Candidate& graviton  = gravitons->at(0);
       const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));

       // met
       Handle<View<reco::Candidate> > metHandle;
       iEvent.getByLabel(metSrc_.c_str(), metHandle);
       const reco::Candidate& metCand = metHandle->at(0);
       
       // All the quantities which depend on RECO could go here
       if(not isGen_) {
           // electrons and muons
           Handle<View<pat::Electron> > electrons;
           Handle<View<pat::Muon> >     muons;
           iEvent.getByLabel("slimmedElectrons", electrons);
           iEvent.getByLabel("slimmedMuons",     muons);

           // number of jets
           Handle<std::vector<pat::Jet>> jets;
           iEvent.getByLabel("slimmedJetsAK8", jets);
           numjets = jets->size();
           met     = metCand.pt();
           metPhi  = metCand.phi();

           // handle goodOfflinePrimaryVertex collection
           Handle<reco::VertexCollection> vertices;
           iEvent.getByToken(vertexToken_, vertices);
           nVtx = vertices->size();
           const reco::Vertex& vertex = (*vertices)[0];
  
           // Effective area constants
           EffectiveAreas _effectiveAreas( FileInPath("RecoEgamma/ElectronIdentification/data/Spring15/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_50ns.txt").fullPath() );
           
           // Energy density
           Handle< double > rhoHandle;
           iEvent.getByLabel("fixedGridRhoFastjetAll", rhoHandle);
           rho = (float)(*rhoHandle);

           // Jet Energy Corrections
           edm::ESHandle<JetCorrectorParametersCollection>  JetCorParColl;
           iSetup.get<JetCorrectionsRecord>().get(payload_, JetCorParColl); 
 
           //we put the definitions inside the channel
           switch(channel){
               case VZ_CHANNEL:{
                   // ------ analize trigger results ----------//
                   Handle<bool> elHlt_handle;
                   Handle<bool> muHlt_handle;
                   Handle<ValueMap<bool> > matchHlt_handle;
                   Handle<ValueMap<float> > deltaPt_handle;
                   Handle<ValueMap<float> >  deltaR_handle;
                   iEvent.getByLabel(InputTag("hltMatchingElectrons","trigBit"), elHlt_handle);
                   iEvent.getByLabel(InputTag("hltMatchingMuons",    "trigBit"), muHlt_handle);
                   elhltbit = (int)(*elHlt_handle);
                   muhltbit = (int)(*muHlt_handle);

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
                   ptlep1         = leptonicV.daughter(0)->pt();
                   ptlep2         = leptonicV.daughter(1)->pt();
                   etalep1        = leptonicV.daughter(0)->eta();
                   etalep2        = leptonicV.daughter(1)->eta();
                   philep1        = leptonicV.daughter(0)->phi();
                   philep2        = leptonicV.daughter(1)->phi();
                   lep        = abs(leptonicV.daughter(0)->pdgId());
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
                   massVhad       = prunedjet1 * prunedMassCorrection( rho, nVtx, hadronicV, JetCorParColl );
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
                        const pat::Muon *mu1 = (pat::Muon*)leptonicV.daughter(0);
                        const pat::Muon *mu2 = (pat::Muon*)leptonicV.daughter(1);
                        const Ptr<pat::Muon> mu1Ptr(muons, mu1->userInt("slimmedIndex") );
                        const Ptr<pat::Muon> mu2Ptr(muons, mu2->userInt("slimmedIndex") );
                        iEvent.getByLabel(InputTag("hltMatchingMuons","deltaR"),   deltaR_handle);
                        iEvent.getByLabel(InputTag("hltMatchingMuons","deltaPt"),  deltaPt_handle);
                        iEvent.getByLabel(InputTag("hltMatchingMuons","matchHlt"), matchHlt_handle);
                        deltaRlep1Obj  =      (*deltaR_handle)[mu1Ptr];
                        deltaRlep2Obj  =      (*deltaR_handle)[mu2Ptr];
                        deltaPtlep1Obj =      (*deltaPt_handle)[mu1Ptr];
                        deltaPtlep2Obj =      (*deltaPt_handle)[mu2Ptr];
                        matchHlt1      = (int)(*matchHlt_handle)[mu1Ptr]; 
                        matchHlt2      = (int)(*matchHlt_handle)[mu2Ptr]; 
                        reco::MuonPFIsolation pfIso1  = mu1->pfIsolationR03();
                        reco::MuonPFIsolation pfIso2  = mu2->pfIsolationR03();
                        // isolation with delta beta correction
                        double absiso1 =  pfIso1.sumChargedHadronPt + std::max(0.0,  pfIso1.sumNeutralHadronEt +  pfIso1.sumPhotonEt -  0.5*pfIso1.sumPUPt );
                        double absiso2 =  pfIso2.sumChargedHadronPt + std::max(0.0,  pfIso2.sumNeutralHadronEt +  pfIso2.sumPhotonEt -  0.5*pfIso2.sumPUPt );
                        relIso1        = absiso1/mu1->pt();
                        relIso2        = absiso2/mu2->pt();
                        trackerMu1     = mu1->userInt("isTracker");
                        trackerMu2     = mu2->userInt("isTracker");
                        highPtMu1      = mu1->userInt("isHighPt");
                        highPtMu2      = mu2->userInt("isHighPt");
                        // retrieve mini isolation
                        miniIso1       = mu1->userFloat("miniIso");
                        miniIso2       = mu2->userFloat("miniIso");
                   }
                   //*****************************************************************//
                   //************************* ID for electrons **********************//
                   //*****************************************************************//
                   else if ( leptonicV.daughter(0)->isElectron() && 
                             leptonicV.daughter(1)->isElectron()    ) {
                        const pat::Electron *el1 = (pat::Electron*)leptonicV.daughter(0);
                        const pat::Electron *el2 = (pat::Electron*)leptonicV.daughter(1);
                        const Ptr<pat::Electron> el1Ptr(electrons, el1->userInt("slimmedIndex") );
                        const Ptr<pat::Electron> el2Ptr(electrons, el2->userInt("slimmedIndex") );
                        iEvent.getByLabel(InputTag("hltMatchingElectrons","deltaR"),   deltaR_handle);
                        iEvent.getByLabel(InputTag("hltMatchingElectrons","deltaPt"),  deltaPt_handle);
                        iEvent.getByLabel(InputTag("hltMatchingElectrons","matchHlt"), matchHlt_handle);
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
	   nVtx = 0;
       }

       /// For the time being, set these to 1
       triggerWeight=1.0;
       pileupWeight=1.0;

       double targetEvents = targetLumiInvPb_*crossSectionPb_;
       lumiWeight = targetEvents/originalNEvents_;

       /// FIXME: these should NOT be hardcoded
       if(massVhad < 40 or massVhad > 95)
	   reg = -1;
       if(massVhad > 40 and massVhad < 60)
	   reg = 0;
       if(massVhad > 60 and massVhad < 95)
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

double EDBRTreeMaker::prunedMassCorrection( double rho,
                                            double nVtx,
                                            const pat::Jet& jet, 
                                            edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl ) {
     std::vector<std::string> jecAK8PayloadNames;
     jecAK8PayloadNames.push_back("L2Relative");
     jecAK8PayloadNames.push_back("L3Absolute");
     if(isData_)
     jecAK8PayloadNames.push_back("L2L3Residual");
     std::vector<JetCorrectorParameters> vPar;
     for ( std::vector<std::string>::const_iterator payloadBegin = jecAK8PayloadNames.begin(), 
                                                    payloadEnd   = jecAK8PayloadNames.end()  , 
                                                    ipayload     = payloadBegin; 
                                                    ipayload    != payloadEnd; 
                                                  ++ipayload )  vPar.push_back( (*JetCorParColl)[*ipayload] );
     // Make the FactorizedJetCorrector
     std::shared_ptr<FactorizedJetCorrector> jecAK8 = std::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) ); 
     jecAK8->setRho   ( rho                         );
     jecAK8->setNPV   ( nVtx                        );
     jecAK8->setJetA  ( jet.jetArea()               );
     jecAK8->setJetPt ( jet.correctedP4(0).pt()     );
     jecAK8->setJetEta( jet.correctedP4(0).eta()    );
     jecAK8->setJetE  ( jet.correctedP4(0).energy() );
     return jecAK8->getCorrection();
}

void EDBRTreeMaker::setDummyValues() {
     nVtx           = -1e4;
     triggerWeight  = -1e4;
     pileupWeight   = -1e4;
     lumiWeight     = -1e4;
     candMass       = -1e4;
     ptVlep         = -1e4;
     ptVhad         = -1e4;
     yVlep          = -1e4;
     yVhad          = -1e4;
     phiVlep        = -1e4;
     phiVhad        = -1e4;
     massVlep       = -1e4;
     massVhad       = -1e4;
     mtVlep         = -1e4;
     tau1           = -1e4;
     tau2           = -1e4;
     tau3           = -1e4;
     tau21          = -1e4;
     ptlep1         = -1e4;
     ptlep2         = -1e4;
     etalep1        = -1e4;
     etalep2        = -1e4;
     philep1        = -1e4;
     philep2        = -1e4;
     miniIso1       = -1e4;
     miniIso2       = -1e4;
     numjets        = -1e4; 
     etjet1         = -1e4;
     ptjet1         = -1e4;
     etajet1        = -1e4;
     phijet1        = -1e4;
     massjet1       = -1e4;
     softjet1       = -1e4;
     prunedjet1     = -1e4;
     nhfjet1        = -1e4;
     chfjet1        = -1e4;
     nemfjet1       = -1e4;
     cemfjet1       = -1e4;
     nmultjet1      = -1e4;
     cmultjet1      = -1e4;
     met            = -1e4;
     metPhi         = -1e4;
     metpt          = -1e4;
     metphi         = -1e4;
     matchHlt1      = -1e4;
     matchHlt2      = -1e4;
     deltaRlep1Obj  = -1e4;
     deltaRlep2Obj  = -1e4;
     deltaPtlep1Obj = -1e4;
     deltaPtlep2Obj = -1e4;
     deltaRleplep   = -1e4;
     deltaRlepjet   = -1e4;
     delPhilepmet   = -1e4;
     delPhijetmet   = -1e4;
     deltaphijetmet = -1e4; 
     lep            = -1e4;
     reg            = -1e4;
     rho            = -1e4;
     barrel1        = -1e4;
     barrel2        = -1e4;
     endcap1        = -1e4;
     endcap2        = -1e4;
     eeDeltaR       = -1e4;
     etel1          = -1e4;
     ptel1          = -1e4;
     etaSC1         = -1e4;
     dEtaIn1        = -1e4;
     dPhiIn1        = -1e4;
     hOverE1        = -1e4;
     sigmaIEtaIEta1 = -1e4;
     e1x5overE5x5_1 = -1e4;
     e2x5overE5x5_1 = -1e4;
     ooEmooP1       = -1e4;
     d01            = -1e4;
     dz1            = -1e4;
     relIso1        = -1e4;
     caloIso1       = -1e4;
     trackIso1      = -1e4;
     ecalDriven1    = -1e4;
     missingHits1   = -1e4; 
     passConVeto1   = -1e4;
     heepV601       = -1e4;
     modheep1       = -1e4;
     etel2          = -1e4;
     ptel2          = -1e4;
     etaSC2         = -1e4;
     dEtaIn2        = -1e4;
     dPhiIn2        = -1e4;
     hOverE2        = -1e4;
     sigmaIEtaIEta2 = -1e4;
     e1x5overE5x5_2 = -1e4;
     e2x5overE5x5_2 = -1e4;
     ooEmooP2       = -1e4;
     d02            = -1e4;
     dz2            = -1e4;
     relIso2        = -1e4;
     caloIso2       = -1e4;
     trackIso2      = -1e4;
     ecalDriven2    = -1e4;
     missingHits2   = -1e4; 
     passConVeto2   = -1e4;
     heepV602       = -1e4; 
     modheep2       = -1e4; 
     trackerMu1     = -1e4;
     trackerMu2     = -1e4;
     highPtMu1      = -1e4;
     highPtMu2      = -1e4;
}

void EDBRTreeMaker::beginJob(){ }

void EDBRTreeMaker::endJob(){ }

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
