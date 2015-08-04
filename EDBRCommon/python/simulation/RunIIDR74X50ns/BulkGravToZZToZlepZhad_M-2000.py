import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/8E8959D5-9E33-E511-ABB1-0025B31E3D3C.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/DC22AA20-D632-E511-876E-0CC47A01035C.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/E48AF619-D532-E511-9BBD-001E67A40604.root' ] );


secFiles.extend( [
               ] )

