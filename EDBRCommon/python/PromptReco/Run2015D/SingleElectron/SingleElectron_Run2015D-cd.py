import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/6CD99171-8A68-E511-987B-02163E014765.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/7656701B-8A68-E511-B404-02163E01416A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/7EFD541E-8A68-E511-A742-02163E01436A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/820A2632-8A68-E511-90EC-02163E012B73.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/9688C843-8A68-E511-BECE-02163E0123C3.root' ] )
