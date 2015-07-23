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

#include "TAxis.h"
#include "TH1.h"
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
  TH1I  *cutFlow;

};

TrigReportData::TrigReportData(const edm::ParameterSet& iConfig):
  trigResult_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("trigResult")))
{
  edm::Service<TFileService> fs;
  cutFlow = fs->make<TH1I>("cutFlow","", 7, 0, 7);
  TAxis *axis = cutFlow->GetXaxis();  
  axis->SetBinLabel(1,"Begin");
  axis->SetBinLabel(2,"HLT");
  axis->SetBinLabel(3,"Vertex");
  axis->SetBinLabel(4,"Leptons");
  axis->SetBinLabel(5,"Dilepton");
  axis->SetBinLabel(6,"V-jet");
  axis->SetBinLabel(7,"Graviton");
}

TrigReportData::~TrigReportData(){ }

void TrigReportData::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  Handle<TriggerResults> trigRes;
  iEvent.getByToken(trigResult_, trigRes);
  int index = trigRes->index(0);
  // cut flow 
  switch(index){
      case  0: cutFlow->Fill("Begin",1); break;
      case  3: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); break;
      case 10: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); break;
      case 11: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); cutFlow->Fill("Leptons",1); break;
      case 15: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); cutFlow->Fill("Leptons",1); cutFlow->Fill("Dilepton",1); break;
      case 17: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); cutFlow->Fill("Leptons",1); cutFlow->Fill("Dilepton",1); cutFlow->Fill("V-jet",1); break;
      case 18: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); cutFlow->Fill("Leptons",1); cutFlow->Fill("Dilepton",1); cutFlow->Fill("V-jet",1); cutFlow->Fill("Graviton",1); break;
  }
}

void TrigReportData::beginJob() { }

void TrigReportData::endJob() { } 

DEFINE_FWK_MODULE(TrigReportData);
