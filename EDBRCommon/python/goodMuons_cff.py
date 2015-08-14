import FWCore.ParameterSet.Config as cms

goodMuons = cms.EDFilter("PATMuonSelector",
                         src = cms.InputTag("goodLeptons:goodMuons"),
                         cut = cms.string(""),
                         filter = cms.bool(False)
                        )

muSequence = cms.Sequence(goodMuons)
