import FWCore.ParameterSet.Config as cms 

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 
readFiles = cms.untracked.vstring() 
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles) 
readFiles.extend( [ 
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/4AB71F09-500D-E511-806D-002590747D90.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/4C054876-750C-E511-AE3F-008CFA56D794.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/4CA5D1FF-840D-E511-8239-0025900E3502.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/54137161-0E0D-E511-AA89-0CC47A13D09C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/54AE4C3B-7C0D-E511-9AAB-0025905A60EE.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/5843BC1E-7C0D-E511-9DD7-0025905A6136.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/5E33B95D-0E0D-E511-92C2-002590E3A0EE.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/62D970E7-810D-E511-9F64-00259073E3FE.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/645E7A61-0E0D-E511-AD11-0CC47A13D09C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/684829D7-740C-E511-8D99-00266CFCCB44.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/86D72E44-4F0D-E511-ADA1-00259073E3CE.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/8A1F2E5D-0E0D-E511-9552-0CC47A13CBEA.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/90A3B61D-7C0D-E511-BB18-002590593876.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/9CAC857A-0E0D-E511-B059-002590E3A0D4.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/60000/A06D976C-0E0D-E511-8BF7-003048F5B2B4.root' ] );
