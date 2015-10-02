import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/04A8EBBF-345F-E511-A729-02163E01435B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/1AA77AC6-345F-E511-8175-02163E0126BC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/705E47C4-345F-E511-BD2B-02163E014638.root' ] )
