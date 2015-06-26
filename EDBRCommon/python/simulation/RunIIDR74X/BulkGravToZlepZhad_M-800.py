import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-800_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/16BE0367-4F12-E511-A2A0-20CF3027A5CA.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-800_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/4EC10A4D-4F12-E511-8AE4-00266CF9ACB0.root' ] );


secFiles.extend( [
               ] )

