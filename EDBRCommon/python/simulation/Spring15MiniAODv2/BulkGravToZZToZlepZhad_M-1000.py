import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-1000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/10000/6EE974B3-5471-E511-9146-F7599BFA28FD.root' ] );


secFiles.extend( [
               ] )
