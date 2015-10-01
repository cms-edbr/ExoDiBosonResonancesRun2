import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/866/00000/287DD559-FC60-E511-94B1-02163E0133ED.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/867/00000/02BC905F-2761-E511-B106-02163E01454B.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/867/00000/3E352C5F-2761-E511-9520-02163E014534.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/869/00000/72B30BE7-1261-E511-A4A5-02163E011D35.root' ] );
