import FWCore.ParameterSet.Config as cms

genMET = cms.EDFilter("PdgIdAndStatusCandViewSelector",
                            src = cms.InputTag("genParticles"),
                            pdgId = cms.vint32( 12,14,16 ),
                            status = cms.vint32(1),
                            )

goodMET = cms.EDFilter("CandViewSelector",
                             src = cms.InputTag("genMET"),
                             cut = cms.string("pt > 40")
                             )

metSequence = cms.Sequence(genMET + goodMET)
