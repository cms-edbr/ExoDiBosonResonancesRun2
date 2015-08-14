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
      double maxDeltaPt_;

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
    maxDeltaR_  (                                                 iConfig.getParameter<double>                  ("maxDeltaR"   ) ),
    maxDeltaPt_ (                                                 iConfig.getParameter<double>                  ("maxDeltaPt"  ) )
{
    produces<bool>("trigBit");
    produces<edm::ValueMap<float> >("deltaR");
    produces<edm::ValueMap<float> >("deltaPt");
    produces<edm::ValueMap<bool > >("matchDeltaR");
    produces<edm::ValueMap<bool > >("matchPt");
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

    vector<float> deltaRLepObj;
    vector<float> deltaPtLepObj;
    vector<bool>  matchDeltaR;
    vector<bool>  matchPt;

    Handle<candidateCollection>     leptons;
    iEvent.getByToken(leptonToken_, leptons);
    typename candidateCollection::const_iterator lep, endLoop = leptons->end();
    for (lep = leptons->begin(); lep != endLoop; ++lep) {
        float pt  = lep->pt();
        float eta = lep->eta();
        float phi = lep->phi();
        if ( numObj ){
            int closest=0;
            for(int i=1; i<numObj; i++){
                int temp = deltaR( eta, phi, etaObj[closest], phiObj[closest] ) <
                           deltaR( eta, phi, etaObj[i],       phiObj[i]       ) ? closest : i;
                closest  = temp;
            }
            double dR  = deltaR( eta, phi, etaObj[closest], phiObj[closest] ); 
            double dPt = abs(pt-ptObj[closest])/pt; 
            bool matchBydR = dR  < maxDeltaR_  ? true : false;
            bool matchByPt = dPt < maxDeltaPt_ ? true : false;
            deltaRLepObj.push_back( dR );
            deltaPtLepObj.push_back(dPt);
            matchDeltaR.push_back( matchBydR );
            matchPt.push_back(     matchByPt );
        }
        else {
            deltaRLepObj.push_back( 9999.);
            deltaPtLepObj.push_back(9999.);
            matchDeltaR.push_back( false );
            matchPt.push_back(     false );
        }
    }

    auto_ptr<ValueMap<float> >      dRMap(new ValueMap<float>());
    auto_ptr<ValueMap<float> >     dPtMap(new ValueMap<float>());
    auto_ptr<ValueMap<bool > > matchDRMap(new ValueMap<bool >());
    auto_ptr<ValueMap<bool > > matchPtMap(new ValueMap<bool >());

    ValueMap<float>::Filler      dRFiller(      *dRMap );
    ValueMap<float>::Filler     dPtFiller(     *dPtMap );
    ValueMap<bool >::Filler matchDRFiller( *matchDRMap );
    ValueMap<bool >::Filler matchPtFiller( *matchPtMap );

         dRFiller.insert( leptons,  deltaRLepObj.begin(),  deltaRLepObj.end() );
        dPtFiller.insert( leptons, deltaPtLepObj.begin(), deltaPtLepObj.end() );
    matchDRFiller.insert( leptons,   matchDeltaR.begin(),   matchDeltaR.end() );
    matchPtFiller.insert( leptons,       matchPt.begin(),       matchPt.end() );

         dRFiller.fill();
        dPtFiller.fill();
    matchDRFiller.fill(); 
    matchPtFiller.fill();
    
    iEvent.put( dRMap,      "deltaR"      );
    iEvent.put( dPtMap,     "deltaPt"     );
    iEvent.put( matchDRMap, "matchDeltaR" );
    iEvent.put( matchPtMap, "matchPt"     );
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
