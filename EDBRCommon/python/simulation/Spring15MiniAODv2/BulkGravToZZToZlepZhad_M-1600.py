import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-1600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/60000/5CFEEE73-7270-E511-961B-001EC9ADE1C2.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-1600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/60000/FE470AB7-E878-E511-912F-001EC9ADDDDF.root' ] );


secFiles.extend( [
               ] )
