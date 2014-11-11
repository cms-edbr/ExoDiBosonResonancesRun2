import FWCore.ParameterSet.Config as cms

tightMuons = cms.EDProducer("TightMuonSelector",
                         src = cms.InputTag("slimmedMuons"),
                         vertex = cms.InputTag("offlineSlimmedPrimaryVertices")
                         )