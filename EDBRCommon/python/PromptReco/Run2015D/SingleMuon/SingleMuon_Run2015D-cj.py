import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/EA6A7938-196C-E511-9EBC-02163E01282E.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/EE3FEF34-196C-E511-B8AA-02163E013427.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/EEA4F942-196C-E511-B803-02163E0127AD.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/FC245B35-196C-E511-A5AC-02163E0144F3.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/FE67C9A4-196C-E511-AB93-02163E0141C1.root' ] )
