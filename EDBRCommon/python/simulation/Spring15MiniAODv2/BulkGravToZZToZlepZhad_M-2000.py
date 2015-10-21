import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/60000/586CA654-6576-E511-8369-0025907FD2B2.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/60000/64F37A56-6576-E511-83D2-E41D2D08E0A0.root' ] );


secFiles.extend( [
               ] )
