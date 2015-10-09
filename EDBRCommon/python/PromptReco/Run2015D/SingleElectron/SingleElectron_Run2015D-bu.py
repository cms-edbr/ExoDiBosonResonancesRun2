import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/028B2F37-F967-E511-8A48-02163E012390.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/065B6686-F967-E511-B521-02163E01438B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/1002332F-0568-E511-A1A7-02163E014676.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/10CE3C3D-F967-E511-86C0-02163E013832.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/18FE7E31-F967-E511-8AB5-02163E0123E1.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/1E900B3A-F967-E511-97C9-02163E0135CD.root' ] )
