import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/00A39E61-4A08-E511-97EB-B499BAAB50A0.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/06BDFA30-F908-E511-A4BD-0026B95B8CC9.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/06E1346E-4A08-E511-91A0-6C3BE5B5C0C0.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/20D6C597-F808-E511-B144-782BCB407B74.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/289F01D9-FA08-E511-812C-B083FED73AA1.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/362F3C36-6009-E511-A23C-A4BADB0B6427.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/46E7F01C-C608-E511-A322-00221982D6CC.root' ] );
