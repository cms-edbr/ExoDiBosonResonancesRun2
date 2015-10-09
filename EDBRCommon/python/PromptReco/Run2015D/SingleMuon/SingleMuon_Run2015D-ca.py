import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/C2BC800E-196A-E511-A700-02163E011890.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/D2B6A304-196A-E511-86EF-02163E0123ED.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/E08F12FA-186A-E511-AAF8-02163E013922.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/EA1A9609-196A-E511-A3E4-02163E01438E.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/EA4596FC-186A-E511-820A-02163E011985.root' ] )
