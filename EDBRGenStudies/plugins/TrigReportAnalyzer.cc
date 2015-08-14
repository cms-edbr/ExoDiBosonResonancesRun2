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

  TH1I  *wfMu, *wfEl;
  TTree *genTree; 
  int run, lumisec, event;
  int lep, index;
  double ptZlep, ptZhad, deltaRleplep;
  double massGrav;

};

TrigReportAnalyzer::TrigReportAnalyzer(const edm::ParameterSet& iConfig):
  trigResult_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("trigResult"))), 
  leptonicZ_(iConfig.getParameter<edm::InputTag>("leptonicZ")),
  hadronicZ_(iConfig.getParameter<edm::InputTag>("hadronicZ"))
{
  edm::Service<TFileService> fs;
  wfMu = fs->make<TH1I>("wfMu","", 7, 0, 7);
  wfEl = fs->make<TH1I>("wfEl","", 7, 0, 7);
  TAxis *axisMu = wfMu->GetXaxis();  
  axisMu->SetBinLabel(1,"Begin");
  axisMu->SetBinLabel(2,"HLT");
  axisMu->SetBinLabel(3,"Vertex");
  axisMu->SetBinLabel(4,"Leptons");
  axisMu->SetBinLabel(5,"Dilepton");
  axisMu->SetBinLabel(6,"V-jet");
  axisMu->SetBinLabel(7,"Graviton");
  TAxis *axisEl = wfEl->GetXaxis();  
  axisEl->SetBinLabel(1,"Begin");
  axisEl->SetBinLabel(2,"HLT");
  axisEl->SetBinLabel(3,"Vertex");
  axisEl->SetBinLabel(4,"Leptons");
  axisEl->SetBinLabel(5,"Dilepton");
  axisEl->SetBinLabel(6,"V-jet");
  axisEl->SetBinLabel(7,"Graviton");

  genTree = fs->make<TTree>("genTree", "physical variables at GEN level");
  genTree->Branch("run",          &run,          "run/I");
  genTree->Branch("lumisec",      &lumisec,      "lumisec/I");
  genTree->Branch("event",        &event,        "event/I");
  genTree->Branch("lep",          &lep,          "lep/I");
  genTree->Branch("index",        &index,        "index/I");
  genTree->Branch("ptZlep",       &ptZlep,       "ptZlep/D");
  genTree->Branch("ptZhad",       &ptZhad,       "ptZhad/D");
  genTree->Branch("massGrav",     &massGrav,     "massGrav/D");
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
  if (index > 1){
     Handle<View<reco::Candidate> > genZlep;
     Handle<View<reco::Candidate> > genZhad;
     iEvent.getByLabel(leptonicZ_ , genZlep);
     iEvent.getByLabel(hadronicZ_ , genZhad);
     const reco::Candidate& Zlep = (*genZlep)[0];
     const reco::Candidate& Zhad = (*genZhad)[0];
     const reco::Candidate* genGrav = Zlep.mother(0);
     const reco::Candidate* lep1 = Zlep.daughter(0);
     const reco::Candidate* lep2 = Zlep.daughter(1);
     lep          = abs( lep1->pdgId() );
     ptZlep       = Zlep.pt() ;
     ptZhad       = Zhad.pt() ;
     massGrav     = genGrav->mass();
     deltaRleplep = deltaR(lep1->eta(),lep1->phi(),lep2->eta(),lep2->phi());
     // fill tree 
     genTree->Fill();
     // cut flow for muons
     if (lep==13){
        switch(index){
            case  2: wfMu->Fill("Begin",1); break;
            case  7: wfMu->Fill("Begin",1); wfMu->Fill("HLT",1); break;
            case 14: wfMu->Fill("Begin",1); wfMu->Fill("HLT",1); wfMu->Fill("Vertex",1); break;
            case 15: wfMu->Fill("Begin",1); wfMu->Fill("HLT",1); wfMu->Fill("Vertex",1); wfMu->Fill("Leptons",1); break;
            case 19: wfMu->Fill("Begin",1); wfMu->Fill("HLT",1); wfMu->Fill("Vertex",1); wfMu->Fill("Leptons",1); wfMu->Fill("Dilepton",1); break;
            case 21: wfMu->Fill("Begin",1); wfMu->Fill("HLT",1); wfMu->Fill("Vertex",1); wfMu->Fill("Leptons",1); wfMu->Fill("Dilepton",1); wfMu->Fill("V-jet",1); break;
            case 22: wfMu->Fill("Begin",1); wfMu->Fill("HLT",1); wfMu->Fill("Vertex",1); wfMu->Fill("Leptons",1); wfMu->Fill("Dilepton",1); wfMu->Fill("V-jet",1); wfMu->Fill("Graviton",1); break;
        }
     }
     // cut flow for electrons
     if (lep==11){
        switch(index){
            case  2: wfEl->Fill("Begin",1); break;
            case  7: wfEl->Fill("Begin",1); wfEl->Fill("HLT",1); break;
            case 14: wfEl->Fill("Begin",1); wfEl->Fill("HLT",1); wfEl->Fill("Vertex",1); break;
            case 15: wfEl->Fill("Begin",1); wfEl->Fill("HLT",1); wfEl->Fill("Vertex",1); wfEl->Fill("Leptons",1); break;
            case 19: wfEl->Fill("Begin",1); wfEl->Fill("HLT",1); wfEl->Fill("Vertex",1); wfEl->Fill("Leptons",1); wfEl->Fill("Dilepton",1); break;
            case 21: wfEl->Fill("Begin",1); wfEl->Fill("HLT",1); wfEl->Fill("Vertex",1); wfEl->Fill("Leptons",1); wfEl->Fill("Dilepton",1); wfEl->Fill("V-jet",1); break;
            case 22: wfEl->Fill("Begin",1); wfEl->Fill("HLT",1); wfEl->Fill("Vertex",1); wfEl->Fill("Leptons",1); wfEl->Fill("Dilepton",1); wfEl->Fill("V-jet",1); wfEl->Fill("Graviton",1); break;
        }
     }
   }
}

void TrigReportAnalyzer::beginJob() { }

void TrigReportAnalyzer::endJob() { } 

DEFINE_FWK_MODULE(TrigReportAnalyzer);
