import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/FC913097-7561-E511-8B85-02163E0138D9.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/866/00000/84B4359E-F660-E511-B47B-02163E011D9F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/867/00000/4C0A288E-1961-E511-8B3D-02163E0141AB.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/867/00000/5425B5A1-1961-E511-924D-02163E013582.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/867/00000/ECAE9A90-1961-E511-AC82-02163E011A29.root' ] )
