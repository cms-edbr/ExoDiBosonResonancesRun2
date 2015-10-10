import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/5C58739F-F669-E511-9139-02163E013530.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/7A5922D6-F669-E511-9D60-02163E01428B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/80760EA4-F669-E511-A9A7-02163E01358D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/8AEFD3AB-F669-E511-9C11-02163E013412.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/A4C80018-F769-E511-9EEE-02163E012289.root' ] )
