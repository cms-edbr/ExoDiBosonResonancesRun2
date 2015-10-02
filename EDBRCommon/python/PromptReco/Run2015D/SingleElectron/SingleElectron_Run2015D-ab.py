import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/043AB467-D75F-E511-808D-02163E011DCC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/04B66463-D75F-E511-94D9-02163E01465C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/182CE8AF-D75F-E511-81FE-02163E01441B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/1EBCC17B-D85F-E511-A795-02163E0140F7.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/200CB644-D85F-E511-93EA-02163E014538.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/20360E6E-D75F-E511-82E7-02163E013450.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/209D7E6E-D75F-E511-9593-02163E013450.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/2601EE67-D75F-E511-BD0F-02163E0126EC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/4A424EE3-D75F-E511-A901-02163E0145B9.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/58924A6B-D75F-E511-937D-02163E011C89.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/74BC7275-D75F-E511-A7BA-02163E0146A6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/764F21D7-D75F-E511-8AED-02163E014553.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/88021A74-D75F-E511-AA9D-02163E01465C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/8EBDFB7B-D75F-E511-9318-02163E0146C3.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/9673636F-D75F-E511-B414-02163E0145C4.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/96DE2B9B-D75F-E511-BA2D-02163E01453C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/AE28EE67-D75F-E511-9191-02163E0126EC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/B6EE076C-D75F-E511-AD8E-02163E0145EF.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/BA5DDB70-D75F-E511-80C8-02163E01349E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/BC36876C-D75F-E511-8FC4-02163E0145EF.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/E255B585-D75F-E511-9255-02163E012AAD.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/E281063F-D85F-E511-8352-02163E0142DA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/676/00000/F06B278B-D75F-E511-A305-02163E0142AA.root' ] )
