// -*- C++ -*-
//
// Original Author:  Jose Cupertino Ruiz Vargas
//         Created:  13 Aug 2015
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

template <typename T>
class HLTmatchValueMap : public edm::EDProducer {
   public:
      explicit HLTmatchValueMap(const edm::ParameterSet&);

   private:
      typedef std::vector<T> candidateCollection;

      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      
      std::vector<std::string> path_;
      edm::EDGetTokenT<edm::TriggerResults> hltToken_;
      edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> hltObjects_;
      edm::EDGetTokenT<candidateCollection> leptonToken_;
      double maxDeltaR_;

      virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
      HLTConfigProvider hltConfig;
      std::vector<std::string> foundPaths;
};

template <typename T>
HLTmatchValueMap<T>::HLTmatchValueMap(const edm::ParameterSet& iConfig):
    path_       (                                                 iConfig.getParameter<std::vector<std::string>>("path"        ) ), 
    hltToken_   (consumes<edm::TriggerResults>                   (iConfig.getParameter<edm::InputTag>           ("hltToken"  ) ) ),
    hltObjects_ (consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>           ("hltObjects") ) ),
    leptonToken_(consumes<candidateCollection>                   (iConfig.getParameter<edm::InputTag>           ("leptons"   ) ) ),
    maxDeltaR_  (                                                 iConfig.getParameter<double>                  ("maxDeltaR"   ) )
{
    produces<bool>("trigBit");
    produces<edm::ValueMap<float> >("deltaR");
    produces<edm::ValueMap<float> >("deltaPt");
    produces<edm::ValueMap<bool > >("matchHlt");
}

template <typename T>
void HLTmatchValueMap<T>::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    Handle<TriggerResults>       trigRes;
    iEvent.getByToken(hltToken_, trigRes);
    bool bit( trigRes->accept(hltConfig.triggerIndex(foundPaths[0])) );
    std::auto_ptr<bool> trigBit(new bool(bit));
    iEvent.put( trigBit, "trigBit" );

    // translate indices into names
    const TriggerNames &names = iEvent.triggerNames(*trigRes);

    // arrays to store trigger object properties
    std::vector<float>  ptObj;
    std::vector<float> etaObj;
    std::vector<float> phiObj;

    // ------ handle trigger objects ----------//
    Handle<pat::TriggerObjectStandAloneCollection> hltObjects;
    iEvent.getByToken(hltObjects_,                 hltObjects);
    int numObj=0;
    for (pat::TriggerObjectStandAlone obj : *hltObjects) {
        obj.unpackPathNames(names);
        bool L3_and_final = obj.hasPathName(foundPaths[0], true, true);
        if ( L3_and_final ) {
            ptObj.push_back(  obj.pt()  );
            etaObj.push_back( obj.eta() );
            phiObj.push_back( obj.phi() );
            numObj++;
        }
    }

    // arrays for the ValueMaps
    vector<float> deltaRLepObj;
    vector<float> deltaPtLepObj;
    vector<bool>  matchHlt;

    Handle<candidateCollection>     leptons;
    iEvent.getByToken(leptonToken_, leptons);
    typename candidateCollection::const_iterator lep, endLoop = leptons->end();
    for (lep = leptons->begin(); lep != endLoop; ++lep) {
        float pt   = lep->pt();
        float eta  = lep->eta();
        float phi  = lep->phi();
        float dR   = 9999.;
        float dPt  = 9999.;
        bool match = false;
        if ( numObj ){
            // arrays for the matched objects
            std::vector<float>  ptMatchedObj;
            std::vector<float> etaMatchedObj;
            std::vector<float> phiMatchedObj;
            int matchedObj = 0; 
            for(int i=0; i<numObj; i++){
                dR = deltaR( eta, phi, etaObj[i], phiObj[i] ); 
                if ( dR > maxDeltaR_ ) continue;
                 ptMatchedObj.push_back(  ptObj[i] );
                etaMatchedObj.push_back( etaObj[i] );
                phiMatchedObj.push_back( phiObj[i] );
                matchedObj++;
            }
            if ( matchedObj ){
                int closest=0; 
                for(int i=0; i<matchedObj; i++){
                    // find closest object ranked by pt
                    int temp = fabs(pt - ptMatchedObj[closest])/pt < 
                               fabs(pt - ptMatchedObj[i])/pt       ? closest : i; 
                    closest  = temp;
                }
                dR  = deltaR(eta, phi, etaMatchedObj[closest], phiMatchedObj[closest]); 
                dPt = fabs(pt - ptMatchedObj[closest]) / pt; 
                match = true;
            }
        }
        deltaRLepObj.push_back(  dR  );
        deltaPtLepObj.push_back( dPt );
        matchHlt.push_back(    match );
    }

    auto_ptr<ValueMap<float> >      dRMap(new ValueMap<float>());
    auto_ptr<ValueMap<float> >     dPtMap(new ValueMap<float>());
    auto_ptr<ValueMap<bool > >   matchMap(new ValueMap<bool >());

    ValueMap<float>::Filler      dRFiller(      *dRMap );
    ValueMap<float>::Filler     dPtFiller(     *dPtMap );
    ValueMap<bool >::Filler   matchFiller(   *matchMap );

       dRFiller.insert( leptons,  deltaRLepObj.begin(),  deltaRLepObj.end() );
      dPtFiller.insert( leptons, deltaPtLepObj.begin(), deltaPtLepObj.end() );
    matchFiller.insert( leptons,      matchHlt.begin(),      matchHlt.end() );

       dRFiller.fill();
      dPtFiller.fill();
    matchFiller.fill(); 
    
    iEvent.put( dRMap,    "deltaR"   );
    iEvent.put( dPtMap,   "deltaPt"  );
    iEvent.put( matchMap, "matchHlt" );
}

template <typename T>
void HLTmatchValueMap<T>::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
   bool changed;
   if ( !hltConfig.init(iRun, iSetup, "HLT", changed) ) {
     edm::LogError("HltAnalysis") << "Initialization of HLTConfigProvider failed!!";
     return;
   }
   foundPaths.clear();
   for (size_t i = 0; i < path_.size(); i++) {
      std::vector<std::string> matchedPaths = hltConfig.matched( hltConfig.triggerNames(), path_[i] );
      while ( !matchedPaths.empty() ){
         foundPaths.push_back( matchedPaths.back() );
         matchedPaths.pop_back();
      }
   }
   std::cout<<"\n************** HLT Information **************\n";
   std::cout<<"\n Run number: " << iRun.run() << std::endl;
   for (size_t i=0; i < foundPaths.size(); i++) std::cout << "\n Found paths: " << foundPaths[i].c_str() << std::endl;
   std::cout<<"\n*********************************************\n\n";
}

typedef HLTmatchValueMap<pat::Electron> PatElectronHLTmatching;
typedef HLTmatchValueMap<pat::Muon>         PatMuonHLTmatching;
DEFINE_FWK_MODULE(PatElectronHLTmatching);
DEFINE_FWK_MODULE(    PatMuonHLTmatching);
