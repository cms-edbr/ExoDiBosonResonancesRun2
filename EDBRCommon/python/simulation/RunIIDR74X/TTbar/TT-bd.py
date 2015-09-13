import FWCore.ParameterSet.Config as cms 

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 
readFiles = cms.untracked.vstring() 
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles) 
readFiles.extend( [ 
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/9A77AFF5-360D-E511-B508-003048FFCC2C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/9C14608C-370D-E511-9285-0026189438EA.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/9E5D1003-9E0C-E511-9441-0CC47A4DEEE0.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A0574882-D10C-E511-B885-00074305CFF2.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A07AAC4B-710D-E511-8B31-00266CF9B630.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A0A4C5A1-370D-E511-B34D-0025905A6060.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A0A8B27C-D00C-E511-BE75-0002C94CD120.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A0AFA28B-CF0C-E511-B16F-0002C94CD0BC.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A0FEB868-D30C-E511-8137-0002C94CD0BC.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A2E2A678-D10C-E511-A105-0002C94CD12E.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A83B84F4-360D-E511-A570-0025905A4964.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/A8A3DDC1-DA0C-E511-A449-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/AC4FEDF5-360D-E511-A312-0025905964C2.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/AE0B1C99-CF0C-E511-92DD-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/70000/B0C87C4E-720D-E511-A7AC-00266CF9B034.root' ] );
