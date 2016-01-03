import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/00FB2975-D8AF-E511-97F0-842B2B292627.root',
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/228EA92B-D9AF-E511-9D4C-001E67A3F8A8.root' ] );


secFiles.extend( [
               ] )

