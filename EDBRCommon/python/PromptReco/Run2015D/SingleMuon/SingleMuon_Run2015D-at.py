import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/84861ECC-E560-E511-91A1-02163E01387D.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/A29FDCCC-E560-E511-9203-02163E0119F5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/843/00000/B8C5F5D6-E560-E511-BB13-02163E0128B2.root' ] )
