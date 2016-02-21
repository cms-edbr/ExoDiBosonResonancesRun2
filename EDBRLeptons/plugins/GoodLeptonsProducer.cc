
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
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "ExoDiBosonResonances/EDBRLeptons/interface/TrackerMuonSelector.h"

//
// class declaration
//

class GoodLeptonsProducer : public edm::EDProducer {
   public:
      explicit GoodLeptonsProducer(const edm::ParameterSet&);
      ~GoodLeptonsProducer();

   private:
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      
      // ----------member data ---------------------------
      edm::EDGetTokenT<reco::VertexCollection>               vertexToken;
      edm::EDGetTokenT<pat::ElectronCollection>            electronToken;
      edm::EDGetTokenT<pat::MuonCollection>                    muonToken;
      edm::EDGetTokenT<edm::ValueMap<float> >              elIsoMapToken;
      edm::EDGetTokenT<edm::ValueMap<float> >              muIsoMapToken;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >     heepToken;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >    looseToken;
};

GoodLeptonsProducer::GoodLeptonsProducer(const edm::ParameterSet& iConfig):
    vertexToken(   consumes<reco::VertexCollection> (            iConfig.getParameter<edm::InputTag>("vertex"    ) ) ),
    electronToken( consumes<pat::ElectronCollection>(            iConfig.getParameter<edm::InputTag>("electrons" ) ) ),
    muonToken(     consumes<pat::MuonCollection>(                iConfig.getParameter<edm::InputTag>("muons"     ) ) ),
    elIsoMapToken( consumes<edm::ValueMap<float> >(              iConfig.getParameter<edm::InputTag>("elIsoMap"  ) ) ),
    muIsoMapToken( consumes<edm::ValueMap<float> >(              iConfig.getParameter<edm::InputTag>("muIsoMap"  ) ) ),
    heepToken(  consumes<edm::ValueMap<vid::CutFlowResult> >(    iConfig.getParameter<edm::InputTag>("heep"      ) ) ),
    looseToken(    consumes<edm::ValueMap<vid::CutFlowResult> >( iConfig.getParameter<edm::InputTag>("loose"     ) ) )
{
    produces<std::vector<pat::Electron> >("Electrons");
    produces<std::vector<pat::Muon> >(    "Muons"    );
}

GoodLeptonsProducer::~GoodLeptonsProducer() {}

// ------------ method called to produce the data  ------------
void
GoodLeptonsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    // handle goodOfflinePrimaryVertex collection
    Handle<reco::VertexCollection>  vertices;
    iEvent.getByToken(vertexToken,  vertices);
    const reco::Vertex& vertex = (*vertices)[0];

    // handle muons and electons
    Handle<pat::ElectronCollection>   electrons;
    Handle<pat::MuonCollection>       muons;
    iEvent.getByToken(electronToken,  electrons);
    iEvent.getByToken(muonToken,      muons);
    size_t elMult=electrons->size();
    size_t muMult=muons->size();

    // miniIsolation valueMaps
    Handle<ValueMap<float> > elIsoMap, muIsoMap ;
    iEvent.getByToken(elIsoMapToken,   elIsoMap);
    iEvent.getByToken(muIsoMapToken,   muIsoMap);

    // electron IDs
    Handle<ValueMap<vid::CutFlowResult> > looseHandle, heepHandle;
    iEvent.getByToken(looseToken,   looseHandle);
    iEvent.getByToken(heepToken,     heepHandle);

    // Cuts to be masked
    vector<string> maskCuts, maskPFIso;
    maskCuts.push_back("GsfEleEmHadD1IsoRhoCut_0");
    maskCuts.push_back("GsfEleTrkPtIsoCut_0"); 
    maskPFIso.push_back("GsfEleEffAreaPFIsoCut_0");

    // output collections
    auto_ptr< vector<pat::Electron> > goodElectrons( new vector<pat::Electron> );
    auto_ptr< vector<pat::Muon> >     goodMuons(     new vector<pat::Muon>     );

    for ( size_t i=0; i<elMult; ++i ) {
        const Ptr<pat::Electron> elPtr(electrons, i);
        const pat::Electron& el = (*electrons)[i];
        bool  HEEP              =  (*heepHandle)[elPtr].cutFlowPassed(); 
        bool  LOOSE             = (*looseHandle)[elPtr].cutFlowPassed(); 
        bool  heep              =  (*heepHandle)[elPtr].getCutFlowResultMasking(maskCuts).cutFlowPassed();
        bool  loose             = (*looseHandle)[elPtr].getCutFlowResultMasking(maskPFIso).cutFlowPassed();
        float pfIso03R          = (*looseHandle)[elPtr].getValueCutUpon(maskPFIso[0]);
        float miniIso           =    (*elIsoMap)[elPtr]; 
        pat::Electron* cloneEl = el.clone();
        cloneEl->addUserInt("slimmedIndex",  i          ); // index to localize the goodElectron in the slimmedElectrons
        cloneEl->addUserInt("HEEP",          HEEP       );
        cloneEl->addUserInt("LOOSE",         LOOSE      );
        cloneEl->addUserInt("heep",          heep       );
        cloneEl->addUserInt("loose",         loose      );
        cloneEl->addUserFloat("pfIso03R",    pfIso03R   );
        cloneEl->addUserFloat("miniIso",     miniIso    );
        goodElectrons->push_back(            *cloneEl   );
    }
    for ( size_t i=0; i<muMult; ++i ) {
        const Ptr<pat::Muon> muPtr(muons, i);
        const pat::Muon& mu    = (*muons)[i];
        float miniIso          = (*muIsoMap)[muPtr]; 
        float trackIso         = mu.isolationR03().sumPt;
        float innerIso         = mu.innerTrack().isNonnull() ? mu.innerTrack()->pt() : -1.e4;
        bool  trackerID        = hptm::isTrackerMuon(mu, vertex);  
        bool  highPtID         = muon::isHighPtMuon( mu, vertex);  
        pat::Muon* cloneMu = mu.clone();
        cloneMu->addUserInt("slimmedIndex", i            );
        cloneMu->addUserInt("isTracker",    trackerID    );
        cloneMu->addUserInt("isHighPt",     highPtID     );
        cloneMu->addUserFloat("trackIso",   trackIso     );
        cloneMu->addUserFloat("innerIso",   innerIso     );
        cloneMu->addUserFloat("miniIso",    miniIso      );
        goodMuons->push_back(               *cloneMu     );
    }

    iEvent.put(goodElectrons, "Electrons");
    iEvent.put(goodMuons,     "Muons"    );
}

//define this as a plug-in
DEFINE_FWK_MODULE(GoodLeptonsProducer);
