import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/1AB75833-F967-E511-9803-02163E0144F7.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/241F502E-F967-E511-BEAF-02163E0120C3.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/301F1A21-F967-E511-861A-02163E0138D1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/3A615035-F967-E511-9C09-02163E01473E.root' ] )
