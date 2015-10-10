import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/2E971528-8A68-E511-9BB5-02163E011983.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/4EA0A63B-8A68-E511-B151-02163E0127DE.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/6CC8323C-8A68-E511-8A78-02163E0118A6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/6CD99171-8A68-E511-987B-02163E014765.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/751/00000/7656701B-8A68-E511-B404-02163E01416A.root' ] )
