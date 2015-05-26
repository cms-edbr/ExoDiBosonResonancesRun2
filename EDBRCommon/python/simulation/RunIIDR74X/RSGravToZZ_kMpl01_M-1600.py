import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1600_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/32DAEB8E-8403-E511-A92B-0002C94CD040.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1600_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/82464CDB-8403-E511-A511-0025905A48D0.root' ] );


secFiles.extend( [
               ] )

