import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/969/00000/EA4596FC-186A-E511-820A-02163E011985.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/129/00000/345DE96A-C86A-E511-BB1D-02163E0143C5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/129/00000/809D6364-C86A-E511-9E26-02163E0144E7.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/129/00000/9A384965-C86A-E511-9152-02163E0141E4.root' ] )
