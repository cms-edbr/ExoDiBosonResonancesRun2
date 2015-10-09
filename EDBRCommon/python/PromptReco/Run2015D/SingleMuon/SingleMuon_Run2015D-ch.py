import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/B0D8753A-196C-E511-B437-02163E0142D1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/B637BDCE-196C-E511-82BE-02163E0141BE.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/B8299139-196C-E511-9DC2-02163E013870.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/B8661131-196C-E511-992E-02163E0140FE.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/C8230147-196C-E511-A70C-02163E0146A9.root' ] )
