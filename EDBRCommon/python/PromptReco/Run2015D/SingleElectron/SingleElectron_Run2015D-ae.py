import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/9AD6F795-6E60-E511-85AC-02163E0145DA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/A8F3FE65-6C60-E511-BA88-02163E012096.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/AC342153-7260-E511-A9DB-02163E014318.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/ACCC7D59-7260-E511-8679-02163E0124F4.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/B241EB76-6C60-E511-8462-02163E0139BC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/B2D7FCD9-7060-E511-9BC0-02163E012096.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/B86834A9-6E60-E511-97B4-02163E01370D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/BC55EC67-6660-E511-BBF1-02163E01463F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/CAA1046D-6C60-E511-AC5D-02163E0137CA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/EEA58A8C-6C60-E511-AC7F-02163E0145F6.root' ] );
