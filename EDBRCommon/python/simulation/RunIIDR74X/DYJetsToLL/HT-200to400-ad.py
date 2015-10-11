import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/06C92FB2-732B-E511-B238-001517FB1944.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/0EB64C7F-1A2D-E511-A084-001E67A406E0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/1457C5A8-732B-E511-836E-90B11C04FE0C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/1C8231EE-6C2F-E511-B891-0026189438CC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/2843DCA5-732B-E511-9691-001E67A3FB9B.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/320177BA-E22B-E511-9AF2-008CFA1C6458.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/40B873ED-6C2F-E511-8DD0-002618943876.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/707573A8-732B-E511-A9F2-001E67A40451.root' ] )
