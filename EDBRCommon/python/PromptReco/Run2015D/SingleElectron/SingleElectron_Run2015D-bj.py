import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/941/00000/008F855B-1962-E511-A3AC-02163E012A7D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/941/00000/00EBA83B-1962-E511-8A55-02163E014362.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/941/00000/1C84506B-1962-E511-9441-02163E014113.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/941/00000/1CCC9141-1962-E511-8962-02163E0127E5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/941/00000/9E46FD4C-1962-E511-9D91-02163E0127E5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/941/00000/EAC0BB45-1962-E511-A45C-02163E011F3B.root' ] )
