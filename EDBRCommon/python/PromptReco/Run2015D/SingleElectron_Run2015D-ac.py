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
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/EEA58A8C-6C60-E511-AC7F-02163E0145F6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/FAAE8954-7260-E511-BD80-02163E0143CD.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/FAF0205D-7260-E511-A471-02163E0144F5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/734/00000/86A9F056-0060-E511-9F37-02163E013487.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/734/00000/A4DEB277-0160-E511-A1EA-02163E01419D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/734/00000/BC8F6458-0060-E511-A1DF-02163E01364B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/801/00000/02D58F8E-5460-E511-ACE4-02163E01470E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/801/00000/10629A2B-5360-E511-9715-02163E014353.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/801/00000/1217EA24-5360-E511-A5D8-02163E014750.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/801/00000/C6BC5316-5360-E511-AFE0-02163E0144EA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/801/00000/E2F1C53E-5360-E511-B07D-02163E0140EC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/842/00000/5C1E8939-4460-E511-BFE6-02163E014534.root' ] );
