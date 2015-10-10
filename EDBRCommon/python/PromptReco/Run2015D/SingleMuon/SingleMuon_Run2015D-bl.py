import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/B0F55573-0568-E511-8897-02163E0138DE.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/722/00000/BCA78950-EB67-E511-810F-02163E0133D8.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/723/00000/0208B4E8-1368-E511-B326-02163E011B35.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/723/00000/98D0BF2D-1468-E511-8896-02163E014352.root' ] )
