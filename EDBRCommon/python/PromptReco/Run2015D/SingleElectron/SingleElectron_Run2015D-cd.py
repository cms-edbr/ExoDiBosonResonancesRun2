import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/CE2FC2E2-0769-E511-B2D8-02163E014177.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/D8CD5AD9-0769-E511-AFAF-02163E01338B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/0E78CA4B-CC69-E511-9CEC-02163E014282.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/24F8960C-CC69-E511-A513-02163E01371C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/26A63405-CC69-E511-AC00-02163E0127CE.root' ] )
