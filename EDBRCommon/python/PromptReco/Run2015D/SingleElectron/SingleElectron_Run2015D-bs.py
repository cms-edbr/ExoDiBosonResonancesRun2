import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/203016EA-6E68-E511-8666-02163E0136B1.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/28E16D65-9268-E511-8622-02163E0146DA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/3E00ABE9-6E68-E511-BC06-02163E01431C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/6683654C-3769-E511-A8E6-02163E011C18.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/76C725E3-6E68-E511-BBE8-02163E011B92.root' ] )
