import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/9E0B2340-F967-E511-87AC-02163E014287.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/ACD50D22-FA67-E511-865D-02163E0145CC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/BA33F745-F967-E511-931C-02163E011D72.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/C0EE48AE-FB67-E511-A727-02163E014478.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/C8D87F32-F967-E511-8477-02163E01430E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/CC77F55A-F967-E511-8211-02163E011CFE.root' ] )
