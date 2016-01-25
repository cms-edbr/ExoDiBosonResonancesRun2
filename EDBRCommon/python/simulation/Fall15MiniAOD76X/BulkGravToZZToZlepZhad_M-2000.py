import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/A4554396-41B8-E511-B299-00221982D02D.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/50000/983B71D0-BDB8-E511-8ACC-20CF3019DF0B.root' ] );

secFiles.extend( [
               ] )

