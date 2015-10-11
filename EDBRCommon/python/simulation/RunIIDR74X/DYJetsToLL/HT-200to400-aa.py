import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/0CDBE958-D32F-E511-8FD3-002590A4FFE8.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/C21390E5-513A-E511-B37B-002590A81DAC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/CE85AAE3-513A-E511-ADD9-002590200B40.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/006E2431-662B-E511-8D35-001E6758651B.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/00BA650B-D02C-E511-964D-002481CFE834.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/0416B1E0-B82C-E511-9E55-001EC9ED7E42.root' ] )
