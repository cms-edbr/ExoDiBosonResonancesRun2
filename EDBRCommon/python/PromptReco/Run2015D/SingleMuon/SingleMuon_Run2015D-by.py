import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/0476510B-196A-E511-A468-02163E0143DA.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/0E6B87F4-186A-E511-8445-02163E011EDF.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/2412ECF0-186A-E511-AE11-02163E014124.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/2EBDED0C-196A-E511-AAE1-02163E011907.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/52E4EE10-196A-E511-81A0-02163E012027.root' ] )
