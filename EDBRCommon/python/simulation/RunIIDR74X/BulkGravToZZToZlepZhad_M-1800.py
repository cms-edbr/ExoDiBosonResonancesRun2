import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1800_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/121A89AD-5713-E511-A8CE-0025905B8598.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1800_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/1E8242AD-5713-E511-8CEA-00259059642E.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1800_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/BA363894-5713-E511-9199-0CC47A4DEE08.root' ] );


secFiles.extend( [
               ] )

