
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
      bool filter_;
      edm::EDGetTokenT<reco::VertexCollection>               vertexToken_;
      edm::EDGetTokenT<pat::ElectronCollection>            electronToken_;
      edm::EDGetTokenT<pat::MuonCollection>                    muonToken_;
      edm::EDGetTokenT<edm::ValueMap<float> >              elIsoMapToken_;
      edm::EDGetTokenT<edm::ValueMap<float> >              muIsoMapToken_;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >  heepV60Token_;
};

GoodLeptonsProducer::GoodLeptonsProducer(const edm::ParameterSet& iConfig):
    filter_(                                                      iConfig.getParameter<bool>(         "filter"      ) ),
    vertexToken_(   consumes<reco::VertexCollection> (            iConfig.getParameter<edm::InputTag>("vertex"    ) ) ),
    electronToken_( consumes<pat::ElectronCollection>(            iConfig.getParameter<edm::InputTag>("electrons" ) ) ),
    muonToken_(     consumes<pat::MuonCollection>(                iConfig.getParameter<edm::InputTag>("muons"     ) ) ),
    elIsoMapToken_( consumes<edm::ValueMap<float> >(              iConfig.getParameter<edm::InputTag>("elIsoMap"  ) ) ),
    muIsoMapToken_( consumes<edm::ValueMap<float> >(              iConfig.getParameter<edm::InputTag>("muIsoMap"  ) ) ),
    heepV60Token_(  consumes<edm::ValueMap<vid::CutFlowResult> >( iConfig.getParameter<edm::InputTag>("heepV60"   ) ) )
{
    produces<std::vector<pat::Electron> >("goodElectrons");
    produces<std::vector<pat::Muon> >(    "goodMuons"    );
}

GoodLeptonsProducer::~GoodLeptonsProducer() {}

