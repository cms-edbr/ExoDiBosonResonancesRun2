import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/ZZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v3/10000/EE7E1D22-7209-E511-9DFA-00259048A87C.root',
       '/store/mc/RunIISpring15DR74/ZZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v3/10000/F0175045-7209-E511-80DA-0025904C68DA.root',
       '/store/mc/RunIISpring15DR74/ZZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v3/50000/7EFD7005-B508-E511-8F56-003048947BBB.root',
       '/store/mc/RunIISpring15DR74/ZZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v3/50000/8C77C263-B408-E511-9473-0025905C3DF6.root',
       '/store/mc/RunIISpring15DR74/ZZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v3/50000/B6F07B74-B508-E511-970D-0025905C3DF6.root' ] );
