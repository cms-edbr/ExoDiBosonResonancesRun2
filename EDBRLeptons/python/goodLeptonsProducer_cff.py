import FWCore.ParameterSet.Config as cms

goodLeptons = cms.EDProducer("goodLeptonsProducer",
                              vertex = cms.InputTag("goodOfflinePrimaryVertex"),
                              electrons = cms.InputTag("slimmedElectrons"),
                              muons = cms.InputTag("slimmedMuons"),
                              elmediumID = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"),
                              eltightID  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight")
                            )

goodLeptonsProducer = cms.Sequence(goodLeptons)
