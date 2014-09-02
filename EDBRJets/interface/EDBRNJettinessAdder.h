#ifndef EDBRNJettinessAdder_h
#define EDBRNJettinessAdder_h

#include <memory>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

class EDBRNJettinessAdder : public edm::EDProducer {
 public:
  explicit EDBRNJettinessAdder(const edm::ParameterSet& iConfig) :
  src_(iConfig.getParameter<edm::InputTag>("src")),
    src_token_(consumes<edm::View<pat::Jet>>(src_)),
    cone_(iConfig.getParameter<double>("cone"))
      {
        produces<std::vector<pat::Jet> >();
      }

  virtual ~EDBRNJettinessAdder() {}

  void produce(edm::Event & iEvent, const edm::EventSetup & iSetup) ;
  float getTau(int num,edm::Ptr<pat::Jet> object) const;

 private:
  edm::InputTag src_ ;
  edm::EDGetTokenT<edm::View<pat::Jet>> src_token_;
  double cone_ ;
};

#endif
