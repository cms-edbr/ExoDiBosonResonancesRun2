import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/5A2B721A-F967-E511-B7B6-02163E0133DD.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/749C8625-F967-E511-A5F1-02163E014200.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/766C6722-F967-E511-8C03-02163E0125BE.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/78B00A2F-F967-E511-9FAC-02163E0142F9.root' ] )
