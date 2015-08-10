import FWCore.ParameterSet.Config as cms

from ExoDiBosonResonances.EDBRLeptons.miniPFIsolationProducer_cff import *

goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
                                       src = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                       cut = cms.string( "chi2 != 0 "
                                                         "& ndof >= 4.0 "
                                                         "& abs(z) <= 24.0 "
                                                         "& abs(position.Rho) <= 2.0 "),
                                       filter = cms.bool(True)
                                       )

goodLeptons = cms.EDProducer("GoodLeptonsProducer",
                              filter       = cms.bool(True),
                              pfCands      = cms.InputTag("packedPFCandidates"),
                              vertex       = cms.InputTag("goodOfflinePrimaryVertex"),
                              electrons    = cms.InputTag("slimmedElectrons"),
                              muons        = cms.InputTag("slimmedMuons"),
                              elIsoMap     = cms.InputTag("patElectronsIsoMap:miniIsolation"),
                              muIsoMap     = cms.InputTag("patMuonsIsoMap:miniIsolation"),
                              heepV60ID    = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60")
                            )

goodLeptonsProducer = cms.Sequence(goodOfflinePrimaryVertex + patElectronsIsoMap + patMuonsIsoMap + goodLeptons)
