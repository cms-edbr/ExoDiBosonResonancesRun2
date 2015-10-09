import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/906B96EC-C46B-E511-9DDC-02163E011963.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/96DB6E39-C56B-E511-9245-02163E013670.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/9A349B05-C56B-E511-AFFA-02163E01459B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/9AC3E611-C56B-E511-91DE-02163E0135AC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/A2CB90F8-C46B-E511-8702-02163E0134C2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/A6F32A05-C56B-E511-8FC3-02163E01459B.root' ] )
