
// -*- C++ -*-
//
// Original Author:  Jose Cupertino Ruiz Vargas
//         Created:  Tue, 9 Jun 2015 22:14:00 GMT
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "ExoDiBosonResonances/EDBRLeptons/interface/TrackerMuonSelector.h"

//
// class declaration
//

class goodLeptonsProducer : public edm::EDProducer {
   public:
      explicit goodLeptonsProducer(const edm::ParameterSet&);
      ~goodLeptonsProducer();

   private:
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      
      // ----------member data ---------------------------
      edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
      edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
};

goodLeptonsProducer::goodLeptonsProducer(const edm::ParameterSet& iConfig):
    vertexToken_(consumes<reco::VertexCollection> (iConfig.getParameter<edm::InputTag>("vertex"))),
    electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
    muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons")))
{
    produces<std::vector<pat::Electron> >("goodElectrons");
    produces<std::vector<pat::Muon> >(    "goodMuons"    );
}

goodLeptonsProducer::~goodLeptonsProducer() {}

// ------------ method called to produce the data  ------------
void
goodLeptonsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    // handle goodOfflinePrimaryVertex collection
    Handle<reco::VertexCollection> vertices;
    iEvent.getByToken(vertexToken_, vertices);
    const reco::Vertex& vertex = (*vertices)[0];

    // electron IDs
    Handle<ValueMap<bool> > elmediumID_handle;
    Handle<ValueMap<bool> > eltightID_handle;
    iEvent.getByLabel(InputTag("egmGsfElectronIDs","cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"), elmediumID_handle);
    iEvent.getByLabel(InputTag("egmGsfElectronIDs","cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight"),   eltightID_handle);

    // handle muons and electons
    Handle<pat::MuonCollection> muons;
    iEvent.getByToken(muonToken_, muons);
    Handle<pat::ElectronCollection> electrons;
    iEvent.getByToken(electronToken_, electrons);
    size_t elmult=electrons->size();
    size_t mumult=muons->size();

    auto_ptr< vector<pat::Electron> > goodElectrons( new vector<pat::Electron> );
    for ( size_t i=0; i<elmult; ++i ) {
        const pat::Electron& el = (*electrons)[i];
        if ( el.pt()<40.||fabs(el.eta())>2.5 ) continue;     // acceptance cut
        const Ptr<pat::Electron> elRef(electrons, i);
        int mediumID = (*elmediumID_handle)[ elRef ]; 
        int  tightID =  (*eltightID_handle)[ elRef ]; 
        if ( !mediumID ) continue;                           // electrons must pass mediumID
        if ( !tightID && !goodElectrons->size() ) continue;  // first electron must be tightID
        goodElectrons->push_back(el);
    }

    auto_ptr< vector<pat::Muon> > goodMuons( new vector<pat::Muon> );
    for ( size_t i=0; i<mumult; ++i ) {
        const pat::Muon& mu = (*muons)[i];
        if ( mu.pt()<40.||fabs(mu.eta())>2.5 ) continue;
        int trackerID = (int)hptm::isTrackerMuon(mu, vertex);
        int tightID   = (int)muon::isTightMuon(  mu, vertex);
        if ( !trackerID ) continue;
        if ( !tightID && !goodMuons->size() ) continue;
        goodMuons->push_back(mu);
    }

    iEvent.put(goodElectrons, "goodElectrons");
    iEvent.put(goodMuons,     "goodMuons"    );
}

//define this as a plug-in
DEFINE_FWK_MODULE(goodLeptonsProducer);
