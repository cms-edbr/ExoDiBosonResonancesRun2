import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/2E4D3E63-1906-E511-A8C4-0CC47A0AD6F8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/3EB756A4-AA05-E511-A06A-0025900E3508.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/44CC27C7-AA05-E511-BEE4-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/4A356134-CC05-E511-AD9C-008CFA064858.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/4C103433-4E07-E511-A2A0-B083FED73FEC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/501D689D-AA05-E511-A54A-0CC47A13CEAC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/52BC606A-6606-E511-8509-6CC2173D57C0.root' ] );
