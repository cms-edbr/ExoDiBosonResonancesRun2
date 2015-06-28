import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/0444A3D7-BB12-E511-9CF4-D485645943AC.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/EAF461AA-1A13-E511-8C64-20CF3027A5CC.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/EC2D11F7-1A13-E511-9370-00266CFFCB80.root' ] );


secFiles.extend( [
               ] )

