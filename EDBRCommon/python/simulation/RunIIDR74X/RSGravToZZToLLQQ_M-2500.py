import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-2500_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/10000/1AB55023-0B07-E511-93DD-00259057490C.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-2500_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/10000/3A54E7EB-0A07-E511-B573-00266CFAEA68.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZToLLQQ_kMpl01_M-2500_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/10000/EA098920-0B07-E511-8F5E-0025905A60D2.root' ] );


secFiles.extend( [
               ] )

