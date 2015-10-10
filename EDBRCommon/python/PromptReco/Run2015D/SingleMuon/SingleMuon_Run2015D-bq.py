import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/90F786E8-1769-E511-A949-02163E013916.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/FE71400F-1869-E511-B1E3-02163E01441C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/2687BCAA-3169-E511-8C42-02163E011C4A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/28E2F6AE-3169-E511-99FC-02163E0145BE.root' ] )
