import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/3A1CAFDF-EC5F-E511-A2E0-02163E014796.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/566E27EA-EC5F-E511-BBE6-02163E012B6F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/7E518A1A-EF5F-E511-9C72-02163E0145EF.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/A08C89B5-ED5F-E511-97D9-02163E014649.root' ] )
