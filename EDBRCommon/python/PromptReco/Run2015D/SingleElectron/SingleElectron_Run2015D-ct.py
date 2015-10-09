import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/64B8250A-C56B-E511-8DA1-02163E0144F2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/663841F9-C46B-E511-9CF7-02163E0128DC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/7C5DA2A6-C66B-E511-A264-02163E01451A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/80909339-C56B-E511-81B9-02163E013670.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/82C1421B-C56B-E511-B2FC-02163E013557.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/88FCAA35-C56B-E511-B694-02163E0141B6.root' ] )
