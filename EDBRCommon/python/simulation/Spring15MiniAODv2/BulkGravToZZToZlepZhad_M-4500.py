import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v2/40000/7496C9E4-4475-E511-BE93-008CFA197A5C.root' ] );


secFiles.extend( [
               ] )
