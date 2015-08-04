import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/24854A05-6137-E511-9216-003048341A9C.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/C2C319FA-6037-E511-B464-00259055C872.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/2C79ED26-2233-E511-A765-0CC47A4D9A10.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/4873ACBC-0332-E511-8CCC-0CC47A412A7A.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/7CF0EB2E-9533-E511-8B58-002590E2D9FE.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/C89616A5-9D33-E511-8A8F-008CFA110C74.root' ] );


secFiles.extend( [
               ] )

