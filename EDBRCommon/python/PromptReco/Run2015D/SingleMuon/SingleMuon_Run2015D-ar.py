import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/EEE132CA-E560-E511-853D-02163E0141C1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/F0ECFDAF-E660-E511-9AC6-02163E0122FF.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/866/00000/287DD559-FC60-E511-94B1-02163E0133ED.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/867/00000/02BC905F-2761-E511-B106-02163E01454B.root' ] )
