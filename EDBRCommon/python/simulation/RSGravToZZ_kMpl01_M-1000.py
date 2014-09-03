import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-1000_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/00CEB50F-9D07-E411-9DBB-002590182FD8.root',
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-1000_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/70529AC9-3707-E411-98D0-0025902CF9E2.root',
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-1000_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/7CEB3A30-3607-E411-964D-003048C7109E.root',
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-1000_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/FCB22594-3B07-E411-8C3D-0025902D959A.root' ] );


secFiles.extend( [
               ] )
