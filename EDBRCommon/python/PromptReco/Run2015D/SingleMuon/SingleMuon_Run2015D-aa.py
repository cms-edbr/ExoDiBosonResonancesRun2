import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/630/00000/BCD78EF7-2B5F-E511-A3A3-02163E0170B5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/673/00000/BC23BFB5-145F-E511-B03F-02163E011A4C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/674/00000/F459D73B-F95E-E511-B5E7-02163E01446D.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/675/00000/086B30F2-9B5F-E511-A3FC-02163E01429F.root' ] )
