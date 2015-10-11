import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/5EBD97DD-252B-E511-BBDC-0025905A48EC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/72AD4589-272B-E511-BAD8-003048FFCB74.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/A070F099-542E-E511-A1DC-001F29072C1E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/AC8543CE-372A-E511-A232-02163E00E833.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/D2F9B5A9-8030-E511-90FB-002481E94C56.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/D82C9AEB-5529-E511-A851-02163E011827.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/DE1CD6AC-6F30-E511-949D-003048F02CBA.root' ] )
