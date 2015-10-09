import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/36B5B7F4-1769-E511-A869-02163E0143D5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/36CE7824-1869-E511-BF31-02163E0133FC.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/3AB91C69-1869-E511-8F9E-02163E014520.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/484A330A-2169-E511-BB1E-02163E014671.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/90F786E8-1769-E511-A949-02163E013916.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/805/00000/FE71400F-1869-E511-B1E3-02163E01441C.root' ] )
