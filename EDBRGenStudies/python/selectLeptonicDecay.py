import FWCore.ParameterSet.Config as cms

leptonicDecay = cms.EDFilter("PdgIdAndStatusCandViewSelector",
                             src = cms.InputTag("genParticles"),
                             pdgId = cms.vint32( 11, 13 ),
                             status = cms.vint32( 23 ),
                             filter = cms.bool(True)
                             )
