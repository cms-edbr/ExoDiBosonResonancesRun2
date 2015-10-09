import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/04F73DD5-C468-E511-8D84-02163E01430A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/16FB82D4-C468-E511-8A65-02163E0146C1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/283D53D3-C468-E511-9CA9-02163E014754.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/7633ADD5-C468-E511-A908-02163E013493.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/AE9CC3D2-C468-E511-8515-02163E0136B9.root' ] )
