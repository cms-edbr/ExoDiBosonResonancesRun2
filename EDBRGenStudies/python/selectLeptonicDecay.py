import FWCore.ParameterSet.Config as cms

leptonicDecay = cms.EDFilter("PdgIdAndStatusCandViewSelector",
                             src = cms.InputTag("prunedGenParticles"),
                             pdgId = cms.vint32( 11, 13 ),
                             status = cms.vint32( 1, 23 ),
                             filter = cms.bool(True)
                             )
