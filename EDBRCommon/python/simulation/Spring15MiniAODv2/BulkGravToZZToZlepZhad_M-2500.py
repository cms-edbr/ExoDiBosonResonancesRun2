import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-2500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/38159005-7976-E511-BA87-001E67248A43.root' ] );


secFiles.extend( [
               ] )
