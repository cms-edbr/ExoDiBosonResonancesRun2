import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/A8ABFFF1-186A-E511-B5E6-02163E0142F7.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/B6500FF3-186A-E511-BC25-02163E01438E.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/B6E7B104-196A-E511-9A43-02163E012542.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/BE24060C-196A-E511-8518-02163E013416.root' ] )
