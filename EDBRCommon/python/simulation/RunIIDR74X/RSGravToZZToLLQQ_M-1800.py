import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-1800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/00B577DA-0B06-E511-8BC2-00259074AE5C.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-1800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/B67198DD-0B06-E511-9181-549F35AE4FBC.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-1800_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/F248F2B6-0B06-E511-A756-003048947AAA.root' ] );


secFiles.extend( [
               ] )

