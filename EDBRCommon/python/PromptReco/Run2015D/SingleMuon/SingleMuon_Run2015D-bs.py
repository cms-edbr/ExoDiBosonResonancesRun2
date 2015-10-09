import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/C2024E29-CE68-E511-8B12-02163E0121ED.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/DAF2F31B-CE68-E511-A0C4-02163E0140D4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/FC69CB23-CE68-E511-B328-02163E011DD4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/804/00000/9CE4DCC2-6268-E511-BBBE-02163E013534.root' ] )
