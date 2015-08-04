import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/14BC0D64-BB34-E511-8CA3-0025905A48F2.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/76EA27AB-8131-E511-9D44-001E675A6630.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/BEF3B2DB-4B32-E511-A4BB-001E67A3E8CC.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/C2E95B67-BB34-E511-AF0F-003048FFD770.root' ] );


secFiles.extend( [
               ] )

