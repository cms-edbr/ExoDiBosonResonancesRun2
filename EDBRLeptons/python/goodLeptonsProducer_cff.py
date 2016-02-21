import FWCore.ParameterSet.Config as cms

goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
                                       src = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                       cut = cms.string( "chi2 != 0 "
                                                         "& ndof >= 4.0 "
                                                         "& abs(z) <= 24.0 "
                                                         "& abs(position.Rho) <= 2.0 "),
                                       filter = cms.bool(True))

electronsMiniIsolationValueMap = cms.EDProducer("PatElectronMiniIsolationValueMap",
                                       r_iso_min = cms.double(0.05),
                                       r_iso_max = cms.double(0.2),
                                       kt_scale  = cms.double(10.),
                                       charged_only = cms.bool(False),
                                       rho     = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                                       leptons = cms.InputTag("slimmedElectrons"),
                                       pfCands = cms.InputTag("packedPFCandidates"))

muonsMiniIsolationValueMap = cms.EDProducer("PatMuonMiniIsolationValueMap",
                                       r_iso_min = cms.double(0.05),
                                       r_iso_max = cms.double(0.2),
                                       kt_scale  = cms.double(10.),
                                       charged_only = cms.bool(False),
                                       rho     = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                                       leptons = cms.InputTag("slimmedMuons"),
                                       pfCands = cms.InputTag("packedPFCandidates"))

goodLeptons = cms.EDProducer("GoodLeptonsProducer",
                                       vertex     = cms.InputTag("goodOfflinePrimaryVertex"),
                                       electrons  = cms.InputTag("slimmedElectrons"),
                                       muons      = cms.InputTag("slimmedMuons"),
                                       elIsoMap   = cms.InputTag("electronsMiniIsolationValueMap:eArea"),
                                       muIsoMap   = cms.InputTag("muonsMiniIsolationValueMap:eArea"),
                                       heep       = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"),
                                       loose      = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose"))

kinElectrons = cms.EDFilter("PATElectronSelector",
                            src = cms.InputTag("goodLeptons:Electrons"),
                            cut = cms.string("pt > 20 & abs(eta) < 2.5 & "+\
                                             "(abs(superCluster().eta()) < 1.442 ||"+\
                                             " abs(superCluster().eta()) > 1.566)"  
                                            )
                            )

idElectrons = cms.EDFilter("PATElectronSelector",
                           src = cms.InputTag("kinElectrons"),
                           cut = cms.string("userInt('LOOSE') == 1")
                           )

isoElectrons = cms.EDFilter("PATElectronSelector",
                            src = cms.InputTag("idElectrons"),
                            cut = cms.string("userFloat('pfIso03R') < 9999.")
                            )

kinMuons = cms.EDFilter("PATMuonSelector",
                        src = cms.InputTag("goodLeptons:Muons"),
                        cut = cms.string("pt > 20 & abs(eta) < 2.4")
                        )

idMuons = cms.EDFilter("PATMuonSelector",
                       src = cms.InputTag("kinMuons"),
                       cut = cms.string("userInt('isTracker') == 1 || userInt('isHighPt') == 1")
                       )

isoMuons = cms.EDFilter("PATMuonSelector",
                        src = cms.InputTag("idMuons"),
                        cut = cms.string("userFloat('miniIso') < 9999.")
                        )

goodLeptonsProducer = cms.Sequence(    goodOfflinePrimaryVertex       +
                                       electronsMiniIsolationValueMap +
                                       muonsMiniIsolationValueMap     +
                                       goodLeptons                    +
                                       kinElectrons +
                                       idElectrons +
                                       isoElectrons +
                                       kinMuons +
                                       idMuons + 
                                       isoMuons
                                       )
