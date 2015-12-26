#include <iostream>

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
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


class TrigReportData : public edm::EDAnalyzer {
public:
  explicit TrigReportData(const edm::ParameterSet&);
  ~TrigReportData();
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  edm::EDGetTokenT<edm::TriggerResults> trigResult_;
  TTree *evTree;
  int run, lumisec, event;  
  int index;

};

TrigReportData::TrigReportData(const edm::ParameterSet& iConfig):
  trigResult_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("trigResult")))
{
  edm::Service<TFileService> fs;
  evTree = fs->make<TTree>("evTree", "basic event information");
  evTree->Branch("run",          &run,          "run/I");
  evTree->Branch("lumisec",      &lumisec,      "lumisec/I");
  evTree->Branch("event",        &event,        "event/I");
  evTree->Branch("index",        &index,        "index/I");
}

TrigReportData::~TrigReportData(){ }

void TrigReportData::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  run     = iEvent.eventAuxiliary().run();
  lumisec = iEvent.eventAuxiliary().luminosityBlock();
  event   = iEvent.eventAuxiliary().event();

  Handle<TriggerResults> trigRes;
  iEvent.getByToken(trigResult_, trigRes);
  index = trigRes->index(0);
  // fill Tree
  evTree->Fill();
}

void TrigReportData::beginJob() { }

void TrigReportData::endJob() { } 

DEFINE_FWK_MODULE(TrigReportData);
