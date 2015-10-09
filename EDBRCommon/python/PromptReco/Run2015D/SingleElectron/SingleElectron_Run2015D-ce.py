import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/96ED9034-8A68-E511-83E9-02163E012B51.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/C89EDF2F-8A68-E511-8E7B-02163E011E32.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/F886AE2A-8A68-E511-93E4-02163E01378A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/FCC1631D-8A68-E511-9ABB-02163E0134B6.root' ] )
