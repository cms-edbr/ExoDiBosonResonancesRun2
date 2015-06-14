import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/347935FC-6812-E511-ADF5-20CF3027A5CC.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/5EF1A8A1-6712-E511-840D-00259074AE52.root' ] );


secFiles.extend( [
               ] )

