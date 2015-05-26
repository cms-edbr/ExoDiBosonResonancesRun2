import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/C43FC883-8E03-E511-856C-0025905A60D2.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/E2BF5584-8A03-E511-91F4-B083FED76C6C.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/E4946287-8A03-E511-A047-002590D0AFDC.root' ] );


secFiles.extend( [
               ] )

