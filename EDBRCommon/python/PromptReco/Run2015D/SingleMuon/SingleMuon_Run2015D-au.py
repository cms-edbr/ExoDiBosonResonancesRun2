import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/D2BE563A-A961-E511-BDDD-02163E0137DF.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/F2441639-A961-E511-957D-02163E0133F8.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/869/00000/72B30BE7-1261-E511-A4A5-02163E011D35.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/926/00000/CAB6D309-8661-E511-AED1-02163E0146EB.root' ] )
