import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/867/00000/4C0A288E-1961-E511-8B3D-02163E0141AB.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/867/00000/5425B5A1-1961-E511-924D-02163E013582.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/867/00000/ECAE9A90-1961-E511-AC82-02163E011A29.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/0C3D6566-9361-E511-8377-02163E0137F3.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/868/00000/1C2AEC73-9361-E511-8942-02163E014610.root' ] )
