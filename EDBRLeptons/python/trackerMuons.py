import FWCore.ParameterSet.Config as cms

trackerMuons = cms.EDProducer("ExoVZTrackerMuonIDProducer",
                         src = cms.InputTag("slimmedMuons"),
                         vertex = cms.InputTag("offlineSlimmedPrimaryVertices")
                         )
