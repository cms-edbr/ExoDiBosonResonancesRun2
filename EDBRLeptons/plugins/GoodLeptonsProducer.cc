
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
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

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
      double  r_iso_min_;
      double  r_iso_max_;
      double   kt_scale_;
      bool charged_only_;
      bool       filter_;
      edm::EDGetTokenT<pat::PackedCandidateCollection> pfToken_;
      edm::EDGetTokenT<reco::VertexCollection>     vertexToken_;
      edm::EDGetTokenT<pat::ElectronCollection>  electronToken_;
      edm::EDGetTokenT<pat::MuonCollection>          muonToken_;
      edm::EDGetTokenT<edm::ValueMap<bool> >    modheepIDToken_;

     double getPFIsolation(edm::Handle<pat::PackedCandidateCollection>, const reco::Candidate*, double, double, double, bool);
};

GoodLeptonsProducer::GoodLeptonsProducer(const edm::ParameterSet& iConfig):
    r_iso_min_(                                                iConfig.getParameter<double>(       "r_iso_min"     ) ),
    r_iso_max_(                                                iConfig.getParameter<double>(       "r_iso_max"     ) ),
    kt_scale_(                                                 iConfig.getParameter<double>(       "kt_scale"      ) ),
    charged_only_(                                             iConfig.getParameter<bool>(         "charged_only"  ) ),
    filter_(                                                   iConfig.getParameter<bool>(         "filter"        ) ),
    pfToken_(        consumes<pat::PackedCandidateCollection>( iConfig.getParameter<edm::InputTag>("pfCands"     ) ) ),
    vertexToken_(    consumes<reco::VertexCollection> (        iConfig.getParameter<edm::InputTag>("vertex"      ) ) ),
    electronToken_(  consumes<pat::ElectronCollection>(        iConfig.getParameter<edm::InputTag>("electrons"   ) ) ),
    muonToken_(      consumes<pat::MuonCollection>(            iConfig.getParameter<edm::InputTag>("muons"       ) ) ),
    modheepIDToken_( consumes<edm::ValueMap<bool> >(           iConfig.getParameter<edm::InputTag>("modheepID" ) ) )
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

    // handle pfcandidates
    Handle<pat::PackedCandidateCollection> pfcands;
    iEvent.getByToken(pfToken_, pfcands);

    // handle goodOfflinePrimaryVertex collection
    Handle<reco::VertexCollection> vertices;
    iEvent.getByToken(vertexToken_, vertices);
    const reco::Vertex& vertex = (*vertices)[0];

    // electron IDs
    Handle<ValueMap<bool> > modheepID_handle;
    iEvent.getByToken(modheepIDToken_, modheepID_handle);

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
        double miniIso = getPFIsolation( pfcands, 
                                         dynamic_cast<const reco::Candidate *>(&el), 
                                         r_iso_min_, 
                                         r_iso_max_, 
                                         kt_scale_, 
                                         charged_only_ );
        int isoID = miniIso<0.1 ? 1 : 0;

        const Ptr<pat::Electron> elRef(electrons, i);
        int modheepID =  (*modheepID_handle)[ elRef ]; 

        if ( filter_ and modheepID and isoID ) {          // electrons must pass the modheepID and be mini-isolated
            pat::Electron* cloneEl = el.clone();          // need to clone the electron to add miniIso as an UserFloat
            cloneEl->addUserFloat("miniIso", miniIso);
            cloneEl->addUserInt("slimmedIndex", i);       // index to localize the goodElectron in the slimmedElectrons collection
            goodElectrons->push_back(*cloneEl);
        }
    }

    auto_ptr< vector<pat::Muon> > goodMuons( new vector<pat::Muon> );
    for ( size_t i=0; i<mumult; ++i ) {
        const pat::Muon& mu = (*muons)[i];
        double miniIso = getPFIsolation( pfcands, 
                                         dynamic_cast<const reco::Candidate *>(&mu), 
                                         r_iso_min_, 
                                         r_iso_max_, 
                                         kt_scale_, 
                                         charged_only_ );

        int isoID = miniIso<0.1 ? 1 : 0;

        int trackerID = (int)hptm::isTrackerMuon(mu, vertex);  
        int highPtID  = (int)muon::isHighPtMuon( mu, vertex);  
        int tracker_OR_highPt_AND_miniIso = (trackerID or highPtID) and isoID;

        if ( filter_ and !tracker_OR_highPt_AND_miniIso   ) continue;  // muons must must be (tracker or highPt) and mini-isolated 
        if ( filter_ and !highPtID and !goodMuons->size() ) continue;  // first muon must be highPt
        pat::Muon* cloneMu = mu.clone();
        cloneMu->addUserFloat("miniIso", miniIso);
        goodMuons->push_back(*cloneMu);
    }

    iEvent.put(goodElectrons, "goodElectrons");
    iEvent.put(goodMuons,     "goodMuons"    );
}

