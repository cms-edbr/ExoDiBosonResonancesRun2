import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/BAD717AF-5867-E511-B4BD-02163E013399.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/C4D4B799-5867-E511-99F3-02163E0126E5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/CABC6F94-5867-E511-BE5B-02163E011A78.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/E6CB5C9F-5867-E511-A5BA-02163E0133E1.root' ] )
