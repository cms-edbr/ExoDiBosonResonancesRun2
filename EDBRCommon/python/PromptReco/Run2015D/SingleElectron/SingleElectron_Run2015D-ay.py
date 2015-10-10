import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/B2FB4058-9361-E511-B06E-02163E0138C1.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/D0984B6A-9361-E511-91D8-02163E013576.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/DE30B659-9361-E511-B25B-02163E01443C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/E28F8B53-9361-E511-94F7-02163E014752.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/E4A88E58-9361-E511-B29D-02163E0144C4.root' ] )
