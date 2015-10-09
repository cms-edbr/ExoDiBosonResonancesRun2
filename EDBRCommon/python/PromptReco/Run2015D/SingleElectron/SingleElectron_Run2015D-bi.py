import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/DE30B659-9361-E511-B25B-02163E01443C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/E28F8B53-9361-E511-94F7-02163E014752.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/E4A88E58-9361-E511-B29D-02163E0144C4.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/F04A318F-9361-E511-8A82-02163E01181F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/FE48CC5B-9361-E511-AD65-02163E0138C1.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/869/00000/0C5CE49F-1B61-E511-9E64-02163E013557.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/926/00000/825C4A4C-4667-E511-A0B1-02163E0126E8.root' ] )
