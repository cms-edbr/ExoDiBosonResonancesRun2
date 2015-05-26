import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-600_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/4C53E4B0-5E03-E511-9A3E-7845C4FC3B69.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-600_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/DC836565-5E03-E511-900B-008CFA197A5C.root' ] );


secFiles.extend( [
               ] )

