import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/136/00000/56FB5790-BF6A-E511-BFC2-02163E0143D7.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/136/00000/96368FA1-BF6A-E511-ADEF-02163E0144B7.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/157/00000/62035E25-1A6B-E511-A9BE-02163E01358D.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/157/00000/8EB21524-1A6B-E511-92A1-02163E01358D.root' ] )
