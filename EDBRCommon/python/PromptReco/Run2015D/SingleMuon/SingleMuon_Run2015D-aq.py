import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/0A26F9D0-E560-E511-B29A-02163E013918.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/201CB0C7-E560-E511-BB1F-02163E013425.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/2E82FAEF-E560-E511-A95B-02163E01410D.root' ] )
