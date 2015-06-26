import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/946E5431-5B12-E511-8B2E-002590DB9152.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/98A91928-5B12-E511-92B6-002590A2CCE6.root' ] );


secFiles.extend( [
               ] )

