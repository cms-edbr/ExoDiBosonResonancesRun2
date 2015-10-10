import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/92407CDE-6E68-E511-A4FA-02163E01247C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/D6066EEC-6E68-E511-9395-02163E0143BE.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/722/00000/F4216DF7-E567-E511-A22B-02163E01364A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/0AE02AD0-0768-E511-ABC4-02163E0144EA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/50DB2AB7-0768-E511-8986-02163E014352.root' ] )