// ------------ method called to produce the data  ------------
void
GoodLeptonsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    // handle HLT information
    Handle<bool>      elHlt_handle;
    Handle<bool>      muHlt_handle;
    bool elPassHlt = *elHlt_handle;
    bool muPassHlt = *muHlt_handle;
    Handle<ValueMap<bool> > elMatchDeltaR_handle,  muMatchDeltaR_handle;
    Handle<ValueMap<bool> > elMatchPt_handle,      muMatchPt_handle;
    iEvent.getByLabel(InputTag("hltMatchingElectrons", "trigBit"),     elHlt_handle);
    iEvent.getByLabel(InputTag("hltMatchingElectrons", "matchDeltaR"), elMatchDeltaR_handle);
    iEvent.getByLabel(InputTag("hltMatchingElectrons", "matchPt"),     elMatchPt_handle);
    iEvent.getByLabel(InputTag("hltMatchingMuons",     "trigBit"),     muHlt_handle);
    iEvent.getByLabel(InputTag("hltMatchingMuons",     "matchDeltaR"), muMatchDeltaR_handle);
    iEvent.getByLabel(InputTag("hltMatchingMuons",     "matchPt"),     muMatchPt_handle);

    // handle goodOfflinePrimaryVertex collection
    Handle<reco::VertexCollection>  vertices;
    iEvent.getByToken(vertexToken_, vertices);
    const reco::Vertex& vertex = (*vertices)[0];

    // handle muons and electons
    Handle<pat::ElectronCollection>   electrons;
    Handle<pat::MuonCollection>       muons;
    iEvent.getByToken(electronToken_, electrons);
    iEvent.getByToken(muonToken_,     muons);
    size_t elMult=electrons->size();
    size_t muMult=muons->size();

    // miniIsolation valueMaps
    Handle<ValueMap<float> > elIsoMap, muIsoMap ;
    iEvent.getByToken(elIsoMapToken_,  elIsoMap);
    iEvent.getByToken(muIsoMapToken_,  muIsoMap);

    // electron IDs
    Handle<ValueMap<vid::CutFlowResult> > heepV60_handle;
    iEvent.getByToken(heepV60Token_,      heepV60_handle);
    // Cuts to be masked
    std::vector<std::string> maskCuts;
    maskCuts.push_back("GsfEleTrkPtIsoCut_0"), maskCuts.push_back("GsfEleEmHadD1IsoRhoCut_0");

    // output collections
    auto_ptr< vector<pat::Electron> > goodElectrons( new vector<pat::Electron> );
    auto_ptr< vector<pat::Muon> >     goodMuons(     new vector<pat::Muon>     );

    for ( size_t i=0; i<elMult; ++i ) {
        const Ptr<pat::Electron> elPtr(electrons, i);
        float miniIso           = (*elIsoMap)[elPtr]; 
        bool  isoID             = miniIso<0.1 ? 1 : 0;
        const pat::Electron& el = (*electrons)[i];
        bool  acceptance        = el.pt()>115. && el.eta()<2.5 ? 1 : 0;
        bool  matchHltByDeltaR  = (*elMatchDeltaR_handle)[elPtr];
        bool  matchHltByPt      = (*elMatchPt_handle)[elPtr];
        bool  heepV60           = (*heepV60_handle)[elPtr].cutFlowPassed(); 
        bool  heepV60_noiso     = (*heepV60_handle)[elPtr].getCutFlowResultMasking(maskCuts).cutFlowPassed();
        if ( filter_ and !(heepV60_noiso and isoID) ) continue;    // electrons must be heepV60_noiso and miniIsolated
        if ( filter_ and !(elPassHlt and matchHltByDeltaR and matchHltByPt and acceptance) ) continue;
        pat::Electron* cloneEl = el.clone();                       // need to clone the electron to add miniIso as UserFloat
        cloneEl->addUserInt("slimmedIndex",  i             );      // index to localize the goodElectron in the slimmedElectrons collection
        cloneEl->addUserInt("heepV60",       heepV60       );
        cloneEl->addUserInt("heepV60_noiso", heepV60_noiso );
        cloneEl->addUserFloat("miniIso", miniIso           );
        goodElectrons->push_back(*cloneEl);
    }

    for ( size_t i=0; i<muMult; ++i ) {
        const Ptr<pat::Muon> muPtr(muons, i);
        float miniIso          = (*muIsoMap)[muPtr]; 
        bool  isoID            = miniIso<0.1 ? 1 : 0;
        const pat::Muon& mu    = (*muons)[i];
        bool  acceptance       = mu.pt()>50. && mu.eta()<2.1 ? 1 : 0;
        bool  matchHltByDeltaR = (*muMatchDeltaR_handle)[muPtr];
        bool  matchHltByPt     = (*muMatchPt_handle)[muPtr];
        bool  trackerID = hptm::isTrackerMuon(mu, vertex);  
        bool  highPtID  = muon::isHighPtMuon( mu, vertex);  
        bool tracker_OR_highPt_AND_miniIso = (trackerID or highPtID) and isoID;
        if ( filter_ and !tracker_OR_highPt_AND_miniIso ) continue;  // muons must be tracker_OR_highPt and miniIsolated 
        if ( filter_ and goodMuons->size()==1 ) {
            bool highPt_AND_tracker = muon::isHighPtMuon( (*goodMuons)[0], vertex) and trackerID; 
            bool tracker_AND_highPt = hptm::isTrackerMuon((*goodMuons)[0], vertex) and highPtID; 
            if ( !(highPt_AND_tracker or tracker_AND_highPt) ) continue; 
        }
        if ( filter_ and !(muPassHlt and matchHltByDeltaR and matchHltByPt and acceptance) ) continue;
        pat::Muon* cloneMu = mu.clone();
        cloneMu->addUserInt("slimmedIndex", i         );
        cloneMu->addUserInt("isTracker",    trackerID );
        cloneMu->addUserInt("isHighPt",     highPtID  );
        cloneMu->addUserFloat("miniIso",    miniIso   );
        goodMuons->push_back(*cloneMu);
    }

    iEvent.put(goodElectrons, "goodElectrons");
    iEvent.put(goodMuons,     "goodMuons"    );
}

//define this as a plug-in
DEFINE_FWK_MODULE(GoodLeptonsProducer);
