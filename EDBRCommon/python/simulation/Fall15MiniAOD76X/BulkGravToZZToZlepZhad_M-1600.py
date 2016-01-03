import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-1600_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/60000/50633C9F-70AF-E511-B24A-1418774105B6.root',
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-1600_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/60000/F6137BBE-70AF-E511-B21B-002590D9D8B6.root' ] );


secFiles.extend( [
               ] )

