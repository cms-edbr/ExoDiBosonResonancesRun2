import FWCore.ParameterSet.Config as cms

goodMuons = cms.EDFilter("CandViewSelector",
                         src = cms.InputTag("slimmedMuons"),
                         cut = cms.string("pt > 40 & abs(eta) < 2.4")
                         )

muSequence = cms.Sequence(goodMuons)
