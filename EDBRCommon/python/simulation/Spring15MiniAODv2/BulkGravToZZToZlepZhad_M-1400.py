import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/50EF71E1-9B71-E511-8A5E-003048C7109E.root' ] );


secFiles.extend( [
               ] )
