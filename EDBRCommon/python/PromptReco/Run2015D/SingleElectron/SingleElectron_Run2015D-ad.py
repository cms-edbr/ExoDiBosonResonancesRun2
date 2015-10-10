import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/4A424EE3-D75F-E511-A901-02163E0145B9.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/58924A6B-D75F-E511-937D-02163E011C89.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/74BC7275-D75F-E511-A7BA-02163E0146A6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/764F21D7-D75F-E511-8AED-02163E014553.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/88021A74-D75F-E511-AA9D-02163E01465C.root' ] )
