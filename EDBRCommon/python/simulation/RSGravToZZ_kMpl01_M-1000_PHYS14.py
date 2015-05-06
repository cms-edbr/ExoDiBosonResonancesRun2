import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_1000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/C66CD097-5678-E411-A13C-0026189438E4.root',
       '/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_1000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/F08160E2-CF7B-E411-A72C-0026189438E8.root' ] );


secFiles.extend( [
               ] )
