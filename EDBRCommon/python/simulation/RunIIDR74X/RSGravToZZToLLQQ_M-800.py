import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/0EE1A750-9E06-E511-8529-782BCB717588.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/64FFF5FA-6D06-E511-9688-B083FED76D99.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/882F9653-9E06-E511-9813-003048FFCB6A.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/DA31905D-6406-E511-B982-001E688651D4.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/70000/DAC99454-9E06-E511-9A3E-00261894397F.root' ] );


secFiles.extend( [
               ] )

