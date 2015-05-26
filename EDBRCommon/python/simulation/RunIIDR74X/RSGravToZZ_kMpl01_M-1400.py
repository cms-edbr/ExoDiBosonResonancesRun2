import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1400_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/386C045E-5F03-E511-B5E7-3417EBE2EDE2.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1400_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/AC30E28D-5F03-E511-A41B-00259073E4F4.root' ] );


secFiles.extend( [
               ] )

