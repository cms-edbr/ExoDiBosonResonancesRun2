import FWCore.ParameterSet.Config as cms


hadronicV = cms.EDFilter("PATJetSelector",
                         src = cms.InputTag("jetsWithTau"),
                         cut = cms.string("pt > 100 & (70.0 < mass < 110.0)")
                         )

hadronicVSequence = cms.Sequence(hadronicV)
