
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
    Handle<ValueMap<float> >          muIsoMap ;
    Handle<ValueMap<float> >          elIsoMap ;
    iEvent.getByToken(muIsoMapToken_, muIsoMap);
    iEvent.getByToken(elIsoMapToken_, elIsoMap);

    // electron IDs
    Handle<ValueMap<vid::CutFlowResult> > heepV60_handle;
    iEvent.getByToken(heepV60Token_,      heepV60_handle);

    // output collections
    auto_ptr< vector<pat::Electron> > goodElectrons( new vector<pat::Electron> );
    auto_ptr< vector<pat::Muon> >     goodMuons(     new vector<pat::Muon>     );

    for ( size_t i=0; i<elMult; ++i ) {
        const pat::Electron& el = (*electrons)[i];
        const Ptr<pat::Electron> elPtr(electrons, i);
        float miniIso = (*elIsoMap)[elPtr]; 
        int isoID = miniIso<0.1 ? 1 : 0;
        std::vector<std::string> maskCuts;
        maskCuts.push_back("GsfEleTrkPtIsoCut_0"), maskCuts.push_back("GsfEleEmHadD1IsoRhoCut_0");
        int heepV60 =       (*heepV60_handle)[elPtr].cutFlowPassed(); 
        int heepV60_noiso = (*heepV60_handle)[elPtr].getCutFlowResultMasking(maskCuts).cutFlowPassed();
        int heepV60_noiso_AND_miniIso = heepV60_noiso and isoID;
        if ( filter_ and !heepV60_noiso_AND_miniIso ) continue;    // electrons must be heepV60_noiso and miniIsolated
        pat::Electron* cloneEl = el.clone();                       // need to clone the electron to add miniIso as UserFloat
        cloneEl->addUserInt("slimmedIndex",  i             );      // index to localize the goodElectron in the slimmedElectrons collection
        cloneEl->addUserInt("heepV60",       heepV60       );
        cloneEl->addUserInt("heepV60_noiso", heepV60_noiso );
        cloneEl->addUserFloat("miniIso", miniIso           );
        goodElectrons->push_back(*cloneEl);
    }

    for ( size_t i=0; i<muMult; ++i ) {
        const pat::Muon& mu = (*muons)[i];
        const Ptr<pat::Muon> muPtr(muons, i);
        float miniIso = (*muIsoMap)[muPtr]; 
        int isoID = miniIso<0.1 ? 1 : 0;
        int trackerID = (int)hptm::isTrackerMuon(mu, vertex);  
        int highPtID  = (int)muon::isHighPtMuon( mu, vertex);  
        int tracker_OR_highPt_AND_miniIso = (trackerID or highPtID) and isoID;
        if ( filter_ and !tracker_OR_highPt_AND_miniIso ) continue;  // muons must be tracker_OR_highPt and miniIsolated 
        if ( filter_ and goodMuons->size()==1 ) {
            int highPt_AND_tracker = (int)muon::isHighPtMuon( (*goodMuons)[0], vertex) and trackerID; 
            int tracker_AND_highPt = (int)hptm::isTrackerMuon((*goodMuons)[0], vertex) and highPtID; 
            if ( !(highPt_AND_tracker or tracker_AND_highPt) ) continue; 
        }
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
