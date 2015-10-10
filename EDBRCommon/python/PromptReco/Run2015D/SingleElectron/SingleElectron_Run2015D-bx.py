import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/F886AE2A-8A68-E511-93E4-02163E01378A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/FCC1631D-8A68-E511-9ABB-02163E0134B6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/804/00000/16B516BD-7568-E511-BB79-02163E011919.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/0E677B3D-B468-E511-BB9E-02163E0146B9.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/3645D13B-B468-E511-96D5-02163E01453F.root' ] )
