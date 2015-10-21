import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/60000/A22AE694-4671-E511-97A7-00259055C872.root' ] );


secFiles.extend( [
               ] )
