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

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

//
// class declaration
//

class GoodElectronsProducer : public edm::EDProducer {
   public:
      explicit GoodElectronsProducer(const edm::ParameterSet&);
      ~GoodElectronsProducer();

   private:
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      
      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::ElectronCollection>            electronToken;
      edm::EDGetTokenT<edm::ValueMap<float> >              elIsoMapToken;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >    looseToken;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >   mediumToken;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >    tightToken;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >     heepToken;
};

GoodElectronsProducer::GoodElectronsProducer(const edm::ParameterSet& iConfig):
    electronToken( consumes<pat::ElectronCollection>(            iConfig.getParameter<edm::InputTag>("electrons" ) ) ),
    elIsoMapToken( consumes<edm::ValueMap<float> >(              iConfig.getParameter<edm::InputTag>("elIsoMap"  ) ) ),
    looseToken(    consumes<edm::ValueMap<vid::CutFlowResult> >( iConfig.getParameter<edm::InputTag>("loose"     ) ) ),
    mediumToken(   consumes<edm::ValueMap<vid::CutFlowResult> >( iConfig.getParameter<edm::InputTag>("medium"    ) ) ),
    tightToken(    consumes<edm::ValueMap<vid::CutFlowResult> >( iConfig.getParameter<edm::InputTag>("tight"     ) ) ),
    heepToken(     consumes<edm::ValueMap<vid::CutFlowResult> >( iConfig.getParameter<edm::InputTag>("heep"      ) ) )
{
    produces<std::vector<pat::Electron> >();
}

GoodElectronsProducer::~GoodElectronsProducer() {}

// ------------ method called to produce the data  ------------
void
GoodElectronsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    // handle muons and electons
    Handle<pat::ElectronCollection>  electrons;
    iEvent.getByToken(electronToken, electrons);
    size_t elMult=electrons->size();

    // miniIsolation valueMaps
    Handle<ValueMap<float> >         elIsoMap;
    iEvent.getByToken(elIsoMapToken, elIsoMap);

    // electron IDs
    Handle<ValueMap<vid::CutFlowResult> > looseHandle, mediumHandle, tightHandle, heepHandle;
    iEvent.getByToken(looseToken,   looseHandle);
    iEvent.getByToken(mediumToken, mediumHandle);
    iEvent.getByToken(tightToken,   tightHandle);
    iEvent.getByToken(heepToken,     heepHandle);

    // Cuts to be masked
    vector<string> maskCuts, maskPFIso;
    maskCuts.push_back("GsfEleEmHadD1IsoRhoCut_0");
    maskCuts.push_back("GsfEleTrkPtIsoCut_0"); 
    maskPFIso.push_back("GsfEleEffAreaPFIsoCut_0");

    // output collections
    auto_ptr< vector<pat::Electron> > goodElectrons( new vector<pat::Electron> );

    for ( size_t i=0; i<elMult; ++i ) {
        const Ptr<pat::Electron> elPtr(electrons, i);
        const pat::Electron& el = (*electrons)[i];
        bool  loose    =  (*looseHandle)[elPtr].getCutFlowResultMasking(maskPFIso).cutFlowPassed();
        bool  medium   = (*mediumHandle)[elPtr].getCutFlowResultMasking(maskPFIso).cutFlowPassed();
        bool  tight    =  (*tightHandle)[elPtr].getCutFlowResultMasking(maskPFIso).cutFlowPassed();
        bool  heep     =   (*heepHandle)[elPtr].getCutFlowResultMasking(maskCuts).cutFlowPassed();
        float miniIso  = (*elIsoMap)[elPtr]; 
        float pfIso03R = (*looseHandle)[elPtr].getValueCutUpon(maskPFIso[0]);
        float caloIso  =  (*heepHandle)[elPtr].getValueCutUpon(maskCuts[0]);
        float trackIso =  (*heepHandle)[elPtr].getValueCutUpon(maskCuts[1]);
        pat::Electron* cloneEl = el.clone();
        cloneEl->addUserInt(  "LOOSE",      (*looseHandle)[elPtr].cutFlowPassed() );
        cloneEl->addUserInt(  "MEDIUM",    (*mediumHandle)[elPtr].cutFlowPassed() );
        cloneEl->addUserInt(  "TIGHT",      (*tightHandle)[elPtr].cutFlowPassed() );
        cloneEl->addUserInt(  "HEEP",        (*heepHandle)[elPtr].cutFlowPassed() );
        cloneEl->addUserInt(  "loose",       loose                                );
        cloneEl->addUserInt(  "medium",      medium                               );
        cloneEl->addUserInt(  "tight",       tight                                );
        cloneEl->addUserInt(  "heep",        heep                                 );
        cloneEl->addUserFloat("miniIso",     miniIso                              );
        cloneEl->addUserFloat("pfIso03R",    pfIso03R                             );
        cloneEl->addUserFloat("caloIso",     caloIso                              );
        cloneEl->addUserFloat("trackIso",    trackIso                             );
        goodElectrons->push_back(           *cloneEl                              );
    }

    iEvent.put(goodElectrons);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GoodElectronsProducer);
