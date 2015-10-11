import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/22A9821F-0D3A-E511-A2E4-00259020083C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/548FDA0F-113A-E511-9A32-002590A3CA16.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/6CEC27D8-023B-E511-B2F0-F04DA23BBCCA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/8A1E68C0-023B-E511-BCAE-001E67398CE1.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/8E1D07A4-D73A-E511-B107-002590A8312A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/98B18BFC-113A-E511-A729-002590A371D4.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/D8F92421-0D3A-E511-8CE5-001E67396D56.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/30000/DA552AEA-D03A-E511-B1A4-00259048A862.root' ] )
