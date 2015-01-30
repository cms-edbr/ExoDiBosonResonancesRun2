import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_4000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v2/00000/080A200F-FC81-E411-BAE7-00A0D1EE27B0.root' ] );


secFiles.extend( [
               ] )
