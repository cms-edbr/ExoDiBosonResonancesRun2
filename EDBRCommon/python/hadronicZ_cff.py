import FWCore.ParameterSet.Config as cms

hadronicV = cms.EDFilter("PATJetSelector",
                         src = cms.InputTag("cleanJets"),
                         cut = cms.string("70. < mass < 110.")
                         )

hadronicVSequence = cms.Sequence(hadronicV)
