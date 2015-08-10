import FWCore.ParameterSet.Config as cms

patElectronsIsoMap = cms.EDProducer("PatElectronMiniIsolationValueMap",
                                     r_iso_min = cms.double(0.05),
                                     r_iso_max = cms.double(0.2),
                                     kt_scale  = cms.double(10.),
                                     charged_only = cms.bool(False),
                                     leptons = cms.InputTag("slimmedElectrons"),
                                     pfCands = cms.InputTag("packedPFCandidates")
                                   )

patMuonsIsoMap = cms.EDProducer("PatMuonMiniIsolationValueMap",
                                     r_iso_min = cms.double(0.05),
                                     r_iso_max = cms.double(0.2),
                                     kt_scale  = cms.double(10.),
                                     charged_only = cms.bool(False),
                                     leptons = cms.InputTag("slimmedMuons"),
                                     pfCands = cms.InputTag("packedPFCandidates")
                               )
