import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/2687BCAA-3169-E511-8C42-02163E011C4A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/28E2F6AE-3169-E511-99FC-02163E0145BE.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/B0D7E7B3-3169-E511-8967-02163E01361C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/C05EB6B2-3169-E511-9B57-02163E013661.root'] )
