import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/6437C7AB-88B8-E511-B237-20CF3019DF14.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/FEBA9529-8DB8-E511-B27A-0025904B5FEE.root' ] );

secFiles.extend( [
               ] )

