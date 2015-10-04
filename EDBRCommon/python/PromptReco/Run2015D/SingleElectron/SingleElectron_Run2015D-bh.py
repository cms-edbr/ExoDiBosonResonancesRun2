import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/1ED7C757-9361-E511-A10A-02163E012B11.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/50648A5D-9361-E511-8B5E-02163E013520.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/5AAE9760-9361-E511-82FF-02163E014249.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/B2FB4058-9361-E511-B06E-02163E0138C1.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/D0984B6A-9361-E511-91D8-02163E013576.root' ] )
