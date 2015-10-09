import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/78DCF4D1-0769-E511-8D3D-02163E011CB5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/90959933-0869-E511-A209-02163E0145F2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/940069D2-0769-E511-A120-02163E01418D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/B4B861D9-0769-E511-A7E1-02163E01247C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/CE2FC2E2-0769-E511-B2D8-02163E014177.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/D8CD5AD9-0769-E511-AFAF-02163E01338B.root' ] )
