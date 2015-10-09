import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/4C7EE302-C56B-E511-B17E-02163E014308.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/50061E0A-C56B-E511-A48F-02163E0144F2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/52365500-C56B-E511-B15A-02163E014773.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/52A96C27-D26B-E511-AB81-02163E0145F5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/626231A5-C66B-E511-AFD1-02163E01451A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/6440AC23-C56B-E511-BC34-02163E011A30.root' ] )
