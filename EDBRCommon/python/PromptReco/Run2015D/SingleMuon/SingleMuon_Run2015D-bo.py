import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/6660058A-0568-E511-8CFF-02163E0142B6.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/A6D7AC67-0568-E511-A830-02163E0143B1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/B0F55573-0568-E511-8897-02163E0138DE.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/722/00000/BCA78950-EB67-E511-810F-02163E0133D8.root' ] )
