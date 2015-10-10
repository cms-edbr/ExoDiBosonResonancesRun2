import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/1EBCC17B-D85F-E511-A795-02163E0140F7.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/200CB644-D85F-E511-93EA-02163E014538.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/20360E6E-D75F-E511-82E7-02163E013450.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/209D7E6E-D75F-E511-9593-02163E013450.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/2601EE67-D75F-E511-BD0F-02163E0126EC.root' ] )
