import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/58F8AABD-AA05-E511-A012-0025904A8ED2.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/5E7E951F-7C06-E511-9768-002590D8C71A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/60A678D4-AB05-E511-AA44-00259077501E.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/6E7618ED-E705-E511-9DAC-842B2B76653D.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/709A26D5-1B06-E511-816A-0CC47A0AD668.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/76AB2A80-D706-E511-AA56-002590AC4B5A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/7CD3F556-BB07-E511-85AB-002590A370DC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/8A6E0BF5-AB05-E511-ABD1-0CC47A13CB36.root' ] );
