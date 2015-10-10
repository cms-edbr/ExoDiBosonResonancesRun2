import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/F2EA8FE2-4367-E511-BDC6-02163E01464C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/614/00000/A0236371-5567-E511-A083-02163E012390.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/028B2F37-F967-E511-8A48-02163E012390.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/065B6686-F967-E511-B521-02163E01438B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/645/00000/1002332F-0568-E511-A1A7-02163E014676.root' ] )
