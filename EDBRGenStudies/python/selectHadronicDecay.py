import FWCore.ParameterSet.Config as cms

hadronicDecay = cms.EDFilter("PdgIdAndStatusCandViewSelector",
                             src = cms.InputTag("genParticles"),
                             pdgId = cms.vint32( 1, 2, 3, 4, 5 ),
                             status = cms.vint32( 23 ),
                             filter = cms.bool(True)
                             )
