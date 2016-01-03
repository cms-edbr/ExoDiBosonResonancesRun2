import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/50000/901318E1-76AF-E511-A589-02163E0179AE.root',
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/50000/DCB48FEA-76AF-E511-9FD1-782BCB538FDF.root' ] );


secFiles.extend( [
               ] )

