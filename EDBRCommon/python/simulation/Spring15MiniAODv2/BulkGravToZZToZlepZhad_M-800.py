import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/60000/DA3836C0-C571-E511-812E-0025904A9472.root' ] );


secFiles.extend( [
               ] )
