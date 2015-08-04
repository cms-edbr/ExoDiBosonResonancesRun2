import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/A257616D-6338-E511-8206-00259073E52A.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/B2A9F509-9B36-E511-B939-02163E01192D.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/12D84B67-5D32-E511-91CD-44A84225CDFE.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/443F8768-F131-E511-915F-02163E00F8AE.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/623BF870-5D32-E511-AAAF-02163E00F4DF.root' ] );


secFiles.extend( [
               ] )

