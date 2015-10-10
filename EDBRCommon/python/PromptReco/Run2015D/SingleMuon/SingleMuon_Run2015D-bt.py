import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/283D53D3-C468-E511-9CA9-02163E014754.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/7633ADD5-C468-E511-A908-02163E013493.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/AE9CC3D2-C468-E511-8515-02163E0136B9.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/0E4B428D-E569-E511-B128-02163E014310.root' ] )
