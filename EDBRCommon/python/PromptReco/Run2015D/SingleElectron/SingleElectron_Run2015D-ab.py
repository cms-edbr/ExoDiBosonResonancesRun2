import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/70E49EC8-345F-E511-B885-02163E01350A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/74E4B9BD-345F-E511-BE50-02163E01246B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/B65B04BA-345F-E511-9DB2-02163E01346A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/CAE5CFD7-345F-E511-87C0-02163E01363C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/CECD47C4-345F-E511-BA52-02163E014638.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/E41946C8-345F-E511-B2C0-02163E014335.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/00179335-7460-E511-8EE6-02163E0139BC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/06DA6564-7760-E511-9E26-02163E014421.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/082E7474-6C60-E511-A4E3-02163E013566.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/08663685-7560-E511-9A92-02163E01463F.root' ] );
