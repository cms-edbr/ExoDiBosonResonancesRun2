import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/06DC9FC8-F55F-E511-8214-02163E011D99.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/120A295C-FE5F-E511-9B21-02163E0135B5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/1A94C275-F05F-E511-883F-02163E014100.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/1E0FBF1E-EF5F-E511-8676-02163E0141BA.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/281931F2-EA5F-E511-B684-02163E013863.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/30CD8613-EF5F-E511-93D1-02163E0141A8.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/3A1CAFDF-EC5F-E511-A2E0-02163E014796.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/566E27EA-EC5F-E511-BBE6-02163E012B6F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/7E518A1A-EF5F-E511-9C72-02163E0145EF.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/A08C89B5-ED5F-E511-97D9-02163E014649.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/B4AD6B53-ED5F-E511-A05B-02163E0143BA.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/B6BFF15E-ED5F-E511-A6E3-02163E0133E4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/C2D5A4CC-F55F-E511-A02A-02163E0123FC.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/E0DD2F18-EF5F-E511-B423-02163E0146E4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/FCCE68ED-EC5F-E511-8F08-02163E01465A.root' ] )
