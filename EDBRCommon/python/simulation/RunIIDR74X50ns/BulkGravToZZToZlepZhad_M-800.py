import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-800_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/580FE5FE-D538-E511-8571-008CFA165F5C.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-800_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/BA67AD3B-D538-E511-9B65-008CFA110AEC.root' ] );


secFiles.extend( [
               ] )

