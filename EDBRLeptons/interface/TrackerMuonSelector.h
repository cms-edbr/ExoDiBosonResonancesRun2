#ifndef TRACKERMUONSELECTOR_SS6JOFOCFZMGXCPD5LWX2ANI9FNC2MBJ_H
#define TRACKERMUONSELECTOR_SS6JOFOCFZMGXCPD5LWX2ANI9FNC2MBJ_H
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include <bitset>

/// High Pt Muon 
namespace hptm {

    /// Auxiliary function to select muons in the context of high-pt muon
    /// analysis. Could be extended to other analyses, of course.
    bool isTrackerMuon (const reco::Muon& recoMu, const reco::Vertex& vertex) {

	//bool isGlobal = false;
	bool isTracker = false;
	//bool muonChamberHit = false;
	bool matchedStations = false;
	bool relativeError = false;
	bool dBCut = false;
	bool longiCut = false;
	bool pixelHit = false;
	bool trackerLayers = false;
	
	//isGlobal = recoMu.isGlobalMuon();
	isTracker = recoMu.isTrackerMuon();

	matchedStations = (recoMu.numberOfMatchedStations() > 1);
	
	const reco::TrackRef& bestTrackRef = recoMu.muonBestTrack();
	const reco::TrackRef& innerTrackRef = recoMu.innerTrack();
	const reco::TrackRef& trackRef = recoMu.track();

	relativeError = (bestTrackRef->ptError()/bestTrackRef->pt()) < 0.3;
	dBCut         = (fabs(bestTrackRef->dxy(vertex.position())) < 0.2);  
	longiCut      = (fabs(bestTrackRef->dz(vertex.position())) < 0.5);
	
	if(innerTrackRef.isNonnull())
	    pixelHit = (innerTrackRef->hitPattern().numberOfValidPixelHits() > 0);
	
	if(trackRef.isNonnull())
	    trackerLayers = (trackRef->hitPattern().trackerLayersWithMeasurement() > 5);
	
	bool passed = (isTracker and 
		       matchedStations and 
		       relativeError and 
		       dBCut and 
		       longiCut and 
		       pixelHit and 
		       trackerLayers);

  
	return passed;
    }
}
#endif
