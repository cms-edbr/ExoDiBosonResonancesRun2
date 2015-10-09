import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/0E4B428D-E569-E511-B128-02163E014310.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/22957172-E669-E511-9180-02163E0143A6.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/62EA1490-E569-E511-A96B-02163E0138C8.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/66E454D9-E569-E511-B530-02163E014216.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/706BD199-E569-E511-9B3A-02163E0141E4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/7CAF609C-E569-E511-A21D-02163E011FB1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/968/00000/8607C7C4-E569-E511-A813-02163E014300.root' ] )
