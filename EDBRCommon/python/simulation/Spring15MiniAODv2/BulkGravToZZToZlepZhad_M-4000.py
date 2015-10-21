import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/3831985C-9070-E511-8C9D-90B11C12E856.root' ] );


secFiles.extend( [
               ] )
