import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1600_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/C25F783B-A732-E511-8C70-02163E0133FF.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1600_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/F0DA0D84-A732-E511-AF52-3417EBE6471A.root' ] );


secFiles.extend( [
               ] )

