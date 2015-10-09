import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/583BE27B-0568-E511-9408-02163E011FF7.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/603078B6-0568-E511-B91C-02163E0143C3.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/64A11C75-0568-E511-A8F5-02163E013848.root' ] )
