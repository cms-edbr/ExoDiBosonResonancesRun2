import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/941/00000/08067E38-3862-E511-A5BC-02163E01339B.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/941/00000/22385038-3862-E511-BA66-02163E01369C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/941/00000/2A808C3D-3862-E511-9B1F-02163E01238D.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/941/00000/361C533D-3862-E511-96E2-02163E011EFF.root' ] )
