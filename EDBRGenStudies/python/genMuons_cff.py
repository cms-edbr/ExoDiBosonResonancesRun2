import FWCore.ParameterSet.Config as cms

genMuons = cms.EDFilter("PdgIdAndStatusCandViewSelector",
                            src = cms.InputTag("genParticles"),
                            pdgId = cms.vint32( 13 ),
                            status = cms.vint32(1),
                            )

goodMuons = cms.EDFilter("CandViewSelector",
                         src = cms.InputTag("genMuons"),
                         cut = cms.string("pt > 40 & abs(eta) < 2.4")
                         )

muSequence = cms.Sequence(genMuons + goodMuons)
