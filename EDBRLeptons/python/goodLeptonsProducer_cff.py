import FWCore.ParameterSet.Config as cms

goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
                                       src = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                       cut = cms.string( "chi2 != 0 "
                                                         "& ndof >= 4.0 "
                                                         "& abs(z) <= 24.0 "
                                                         "& abs(position.Rho) <= 2.0 "),
                                       filter = cms.bool(True)
                                       )

goodLeptons = cms.EDProducer("GoodLeptonsProducer",
                              r_iso_min    = cms.double(0.05),
                              r_iso_max    = cms.double(0.2),
                              kt_scale     = cms.double(10.),
                              charged_only = cms.bool(False),
                              filter       = cms.bool(True),
                              pfCands      = cms.InputTag("packedPFCandidates"),
                              vertex       = cms.InputTag("goodOfflinePrimaryVertex"),
                              electrons    = cms.InputTag("slimmedElectrons"),
                              muons        = cms.InputTag("slimmedMuons"),
                              modheepID    = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60-NonIso")
                            )

goodLeptonsProducer = cms.Sequence(goodOfflinePrimaryVertex + goodLeptons)
