import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/C42D6F51-F967-E511-AEB3-02163E0142D8.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/C620A864-F967-E511-A336-02163E01461D.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/DA73CF21-F967-E511-968F-02163E011A06.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/682/00000/583BE27B-0568-E511-9408-02163E011FF7.root' ] )
