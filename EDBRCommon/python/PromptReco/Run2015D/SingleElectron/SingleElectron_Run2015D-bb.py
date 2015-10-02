import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/5CEA4970-7561-E511-8B9C-02163E011AC2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/6AE0616D-7561-E511-9C25-02163E012861.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/7A980471-7561-E511-93E1-02163E01443B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/7C6BE01E-7661-E511-9743-02163E0138BA.root' ] )
