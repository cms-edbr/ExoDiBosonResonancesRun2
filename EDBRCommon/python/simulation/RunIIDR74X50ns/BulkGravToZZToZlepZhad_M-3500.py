import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/5CB470DC-DE31-E511-BC34-F45214C748D0.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/8242AAEE-D931-E511-AFDF-0CC47A4DED04.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/96001403-DA31-E511-9B13-002481E0DC7C.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/A65506AB-DF31-E511-83DE-0002C90F8088.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/BA3CA8F0-D931-E511-8742-00266CFFA630.root' ] );


secFiles.extend( [
               ] )

