import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        '/store/user/tomei/DYJetsToLL_M-50_HT-200to400_Tune4C_13TeV-madgraph-tauola/Spring14dr-PU20bx25_POSTLS170_V7AN1-miniAOD706p1/140717_173448/0000/miniAOD-prod_PAT_99.root'
        )
                            )

process.jetsWithNSubj = cms.EDProducer("EDBRNJettinessAdder",
                                       src = cms.InputTag("slimmedJetsAK8"),
                                       cone = cms.double(0.8)
                                       )

process.p = cms.Path(process.jetsWithNSubj)
