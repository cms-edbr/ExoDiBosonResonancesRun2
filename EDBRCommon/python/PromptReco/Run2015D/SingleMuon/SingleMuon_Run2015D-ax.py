import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/26BE3A44-A961-E511-9403-02163E014249.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/5C042B37-A961-E511-A91F-02163E0144C4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/6C6A8F48-A961-E511-9F87-02163E011A31.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/868/00000/7EE3B839-A961-E511-A89B-02163E013559.root' ] )
