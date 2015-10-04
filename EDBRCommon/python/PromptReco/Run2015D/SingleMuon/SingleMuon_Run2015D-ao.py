import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/734/00000/84C8C331-4960-E511-AFD1-02163E014144.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/734/00000/C08D5C42-4960-E511-BD77-02163E0145C4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/734/00000/E4FB9549-4960-E511-A4A1-02163E014741.root' ] )
