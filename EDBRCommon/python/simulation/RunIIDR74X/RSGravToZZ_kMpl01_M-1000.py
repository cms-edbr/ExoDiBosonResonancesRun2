import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/3277D845-A303-E511-9B71-00259073E51E.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/4E5AA245-A303-E511-A588-0025901D4ADE.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/886D6A9B-A603-E511-8737-0025905B858E.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/941D2499-A603-E511-A982-0025905A606A.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-1000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/B457A34A-A303-E511-B02E-002590DB91CE.root' ] );


secFiles.extend( [
               ] )

