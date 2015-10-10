import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/B4AD6B53-ED5F-E511-A05B-02163E0143BA.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/B6BFF15E-ED5F-E511-A6E3-02163E0133E4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/C2D5A4CC-F55F-E511-A02A-02163E0123FC.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/E0DD2F18-EF5F-E511-B423-02163E0146E4.root' ] )
