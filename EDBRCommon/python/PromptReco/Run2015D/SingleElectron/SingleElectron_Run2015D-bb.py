import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/394/00000/5EBDE45C-4364-E511-87FD-02163E0146A6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/395/00000/22B7FD01-1D64-E511-BAAD-02163E014585.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/461/00000/2E26CDFB-7265-E511-9D1A-02163E01433E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/461/00000/76EC8AF8-7265-E511-A031-02163E01204B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/531/00000/024E80E0-1F66-E511-9B68-02163E0142FE.root' ] )
