import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/E4320085-7561-E511-ACC0-02163E0133F8.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/E820C271-7561-E511-B998-02163E011838.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/FC913097-7561-E511-8B85-02163E0138D9.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/866/00000/84B4359E-F660-E511-B47B-02163E011D9F.root' ] )
