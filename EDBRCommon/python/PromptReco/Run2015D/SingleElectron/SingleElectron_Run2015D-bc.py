import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/88108D6C-7561-E511-B3E9-02163E014412.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/90927775-7561-E511-97F4-02163E01442F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/92207281-7561-E511-9E49-02163E012B18.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/941E9379-7561-E511-98EE-02163E013393.root' ] )
