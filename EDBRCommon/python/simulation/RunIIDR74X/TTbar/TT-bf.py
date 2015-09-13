import FWCore.ParameterSet.Config as cms 

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 
readFiles = cms.untracked.vstring() 
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles) 
readFiles.extend( [ 
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/D4A0BF1F-9F0C-E511-9D0D-20CF305B057E.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/D4B60A90-720D-E511-B07B-008CFA00206C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/D6C4CBF5-360D-E511-985A-003048FFCB6A.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/D6D15FF5-360D-E511-A750-0025905A60F8.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/D8294288-D10C-E511-8601-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DA4001F5-360D-E511-AF43-0025905A6088.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DA489955-720D-E511-827E-00266CF24ED4.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DA4BDD46-710D-E511-8908-00266CF27170.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DAB0D4F7-360D-E511-9C50-003048FFD7A2.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DAF96C2B-360D-E511-9294-002618943858.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DAFBF10B-9D0C-E511-8E5B-002590747E1C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DC4751A0-370D-E511-8723-0025905A60D2.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/DEE92D0F-700D-E511-9587-782BCB6A50CA.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/E0E16308-9D0C-E511-9970-0CC47A4D9980.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/E218820B-9D0C-E511-8C1A-0CC47A4DEEE0.root' ] );
