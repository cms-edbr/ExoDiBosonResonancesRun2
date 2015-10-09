import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/C82D72B1-3169-E511-AE40-02163E014241.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/D2593DB0-3169-E511-8C3E-02163E01428F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/D4463BB4-3169-E511-B991-02163E011C4A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/E832EAA5-3169-E511-8732-02163E012821.root' ] )
