import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/0E78CA4B-CC69-E511-9CEC-02163E014282.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/24F8960C-CC69-E511-A513-02163E01371C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/26A63405-CC69-E511-AC00-02163E0127CE.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/2808130E-CC69-E511-9B19-02163E012523.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/8257AE2D-CC69-E511-ABB5-02163E011A55.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/968/00000/8294D71C-CC69-E511-8430-02163E011E5C.root' ] )
