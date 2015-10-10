import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/DC70E232-D829-E511-9357-001E67A42161.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/DECBBEDF-C429-E511-9961-02163E0120D4.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/E82E2627-B829-E511-A6AC-002618FDA287.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/EAA7714B-0029-E511-A731-001E675A6AB8.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/F43B1859-4A32-E511-ACA6-008CFA1111EC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/F6C68F7E-0629-E511-8A3C-008CFA05E8F0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/FE5718B2-A02A-E511-AE23-001E67504D15.root' ] )
