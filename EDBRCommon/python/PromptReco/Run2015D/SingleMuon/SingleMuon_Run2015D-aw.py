import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/867/00000/02BC905F-2761-E511-B106-02163E01454B.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/867/00000/3E352C5F-2761-E511-9520-02163E014534.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/06B98136-A961-E511-A8D0-02163E01439C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/1840F038-A961-E511-A6FD-02163E0133F8.root' ] )
