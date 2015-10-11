import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/A82C36D2-7D2C-E511-BD7E-00259021A53E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/AAAB24AC-C22A-E511-960A-02163E00B1FF.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/AEF899F5-4029-E511-8DEF-002354EF3BD2.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/C040B733-5730-E511-9CE7-6CC2173BC060.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/C4727001-5C28-E511-8380-0025905B858E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/C86646B0-7528-E511-A67F-0025905A6136.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/CC6555F0-F929-E511-A094-0002C90C4FC6.root' ] )
