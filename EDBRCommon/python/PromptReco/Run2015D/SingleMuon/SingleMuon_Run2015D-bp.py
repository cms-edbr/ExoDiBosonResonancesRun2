import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/723/00000/0208B4E8-1368-E511-B326-02163E011B35.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/723/00000/98D0BF2D-1468-E511-8896-02163E014352.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/723/00000/D04D65E7-1368-E511-A898-02163E0138F0.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/735/00000/D496F6C8-3068-E511-B166-02163E014506.root' ] )
