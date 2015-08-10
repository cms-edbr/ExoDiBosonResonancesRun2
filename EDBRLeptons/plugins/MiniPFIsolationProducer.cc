// -*- C++ -*-
//
// Original Author:  Jose Cupertino Ruiz Vargas
//         Created:  Monday, 10 Aug 2015
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

template <typename T>
class MiniPFIsolationProducer : public edm::EDProducer {
   public:
      explicit MiniPFIsolationProducer(const edm::ParameterSet&);

   private:
      typedef T candidate_type;
      typedef std::vector<candidate_type> candidateCollection;

      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      
      double r_iso_min_;
      double r_iso_max_;
      double kt_scale_;
      bool charged_only_;
      edm::EDGetTokenT<candidateCollection> leptonToken;
      edm::EDGetTokenT<pat::PackedCandidateCollection> pfToken;
};

template <typename T>
MiniPFIsolationProducer<T>::MiniPFIsolationProducer(const edm::ParameterSet& iConfig):
    r_iso_min_(                                           iConfig.getParameter<double>("r_iso_min"       ) ),
    r_iso_max_(                                           iConfig.getParameter<double>("r_iso_max"       ) ),
    kt_scale_(                                            iConfig.getParameter<double>("kt_scale"        ) ),
    charged_only_(                                        iConfig.getParameter<bool>("charged_only"      ) ),
    leptonToken(consumes<candidateCollection>(            iConfig.getParameter<edm::InputTag>("leptons") ) ),
    pfToken(    consumes<pat::PackedCandidateCollection>( iConfig.getParameter<edm::InputTag>("pfCands") ) )
{
    produces<edm::ValueMap<float> >();
}

template <typename T>
void MiniPFIsolationProducer<T>::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace std;

    edm::Handle<candidateCollection> leptons;
    iEvent.getByToken(leptonToken, leptons);

    edm::Handle<pat::PackedCandidateCollection> pfcands;
    iEvent.getByToken(pfToken, pfcands);

    vector<float> miniIso;

    // loop over leptons
    typename candidateCollection::const_iterator lep, endLoop = leptons->end();
    for (lep = leptons->begin(); lep != endLoop; ++lep) {
        if (lep->pt() < 5) {miniIso.push_back(9999.); continue;}
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
        double r_iso = max(r_iso_min_,min(r_iso_max_, kt_scale_/lep->pt()));
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
        if (charged_only_){
          iso = iso_ch;
        } 
        else {
          iso = iso_ch + max(0., iso_nh + iso_ph - 0.5*iso_pu);
        }
        miniIso.push_back(iso/lep->pt());
    }// close loop over leptons

    // convert into ValueMap
    auto_ptr<edm::ValueMap<float> > miniMap(new edm::ValueMap<float>());
    edm::ValueMap<float>::Filler miniFiller(*miniMap);
    miniFiller.insert(leptons, miniIso.begin(), miniIso.end());
    miniFiller.fill();

    iEvent.put(miniMap);
}

//define this as a plug-in

typedef MiniPFIsolationProducer<pat::Electron> PatElectronMiniIsolationValueMap;
typedef MiniPFIsolationProducer<pat::Muon>         PatMuonMiniIsolationValueMap;

DEFINE_FWK_MODULE(PatElectronMiniIsolationValueMap);
DEFINE_FWK_MODULE(PatMuonMiniIsolationValueMap);
