import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/745F039B-5867-E511-8C61-02163E013797.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/78ABEB9E-5867-E511-9D72-02163E014427.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/8896C38A-5867-E511-97BF-02163E0126B5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/96179D90-5867-E511-BC27-02163E013894.root' ] )
