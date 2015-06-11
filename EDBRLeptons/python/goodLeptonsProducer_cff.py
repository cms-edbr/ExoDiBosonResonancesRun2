import FWCore.ParameterSet.Config as cms

goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
                                       src = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                       cut = cms.string( "chi2 != 0 "
                                                         "& ndof >= 4.0 "
                                                         "& abs(z) <= 24.0 "
                                                         "& abs(position.Rho) <= 2.0 "),
                                       filter = cms.bool(True)
                                       )

goodLeptons = cms.EDProducer("goodLeptonsProducer",
                              vertex = cms.InputTag("goodOfflinePrimaryVertex"),
                              electrons = cms.InputTag("slimmedElectrons"),
                              muons = cms.InputTag("slimmedMuons"),
                              elmediumID = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"),
                              eltightID  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight")
                            )

goodLeptonsProducer = cms.Sequence(goodOfflinePrimaryVertex + goodLeptons)
