import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/DE6F8D70-7561-E511-81D8-02163E014660.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/E4320085-7561-E511-ACC0-02163E0133F8.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/E820C271-7561-E511-B998-02163E011838.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/843/00000/FC913097-7561-E511-8B85-02163E0138D9.root' ] )
