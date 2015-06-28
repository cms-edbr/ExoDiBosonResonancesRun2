import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/60218D7B-C712-E511-9B03-90B11C070100.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/F06DDF83-C712-E511-92EA-0025907253E0.root' ] );


secFiles.extend( [
               ] )

