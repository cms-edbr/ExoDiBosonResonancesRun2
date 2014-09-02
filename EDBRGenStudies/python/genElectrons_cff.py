import FWCore.ParameterSet.Config as cms

genElectrons = cms.EDFilter("PdgIdAndStatusCandViewSelector",
                            src = cms.InputTag("genParticles"),
                            pdgId = cms.vint32( 11 ),
                            status = cms.vint32(1),
                            )

goodElectrons = cms.EDFilter("CandViewSelector",
                             src = cms.InputTag("genElectrons"),
                             cut = cms.string("pt > 40 & abs(eta) < 2.5 & (abs(eta) < 1.442 || abs(eta) > 1.566)")
                             )

eleSequence = cms.Sequence(genElectrons + goodElectrons)
