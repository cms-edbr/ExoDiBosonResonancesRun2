import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/8ADA6E74-3A5F-E511-BE8C-02163E013627.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/CEAE1A74-3A5F-E511-821F-02163E013938.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/D278497C-3A5F-E511-AC54-02163E0125A9.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/E8CA6697-3A5F-E511-AE24-02163E011BD1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/0AB3E73A-5B60-E511-A8AF-02163E0146CB.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/163B2B19-5A60-E511-9012-02163E0137DF.root' ] );
