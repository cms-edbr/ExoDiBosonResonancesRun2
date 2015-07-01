import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/36809FFF-6314-E511-8955-0CC47A4DEE9A.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/4018D9B5-6314-E511-B597-0025905A6132.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/60C92BA6-6314-E511-89FD-001E675811CC.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/8E7FCAB9-6314-E511-9D62-0025905A60BE.root' ] );


secFiles.extend( [
               ] )

