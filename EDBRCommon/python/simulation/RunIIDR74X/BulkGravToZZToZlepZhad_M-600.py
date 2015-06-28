import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/24A9CF37-0D14-E511-87CB-0025904B1426.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/A86DBAEE-3C13-E511-88AE-02163E01374A.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/C87BEC55-3E13-E511-BB93-E41D2D08DC90.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/CCE02AFD-0D13-E511-A01F-02163E0141EB.root',
       '/store/mc/RunIISpring15DR74/BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/D2FDB966-3D13-E511-AD8D-002590D8C740.root' ] );


secFiles.extend( [
               ] )

