import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/A061779A-5212-E511-A0F7-00266CF9B874.root' ] );


secFiles.extend( [
               ] )

