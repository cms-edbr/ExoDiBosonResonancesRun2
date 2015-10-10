import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/531/00000/609D0C74-6166-E511-90C5-02163E0141CC.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/531/00000/8A617C75-6166-E511-BA00-02163E0134E3.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/599/00000/9CFF4A16-6566-E511-AA03-02163E012036.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/599/00000/AECE6E6B-6566-E511-9FB7-02163E01459A.root' ] )
