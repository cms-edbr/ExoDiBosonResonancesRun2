import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/968A6F28-9607-E411-B68E-001E6724804D.root',
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/A0BE9D76-9507-E411-A7F1-001E67248A1B.root',
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/A4505D70-4107-E411-B790-001E672488A4.root',
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/AC640F72-4407-E411-B456-001E6724839F.root',
       '/store/mc/Spring14miniaod/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/FA933F36-9607-E411-BB8E-001E67248A1B.root' ] );


secFiles.extend( [
               ] )
