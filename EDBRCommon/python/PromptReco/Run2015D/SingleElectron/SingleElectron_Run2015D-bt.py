import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/D47D70BA-4367-E511-9AFC-02163E01437B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/EE37D8BA-4367-E511-8E9F-02163E0140FE.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/EE9B16C8-4367-E511-A7A4-02163E0138E6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/F2EA8FE2-4367-E511-BDC6-02163E01464C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/614/00000/A0236371-5567-E511-A083-02163E012390.root' ] )
