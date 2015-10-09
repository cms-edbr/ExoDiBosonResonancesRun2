import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/2A471BB9-4367-E511-B1B6-02163E0133C6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/345819B9-4367-E511-A30B-02163E01364A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/36D38BBF-4367-E511-A47D-02163E014552.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/3CB89EBC-4367-E511-907A-02163E01193F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/4259FBBD-4367-E511-A4AD-02163E011F0B.root' ] )
