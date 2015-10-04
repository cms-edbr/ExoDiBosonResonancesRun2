import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/734/00000/5212737C-0060-E511-8750-02163E0145ED.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/734/00000/86A9F056-0060-E511-9F37-02163E013487.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/734/00000/A4DEB277-0160-E511-A1EA-02163E01419D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/734/00000/BC8F6458-0060-E511-A1DF-02163E01364B.root' ] )
