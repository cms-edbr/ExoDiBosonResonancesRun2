import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/2808130E-CC69-E511-9B19-02163E012523.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/8257AE2D-CC69-E511-ABB5-02163E011A55.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/8294D71C-CC69-E511-8430-02163E011E5C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/84D0EA25-CC69-E511-8596-02163E0142F3.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/A687AF05-CC69-E511-89CE-02163E0141A2.root' ] )
