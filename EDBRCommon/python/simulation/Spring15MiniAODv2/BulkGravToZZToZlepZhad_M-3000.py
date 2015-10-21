import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-3000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/10000/1CFF1176-0471-E511-AA4C-A0000420FE80.root' ] );


secFiles.extend( [
               ] )
