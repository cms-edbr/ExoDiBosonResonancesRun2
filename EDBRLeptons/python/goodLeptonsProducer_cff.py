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
                                       leptons = cms.InputTag("slimmedElectrons"),
                                       pfCands = cms.InputTag("packedPFCandidates"))

muonsMiniIsolationValueMap = cms.EDProducer("PatMuonMiniIsolationValueMap",
                                       r_iso_min = cms.double(0.05),
                                       r_iso_max = cms.double(0.2),
                                       kt_scale  = cms.double(10.),
                                       charged_only = cms.bool(False),
                                       leptons = cms.InputTag("slimmedMuons"),
                                       pfCands = cms.InputTag("packedPFCandidates"))

goodLeptons = cms.EDProducer("GoodLeptonsProducer",
                                       filter     = cms.bool(True),
                                       vertex     = cms.InputTag("goodOfflinePrimaryVertex"),
                                       electrons  = cms.InputTag("slimmedElectrons"),
                                       muons      = cms.InputTag("slimmedMuons"),
                                       elIsoMap   = cms.InputTag("electronsMiniIsolationValueMap:eArea"),
                                       muIsoMap   = cms.InputTag("muonsMiniIsolationValueMap:eArea"),
                                       heepV60    = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"))

goodElectrons = cms.EDFilter("PATElectronSelector",
                                       src = cms.InputTag("goodLeptons:Electrons"),
                                       cut = cms.string("pt > 35 & abs(eta) < 2.5"))

goodMuons = cms.EDFilter("PATMuonSelector",
                                       src = cms.InputTag("goodLeptons:Muons"),
                                       cut = cms.string("pt > 20 & abs(eta) < 2.4"))

goodLeptonsProducer = cms.Sequence(    goodOfflinePrimaryVertex       +
                                       electronsMiniIsolationValueMap +
                                       muonsMiniIsolationValueMap     +
                                       goodLeptons                    +
                                       goodElectrons                  +
                                       goodMuons                      )
