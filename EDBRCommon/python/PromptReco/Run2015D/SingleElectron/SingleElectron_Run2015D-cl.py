import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/84D0EA25-CC69-E511-8596-02163E0142F3.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/A687AF05-CC69-E511-89CE-02163E0141A2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/E0989105-CC69-E511-8C3F-02163E012523.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/109FCED0-F669-E511-8E0F-02163E01428B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/121E929B-F669-E511-BEED-02163E011890.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/1A26B1D0-F669-E511-B49E-02163E01428B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/1CFCDA9C-F669-E511-B003-02163E0142D5.root' ] )
