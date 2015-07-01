import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/3062545B-7412-E511-8555-002590DB91F0.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6001C859-7412-E511-AA2F-047D7BD6DDAC.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/BEB259C8-7312-E511-9179-0002C90B7F94.root' ] );


secFiles.extend( [
               ] )

