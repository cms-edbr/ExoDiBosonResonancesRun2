import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/5CA69132-F967-E511-BF67-02163E014485.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/6693A85A-FA67-E511-B66C-02163E01459D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/66A2EECE-F967-E511-98B1-02163E011C4A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/6AD1AB5B-FA67-E511-87A9-02163E01459D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/74422752-F967-E511-8224-02163E01437F.root' ] )
