import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/A844DE13-6232-E511-891E-00259073E4E8.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/C41D9EAD-C232-E511-B92F-90B11C06CD59.root' ] );


secFiles.extend( [
               ] )

