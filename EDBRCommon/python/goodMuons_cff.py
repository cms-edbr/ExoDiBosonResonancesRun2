import FWCore.ParameterSet.Config as cms

goodMuons = cms.EDFilter("PATMuonSelector",
                         src = cms.InputTag("goodLeptons:goodMuons"),
                         cut = cms.string("pt > 40 & abs(eta) < 2.5"),
                         filter = cms.bool(False)
                        )

muSequence = cms.Sequence(goodMuons)
