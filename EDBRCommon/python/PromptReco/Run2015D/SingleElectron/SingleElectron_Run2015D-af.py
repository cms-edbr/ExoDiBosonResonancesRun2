import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/BA5DDB70-D75F-E511-80C8-02163E01349E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/BC36876C-D75F-E511-8FC4-02163E0145EF.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/E255B585-D75F-E511-9255-02163E012AAD.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/E281063F-D85F-E511-8352-02163E0142DA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/F06B278B-D75F-E511-A305-02163E0142AA.root' ] )
