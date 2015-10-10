import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/531/00000/1ABF51E0-1F66-E511-972E-02163E0124DC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/531/00000/50A6B405-2066-E511-94A6-02163E012754.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/531/00000/68358FE3-1F66-E511-90E4-02163E01446D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/531/00000/EC762CE0-1F66-E511-8517-02163E014334.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/599/00000/044ED018-6366-E511-8159-02163E0133A2.root' ] )
