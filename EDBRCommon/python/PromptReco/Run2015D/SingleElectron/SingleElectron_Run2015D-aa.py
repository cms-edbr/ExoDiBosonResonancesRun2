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
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/677/00000/705E47C4-345F-E511-BD2B-02163E014638.root' ] );
