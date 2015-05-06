import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_2000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v2/10000/6E02E34E-8876-E411-BC19-003048D3739C.root' ] );

secFiles.extend( [
               ] )
