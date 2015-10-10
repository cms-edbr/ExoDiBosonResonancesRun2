import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/D4463BB4-3169-E511-B991-02163E011C4A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/816/00000/E832EAA5-3169-E511-8732-02163E012821.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/04F73DD5-C468-E511-8D84-02163E01430A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/819/00000/16FB82D4-C468-E511-8A65-02163E0146C1.root' ] )
