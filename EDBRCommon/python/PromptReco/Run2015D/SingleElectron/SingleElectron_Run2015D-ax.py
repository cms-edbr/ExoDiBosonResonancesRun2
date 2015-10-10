import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/0C3D6566-9361-E511-8377-02163E0137F3.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/1C2AEC73-9361-E511-8942-02163E014610.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/1ED7C757-9361-E511-A10A-02163E012B11.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/50648A5D-9361-E511-8B5E-02163E013520.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/5AAE9760-9361-E511-82FF-02163E014249.root' ] )
