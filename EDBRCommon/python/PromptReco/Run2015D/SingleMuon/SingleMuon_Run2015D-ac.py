import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/1A94C275-F05F-E511-883F-02163E014100.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/1E0FBF1E-EF5F-E511-8676-02163E0141BA.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/281931F2-EA5F-E511-B684-02163E013863.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/30CD8613-EF5F-E511-93D1-02163E0141A8.root' ] )
