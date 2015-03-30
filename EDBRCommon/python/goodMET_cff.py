import FWCore.ParameterSet.Config as cms

goodMET = cms.EDFilter("PATMETSelector",
                             src = cms.InputTag("slimmedMETs"),
                             cut = cms.string("pt >40")
       #                      cut = cms.string("pt > 250")
                             )

metSequence = cms.Sequence(goodMET)
