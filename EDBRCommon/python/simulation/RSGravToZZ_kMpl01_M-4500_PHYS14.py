import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/1898E9B3-9C6B-E411-88A4-00266CF327E0.root',
       '/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/2AED908C-9C6B-E411-9860-0025904B5FAE.root',
       '/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/B655D48B-9C6B-E411-AEDA-0025904B1420.root',
       '/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/BEA3489E-9C6B-E411-B0BC-00266CF32F00.root',
       '/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/10000/70D5490C-C76B-E411-87A9-002590494CC4.root',
       '/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/10000/F8B01395-C56B-E411-A21E-002481E76372.root' ] );


secFiles.extend( [
               ] )
