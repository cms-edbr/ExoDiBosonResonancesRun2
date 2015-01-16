import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/00000/6C316E89-836F-E411-A3D7-00266CFFA6A8.root',
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/00000/8047AB86-836F-E411-80B8-002481E0DC4E.root',
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/10000/5E8C5398-0A70-E411-9538-0025904B1420.root',
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/10000/CA90E2E0-3976-E411-B96E-002590AC4C72.root',
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/10000/E2D1D38A-0A70-E411-BF6E-0025907FD424.root' ] );


secFiles.extend( [
               ] )
