import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/D2373C3A-F967-E511-BB06-02163E012A72.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/ECA30B3A-F967-E511-8D3D-02163E0135CD.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/EE9DFD4B-F967-E511-8EB2-02163E01442C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/FEA02D31-F967-E511-8205-02163E011BEF.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/682/00000/063A29EC-6E68-E511-A885-02163E0125D3.root' ] )
