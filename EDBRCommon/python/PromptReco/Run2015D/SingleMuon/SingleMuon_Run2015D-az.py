import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/5A220C8A-5867-E511-82E9-02163E011E5E.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/5E1E5096-5867-E511-BC5A-02163E01371E.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/6C552586-5867-E511-8398-02163E0145D5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/6E842D93-5867-E511-88B9-02163E0134B8.root' ] )
