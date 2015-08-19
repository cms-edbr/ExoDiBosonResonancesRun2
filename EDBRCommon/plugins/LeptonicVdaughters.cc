// -*- C++ -*-
//
// Original Author:  Jose Cupertino Ruiz Vargas
//         Created:  Tue, 18 Aug 2015
//


// system include files
#include <memory>

// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

class LeptonicVdaughters : public edm::EDProducer {
   public:
      explicit LeptonicVdaughters(const edm::ParameterSet&);
      ~LeptonicVdaughters();

   private:
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      
      edm::EDGetTokenT<reco::CandidateCollection> collectionToken;
};

LeptonicVdaughters::LeptonicVdaughters(const edm::ParameterSet& iConfig):
    collectionToken( consumes<reco::CandidateCollection> ( iConfig.getParameter<edm::InputTag>("src") ) )
{
    produces<std::vector<pat::Electron> >("Electrons");
    produces<std::vector<pat::Muon> >(    "Muons"    );
}

LeptonicVdaughters::~LeptonicVdaughters() {}

void
LeptonicVdaughters::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    // output collections
    auto_ptr< vector<pat::Muon> >     Muons(     new vector<pat::Muon>     );
    auto_ptr< vector<pat::Electron> > Electrons( new vector<pat::Electron> );

    // LeptonicV
    Handle<reco::CandidateCollection>  leptonicV_handle;
    iEvent.getByToken(collectionToken, leptonicV_handle);

    const reco::Candidate& leptonicV = (*leptonicV_handle)[0];

    if ( leptonicV.daughter(0)->isMuon() && 
         leptonicV.daughter(1)->isMuon()    ) {
         const pat::Muon *mu1 = (pat::Muon*)leptonicV.daughter(0);
         const pat::Muon *mu2 = (pat::Muon*)leptonicV.daughter(1);
         Muons->push_back( *mu1 );
         Muons->push_back( *mu2 );
    }

    if ( leptonicV.daughter(0)->isElectron() && 
         leptonicV.daughter(1)->isElectron()    ) {
         const pat::Electron *el1 = (pat::Electron*)leptonicV.daughter(0);
         const pat::Electron *el2 = (pat::Electron*)leptonicV.daughter(1);
         Electrons->push_back( *el1 );
         Electrons->push_back( *el2 );
    }

    iEvent.put(Electrons, "Electrons");
    iEvent.put(Muons,     "Muons"    );
}

DEFINE_FWK_MODULE(LeptonicVdaughters);
