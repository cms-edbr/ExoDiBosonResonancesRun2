import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/D0136B96-0768-E511-ACFE-02163E01263D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/723/00000/D69D0A9E-0768-E511-B9DD-02163E012273.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/735/00000/92C938AE-5968-E511-99A9-02163E013403.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/02211C2D-8A68-E511-90B5-02163E011891.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/0660FC36-8A68-E511-AA6F-02163E01423A.root' ] )
