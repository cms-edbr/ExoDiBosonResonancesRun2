#include <iostream>

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "TAxis.h"
#include "TH1.h"
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
  edm::InputTag leptonicZ_ , hadronicZ_ ; 

  TH1I  *cutFlow;
  TTree *genTree; 
  int lep, index;
  double ptZlep, ptZhad;
  double massGrav;

};

TrigReportAnalyzer::TrigReportAnalyzer(const edm::ParameterSet& iConfig):
  trigResult_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("trigResult"))), 
  leptonicZ_(iConfig.getParameter<edm::InputTag>("leptonicZ")),
  hadronicZ_(iConfig.getParameter<edm::InputTag>("hadronicZ"))
{
  edm::Service<TFileService> fs;
  cutFlow = fs->make<TH1I>("cutFlow","", 6, 0, 6);
  TAxis *axis = cutFlow->GetXaxis();  
  axis->SetBinLabel(1,"Begin");
  axis->SetBinLabel(2,"HLT");
  axis->SetBinLabel(3,"Vertex");
  axis->SetBinLabel(4,"LeptonicZ");
  axis->SetBinLabel(5,"HadronicZ");
  axis->SetBinLabel(6,"Graviton");

  genTree = fs->make<TTree>("genTree", "physical variables at GEN level");
  genTree->Branch("lep",      &lep,      "lep/I");
  genTree->Branch("index",    &index,    "index/I");
  genTree->Branch("ptZlep",   &ptZlep,   "ptZlep/D");
  genTree->Branch("ptZhad",   &ptZhad,   "ptZhad/D");
  genTree->Branch("massGrav", &massGrav, "massGrav/D");
}

TrigReportAnalyzer::~TrigReportAnalyzer(){ }

void TrigReportAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  Handle<TriggerResults> trigRes;
  iEvent.getByToken(trigResult_, trigRes);
  index = trigRes->index(0);
  switch(index){
      case  2: cutFlow->Fill("Begin",1); break;
      case  4: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); break;
      case 11: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); break;
      case 16: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); cutFlow->Fill("LeptonicZ",1); break;
      case 18: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); cutFlow->Fill("LeptonicZ",1); cutFlow->Fill("HadronicZ",1); break;
      case 19: cutFlow->Fill("Begin",1); cutFlow->Fill("HLT",1); cutFlow->Fill("Vertex",1); cutFlow->Fill("LeptonicZ",1); cutFlow->Fill("HadronicZ",1); cutFlow->Fill("Graviton",1); break;
  }
  // fill tree 
  if (index > 1){
     Handle<View<reco::Candidate> > genZlep;
     Handle<View<reco::Candidate> > genZhad;
     iEvent.getByLabel(leptonicZ_ , genZlep);
     iEvent.getByLabel(hadronicZ_ , genZhad);
     const reco::Candidate& Zlep = (*genZlep)[0];
     const reco::Candidate& Zhad = (*genZhad)[0];
     const reco::Candidate* genGrav = Zlep.mother(0);
     lep      = abs( Zlep.daughter(0)->pdgId() );
     ptZlep   = Zlep.pt() ;
     ptZhad   = Zhad.pt() ;
     massGrav = genGrav->mass();
     genTree->Fill();
  }
}

void TrigReportAnalyzer::beginJob() { }

void TrigReportAnalyzer::endJob() { } 

DEFINE_FWK_MODULE(TrigReportAnalyzer);
