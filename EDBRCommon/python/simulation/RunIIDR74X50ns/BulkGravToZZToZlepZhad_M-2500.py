import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/32AA12A4-9D33-E511-A757-008CFA1974D8.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/5EFC3E81-EA31-E511-B875-3417EBE645D6.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/725C5431-6E33-E511-89D2-0025905964B6.root' ] );


secFiles.extend( [
               ] )

