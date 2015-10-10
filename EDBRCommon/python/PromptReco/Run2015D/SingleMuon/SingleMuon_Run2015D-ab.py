import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/675/00000/5E85670E-9C5F-E511-AD41-02163E011E80.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/675/00000/D084BBEE-9B5F-E511-B416-02163E012042.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/06DC9FC8-F55F-E511-8214-02163E011D99.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/120A295C-FE5F-E511-9B21-02163E0135B5.root' ] )
