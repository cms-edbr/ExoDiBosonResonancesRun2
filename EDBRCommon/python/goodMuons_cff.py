import FWCore.ParameterSet.Config as cms

goodMuons = cms.EDFilter("PATMuonSelector",
                         src = cms.InputTag("goodLeptons:goodMuons"),
                         cut = cms.string("pt > 50 & abs(eta) < 2.1"),
                         filter = cms.bool(False)
                        )

muSequence = cms.Sequence(goodMuons)
