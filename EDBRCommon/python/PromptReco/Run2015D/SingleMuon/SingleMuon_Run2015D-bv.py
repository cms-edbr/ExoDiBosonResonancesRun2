import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/7CAF609C-E569-E511-A21D-02163E011FB1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/8607C7C4-E569-E511-A813-02163E014300.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/0476510B-196A-E511-A468-02163E0143DA.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/0E6B87F4-186A-E511-8445-02163E011EDF.root' ] )
