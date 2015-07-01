import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/2CD5B7F6-0013-E511-BA98-002590D0AFD0.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/42292EFD-0013-E511-93AE-B083FED76520.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/C05F1304-0113-E511-9D0A-0025B3E0654E.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/EA211D18-0113-E511-8431-000F530E4644.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/FA3CFA00-0113-E511-AF9D-842B2B28EB06.root' ] );


secFiles.extend( [
               ] )

