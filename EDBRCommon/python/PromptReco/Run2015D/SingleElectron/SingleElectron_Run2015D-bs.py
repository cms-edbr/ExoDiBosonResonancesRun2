import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/C252E1B8-4367-E511-AD75-02163E01475E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/D01616BC-4367-E511-899D-02163E01342B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/D07339B9-4367-E511-BA1F-02163E01462F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/D20631F0-4367-E511-A7C1-02163E0140E5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/D2E822B8-4367-E511-8C3E-02163E013756.root' ] )
