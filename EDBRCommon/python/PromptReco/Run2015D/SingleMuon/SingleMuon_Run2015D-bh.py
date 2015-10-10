import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/541C8D23-F967-E511-9CC2-02163E0138B9.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/5843AE1D-F967-E511-AD52-02163E011FE0.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/5A2B721A-F967-E511-B7B6-02163E0133DD.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/749C8625-F967-E511-A5F1-02163E014200.root' ] )
