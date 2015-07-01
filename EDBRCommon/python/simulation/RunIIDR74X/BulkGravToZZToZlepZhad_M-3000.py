import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/10000/5C3483F7-3613-E511-9C80-90B11C06DD39.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/10000/82A0EA3A-4513-E511-89E1-A0369F301924.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/10000/969BD035-4613-E511-879D-0026182FD7A3.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3000_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/10000/D238AD20-4613-E511-90E5-20CF305B0519.root' ] );


secFiles.extend( [
               ] )

