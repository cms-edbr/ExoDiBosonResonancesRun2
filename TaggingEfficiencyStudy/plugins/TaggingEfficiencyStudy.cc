// -*- C++ -*-
//
// Package:    ExoDiBosonResonances/TaggingEfficiencyStudy
// Class:      TaggingEfficiencyStudy
// 
/**\class TaggingEfficiencyStudy TaggingEfficiencyStudy.cc ExoDiBosonResonances/TaggingEfficiencyStudy/plugins/TaggingEfficiencyStudy.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Thiago Tomei Fernandez
//         Created:  Wed, 10 Dec 2014 10:25:00 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "TH1D.h"

//
// class declaration
//

class TaggingEfficiencyStudy : public edm::EDAnalyzer {
   public:
      explicit TaggingEfficiencyStudy(const edm::ParameterSet&);
      ~TaggingEfficiencyStudy();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  TH1D* histoDenominator;
  TH1D* histoPrunedMass;
  TH1D* histoPrunedMassAndTau;
  TH1D* histoZdaughters;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TaggingEfficiencyStudy::TaggingEfficiencyStudy(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  histoDenominator = fs->make<TH1D>("histoDenominator","Denominator",100,100,2100);
  histoPrunedMass = fs->make<TH1D>("histoPrunedMass","PrunedMass",100,100,2100);
  histoPrunedMassAndTau = fs->make<TH1D>("histoPrunedMassAndTau","FullTagging",100,100,2100);
  histoZdaughters = fs->make<TH1D>("histoZdaughters","Zdaughters",30,0.5,30.5);
}


TaggingEfficiencyStudy::~TaggingEfficiencyStudy()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TaggingEfficiencyStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;

   Handle<std::vector<GenParticle> > prunedGenParticles;
   iEvent.getByLabel("prunedGenParticles",prunedGenParticles);
   
   Handle<std::vector<pat::Jet> > jets;
   iEvent.getByLabel("cleanPatJets", jets);

   if(jets->size() == 0) return;

   const pat::Jet& leadingJet = jets->at(0);

   bool foundBoson=false;
   int bosonIdx = -1;
   for(size_t i = 0; i != prunedGenParticles->size(); ++i) {
     const GenParticle& boson = prunedGenParticles->at(i);
     if (boson.pdgId() != 23) continue;
     histoZdaughters->Fill(std::abs(boson.daughter(0)->pdgId()));
     if (std::abs(boson.daughter(0)->pdgId()) > 5) continue;
     // If we got here we found a hadronically decaying Z boson
     // See if it matches
     double dR = deltaR(leadingJet.eta(), leadingJet.phi(), boson.eta(), boson.phi());
     if (dR > 0.8) continue;
     // If we got here, it matches!
     foundBoson = true;
     bosonIdx = i;
     break;
   }

   // Now we found a matched boson!
   // Check if it passes the prunedMass and tau21 cuts;
   double tau2 = leadingJet.userFloat("NjettinessAK8:tau2"); 
   double tau1 = leadingJet.userFloat("NjettinessAK8:tau1"); 
   double tau21 = (tau1 != 0) ? tau2/tau1 : 1.0;
   double prunedMass = leadingJet.userFloat("ak8PFJetsCHSPrunedLinks");  
   
   if(foundBoson == true) {
     const GenParticle& boson = prunedGenParticles->at(bosonIdx);
     histoDenominator->Fill(boson.pt());
   if(foundBoson && prunedMass > 70.0 && prunedMass < 110.0)
     histoPrunedMass->Fill(boson.pt());
   if(foundBoson && prunedMass 70.0 && prunedMass < 110.0 && tau21 < 0.5)
     histoPrunedMassAndTau->Fill(boson.pt());
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
TaggingEfficiencyStudy::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TaggingEfficiencyStudy::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
TaggingEfficiencyStudy::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
TaggingEfficiencyStudy::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
TaggingEfficiencyStudy::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
TaggingEfficiencyStudy::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TaggingEfficiencyStudy::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TaggingEfficiencyStudy);
