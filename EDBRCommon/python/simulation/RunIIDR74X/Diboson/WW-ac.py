import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A2F91C54-4A08-E511-8171-6C3BE5B5F228.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/B67A4E30-6009-E511-A074-842B2B298D0B.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/D072628A-4A08-E511-9B31-6C3BE5B5B078.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/E06D662B-F908-E511-942F-B083FED73AA1.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/E6C0F92C-6009-E511-902A-000F5327372C.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/ECC168E0-FA08-E511-AE2F-782BCB407B74.root',
       '/store/mc/RunIISpring15DR74/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/F2C55628-6009-E511-8CA8-6C3BE5B58198.root' ] );
