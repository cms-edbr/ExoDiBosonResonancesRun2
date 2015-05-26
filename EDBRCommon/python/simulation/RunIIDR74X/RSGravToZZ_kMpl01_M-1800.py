import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/103DF8E7-6F03-E511-9DB8-003048335516.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/ACB92CD7-6F03-E511-9C52-0025904B582A.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/B655FCD4-6F03-E511-BDF5-0025907B4F6C.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/D68AABD5-6F03-E511-B72D-0025904B6FF6.root' ] );


secFiles.extend( [
               ] )

