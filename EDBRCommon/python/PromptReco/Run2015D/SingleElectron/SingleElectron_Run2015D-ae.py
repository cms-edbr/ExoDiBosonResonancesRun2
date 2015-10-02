import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/CAE5CFD7-345F-E511-87C0-02163E01363C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/CECD47C4-345F-E511-BA52-02163E014638.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/E41946C8-345F-E511-B2C0-02163E014335.root' ] )
