import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/6ECE4C1A-2FAF-E511-BD58-003048F5B300.root',
       '/store/mc/RunIIFall15MiniAODv1/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/AC68BE11-2FAF-E511-B3F3-0CC47A57CC8A.root' ] );


secFiles.extend( [
               ] )

