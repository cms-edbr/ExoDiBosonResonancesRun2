// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "ExoDiBosonResonances/EDBRLeptons/interface/TrackerMuonSelector.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

//
// class declaration
//

class ExoVZTrackerMuonIDProducer : public edm::EDProducer {
   public:
      explicit ExoVZTrackerMuonIDProducer(const edm::ParameterSet&);
      ~ExoVZTrackerMuonIDProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      edm::EDGetTokenT<edm::View<pat::Muon> > MuonToken_;
      edm::EDGetTokenT<edm::View<reco::Vertex> > VertexToken_;
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
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
ExoVZTrackerMuonIDProducer::ExoVZTrackerMuonIDProducer(const edm::ParameterSet& iConfig):
    MuonToken_ (consumes<edm::View<pat::Muon> > (iConfig.getParameter<edm::InputTag>( "src" ) ) ),
    VertexToken_ (consumes<edm::View<reco::Vertex> > (iConfig.getParameter<edm::InputTag>( "vertex" ) ) )
{
  produces<std::vector<pat::Muon>>();
}


ExoVZTrackerMuonIDProducer::~ExoVZTrackerMuonIDProducer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ExoVZTrackerMuonIDProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   Handle <edm::View<pat::Muon> > muons;
   Handle <edm::View<reco::Vertex> > vertices;
   
   std::auto_ptr<std::vector<pat::Muon> > outMuonCollection(new std::vector<pat::Muon>);
     
   iEvent.getByToken(MuonToken_, muons);
   iEvent.getByToken(VertexToken_, vertices);
   
   // Loop over the muons, check the ones that pass the IDENTIFICATIO
   for (size_t i=0; i != muons->size(); ++i)
   {
       pat::Muon newMu = (*muons->at(i).clone());
       if (hptm::isTrackerMuon(newMu,vertices->at(0)))
	   newMu.addUserInt("trackerMuon",1);
       else
	   newMu.addUserInt("trackerMuon",0);

       outMuonCollection->push_back(newMu);
   }
   
   iEvent.put(outMuonCollection);
 }

// ------------ method called once each job just before starting event loop  ------------
void 
ExoVZTrackerMuonIDProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ExoVZTrackerMuonIDProducer::endJob() {
}
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ExoVZTrackerMuonIDProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ExoVZTrackerMuonIDProducer);
