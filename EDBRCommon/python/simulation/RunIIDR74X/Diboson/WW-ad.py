import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/380653DA-F408-E511-829F-782BCB27BA01.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/5E45E2D1-F408-E511-9D9B-000F530E4AB0.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/6667190C-0409-E511-9F2A-001EC9B2118C.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/6E3F7018-0709-E511-B085-B499BAAC0068.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/76D25462-F208-E511-983A-00221982C61D.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/7C4A7018-0709-E511-A097-B499BAAC0068.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/80F1144B-3E09-E511-A431-000F530E4780.root' ] );
