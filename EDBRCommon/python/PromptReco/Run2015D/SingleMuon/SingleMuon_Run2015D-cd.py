import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/2C34CF40-196C-E511-AD95-02163E0146DB.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/30BABD40-196C-E511-A2C0-02163E0146DB.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/34B36B36-196C-E511-B8CF-02163E01389B.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/34CA8933-196C-E511-86C3-02163E0141BC.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/4A031CB6-196C-E511-BE66-02163E0143ED.root' ] )