// ------------ method to calculate the mini isolation  ------------
double 
GoodLeptonsProducer::getPFIsolation(edm::Handle<pat::PackedCandidateCollection> pfcands,
                                    const reco::Candidate* lep,  
                                    double r_iso_min, double r_iso_max, double kt_scale,
                                    bool charged_only) 
{
    using namespace std;

    if (lep->pt() < 5) return 9999.;
    // initialize cones
    double deadcone_nh(0.), deadcone_ch(0.), deadcone_ph(0.), deadcone_pu(0.);
    if(lep->isElectron()) {
      if (fabs(lep->eta())>1.479) {deadcone_ch = 0.015; deadcone_pu = 0.015; deadcone_ph = 0.08;}
    } else if(lep->isMuon()) {
      deadcone_ch = 0.0001; deadcone_pu = 0.01; deadcone_ph = 0.01;deadcone_nh = 0.01;  
    }
    // initialize sums
    double iso_nh(0.); double iso_ch(0.); 
    double iso_ph(0.); double iso_pu(0.);
    double ptThresh(0.5);
    if(lep->isElectron()) ptThresh = 0;
    // isolation cone
    double r_iso = max(r_iso_min, min(r_iso_max, kt_scale/lep->pt()));
    // loop over PF candidates
    for (const pat::PackedCandidate &pfc : *pfcands) {
        if (abs(pfc.pdgId())<7) continue;
        double dr = deltaR(pfc, *lep);
        if (dr > r_iso) continue;
        //////////////////  NEUTRALS  ///////////////////
        if (pfc.charge()==0){
            if (pfc.pt()>ptThresh) {
                /////////// PHOTONS ////////////
                if (abs(pfc.pdgId())==22) {
                    if(dr < deadcone_ph) continue;
                    iso_ph += pfc.pt();
                }  /////////// NEUTRAL HADRONS ////////////
                else if (abs(pfc.pdgId())==130) {
                    if(dr < deadcone_nh) continue;
                    iso_nh += pfc.pt();
                }
            }
        }  //////////////////  CHARGED from PV  ////////////////////
        else if (pfc.fromPV()>1){
            if (abs(pfc.pdgId())==211) {
                if(dr < deadcone_ch) continue;
                iso_ch += pfc.pt();
            }
        }  //////////////////  CHARGED from PU  ////////////////////
        else {
            if (pfc.pt()>ptThresh){
                if(dr < deadcone_pu) continue;
                iso_pu += pfc.pt();
            }
        }
    }// close loop over PF candidates

    double iso(0.);
    if (charged_only){
      iso = iso_ch;
    } 
    else {
      iso = iso_ch + max(0., iso_nh + iso_ph - 0.5*iso_pu);
    }

    return iso/lep->pt();

}//close getPFIsolation

//define this as a plug-in
DEFINE_FWK_MODULE(GoodLeptonsProducer);
