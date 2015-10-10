import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/1E64DB91-F669-E511-A17E-02163E0146DA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/2614929B-F669-E511-BE30-02163E011890.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/44AFB9C4-F669-E511-A896-02163E01424F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/481E349B-F669-E511-950C-02163E0145E7.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/4C45F1AD-F669-E511-9D32-02163E014225.root' ] )
