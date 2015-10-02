import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/648D46F3-4160-E511-A634-02163E014734.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/7225F7BD-5760-E511-8235-02163E014421.root' ] )
