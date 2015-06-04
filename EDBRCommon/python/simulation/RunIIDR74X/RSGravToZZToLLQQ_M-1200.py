import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-1200_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/0E712DCC-A108-E511-B1FF-002590FC5ACC.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-1200_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/50CA0855-9407-E511-A219-00259073E4D6.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-1200_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/AC8105DC-B909-E511-8B64-008CFA197D10.root' ] );


secFiles.extend( [
               ] )

