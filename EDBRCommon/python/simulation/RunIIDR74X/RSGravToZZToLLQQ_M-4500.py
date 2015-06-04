import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-4500_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/0E6BC100-2608-E511-81FE-B083FED7685B.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-4500_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/2C69D809-2608-E511-9F6F-AC853DA06A1A.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-4500_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/96B4A5FF-2508-E511-8C7A-AC853D9DACD7.root' ] );


secFiles.extend( [
               ] )

