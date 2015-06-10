import FWCore.ParameterSet.Config as cms

miniIsolation = cms.EDProducer("miniPFIsolationProducer",
                                r_iso_min = cms.double(0.05),
                                r_iso_max = cms.double(0.2),
                                kt_scale  = cms.double(10.),
                                charged_only = cms.bool(False),
                                electrons = cms.InputTag("goodElectrons"),
                                muons = cms.InputTag("goodMuons"),
                                pfCands = cms.InputTag("packedPFCandidates")
                              )

miniPFIsolationProducer = cms.Sequence(miniIsolation)
