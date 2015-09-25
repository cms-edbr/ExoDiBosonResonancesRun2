import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/630/00000/6E469C2A-165F-E511-9E77-02163E01414D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/673/00000/86A59632-0B5F-E511-8443-02163E014133.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/674/00000/AA2BE3D9-F45E-E511-9D3A-02163E0121D3.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/675/00000/864628EB-9C5F-E511-AF26-02163E014767.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/675/00000/D8CD44FA-9C5F-E511-8B24-02163E0134DD.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/675/00000/DC55BAD0-9C5F-E511-84E6-02163E01474C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/675/00000/E24CD8D3-9C5F-E511-A94A-02163E0140FB.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/04A8EBBF-345F-E511-A729-02163E01435B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/1AA77AC6-345F-E511-8175-02163E0126BC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/705E47C4-345F-E511-BD2B-02163E014638.root',
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
