import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/8663653F-F607-E511-8F33-D4AE526A0D22.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/8C0EB125-1709-E511-A30C-6C3BE5B59150.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/A2C4B5DB-F408-E511-B9AF-000F530E46D8.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/A876CE70-3E09-E511-A15B-00259073E3B6.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/BCAEA88A-3509-E511-A69F-000F530E46DC.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/BEA00C19-0409-E511-8D96-842B2B18192E.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/C2E92277-F208-E511-B163-02163E012028.root' ] );
