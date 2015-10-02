import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/AE1F4A70-7561-E511-801F-02163E011AC2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/B8755465-7561-E511-B65A-02163E0142FF.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/C07DDC7C-7561-E511-8F20-02163E012B2E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/C2E2CA81-7561-E511-B45C-02163E011C7D.root' ] )
