import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/70E49EC8-345F-E511-B885-02163E01350A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/74E4B9BD-345F-E511-BE50-02163E01246B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/B65B04BA-345F-E511-9DB2-02163E01346A.root' ] )
