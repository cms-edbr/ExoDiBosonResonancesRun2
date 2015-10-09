import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/722/00000/F4216DF7-E567-E511-A22B-02163E01364A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/0AE02AD0-0768-E511-ABC4-02163E0144EA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/50DB2AB7-0768-E511-8986-02163E014352.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/D0136B96-0768-E511-ACFE-02163E01263D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/D69D0A9E-0768-E511-B9DD-02163E012273.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/735/00000/92C938AE-5968-E511-99A9-02163E013403.root' ] )
