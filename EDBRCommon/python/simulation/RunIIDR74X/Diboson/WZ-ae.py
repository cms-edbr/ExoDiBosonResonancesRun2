import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/963E8A98-AD05-E511-ADA7-00304865C244.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A0A3EEAA-1607-E511-A4D9-1CC1DE19285A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A2015043-B405-E511-AC68-00304865C2D0.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A487E395-8B06-E511-8E37-F45214C7B6BA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A4FE1036-B506-E511-A809-AC853D9DAC41.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/AA6933F3-AB05-E511-A25E-002590EFF972.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/B0D8955F-7B06-E511-A3AD-0022195E1F5E.root' ] );
