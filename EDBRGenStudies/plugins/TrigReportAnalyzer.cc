#include <iostream>

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "TTree.h"


class TrigReportAnalyzer : public edm::EDAnalyzer {
public:
  explicit TrigReportAnalyzer(const edm::ParameterSet&);
  ~TrigReportAnalyzer();
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  edm::EDGetTokenT<edm::TriggerResults> trigResult_;
  edm::EDGetTokenT<reco::CandidateCollection> leptonicZ_; 
  edm::EDGetTokenT<reco::CandidateCollection> hadronicZ_; 

  TTree *genTree; 
  int    run,      lumisec,   event;
  int    lep,      index;
  double ptZlep,   ptZhad; 
  double massZlep, massZhad; 
  double massGrav;
  double deltaRleplep;
 
};

TrigReportAnalyzer::TrigReportAnalyzer(const edm::ParameterSet& iConfig):
  trigResult_(consumes<edm::TriggerResults>(       iConfig.getParameter<edm::InputTag>("trigResult"))), 
  leptonicZ_( consumes<reco::CandidateCollection>( iConfig.getParameter<edm::InputTag>("leptonicZ" ))),
  hadronicZ_( consumes<reco::CandidateCollection>( iConfig.getParameter<edm::InputTag>("hadronicZ" )))
{
  edm::Service<TFileService> fs;
  genTree = fs->make<TTree>("genTree", "physical variables at GEN level");
  genTree->Branch("run",          &run,          "run/I"         );
  genTree->Branch("lumisec",      &lumisec,      "lumisec/I"     );
  genTree->Branch("event",        &event,        "event/I"       );
  genTree->Branch("lep",          &lep,          "lep/I"         );
  genTree->Branch("index",        &index,        "index/I"       );
  genTree->Branch("ptZlep",       &ptZlep,       "ptZlep/D"      );
  genTree->Branch("ptZhad",       &ptZhad,       "ptZhad/D"      );
  genTree->Branch("massZlep",     &massZlep,     "massZlep/D"    );
  genTree->Branch("massZhad",     &massZhad,     "massZhad/D"    );
  genTree->Branch("massGrav",     &massGrav,     "massGrav/D"    );
  genTree->Branch("deltaRleplep", &deltaRleplep, "deltaRleplep/D");
}

TrigReportAnalyzer::~TrigReportAnalyzer(){ }

void TrigReportAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  run     = iEvent.eventAuxiliary().run();
  lumisec = iEvent.eventAuxiliary().luminosityBlock();
  event   = iEvent.eventAuxiliary().event();

  Handle<TriggerResults> trigRes;
  iEvent.getByToken(trigResult_, trigRes);
  index = trigRes->index(0);
  if ( index==0 ) return; // If there is not genZlep, skip event
  Handle< reco::CandidateCollection > genZlep;
  iEvent.getByToken(leptonicZ_ ,      genZlep);
  const reco::Candidate& Zlep = (*genZlep)[0];
  const reco::Candidate* genGrav = Zlep.mother(0);
  const reco::Candidate* lep1 = Zlep.daughter(0);
  const reco::Candidate* lep2 = Zlep.daughter(1);
  lep          = abs( lep1->pdgId() );
  ptZlep       = Zlep.pt();
  massZlep     = Zlep.mass();
  massGrav     = genGrav->mass();
  deltaRleplep = deltaR(lep1->eta(),lep1->phi(),lep2->eta(),lep2->phi());
  if (index>19 ){
      Handle< reco::CandidateCollection > genZhad;
      iEvent.getByToken(leptonicZ_ ,      genZhad);
      const reco::Candidate& Zhad = (*genZhad)[0];
      ptZhad   = Zhad.pt();
      massZhad = Zhad.mass();
  }
  else {
      ptZhad   = -1e4;
      massZhad = -1e4;
  }
  // fill tree 
  genTree->Fill();
}

void TrigReportAnalyzer::beginJob() { }

void TrigReportAnalyzer::endJob() { } 

DEFINE_FWK_MODULE(TrigReportAnalyzer);
