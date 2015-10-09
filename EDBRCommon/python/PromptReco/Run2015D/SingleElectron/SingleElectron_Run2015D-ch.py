import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/186283ED-0069-E511-AF60-02163E011E4C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/18CC41E8-0069-E511-9A6C-02163E0134F8.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/3E443D66-0269-E511-962A-02163E0146B5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/4432F6EC-0069-E511-ABC7-02163E0119FA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/62CE60F0-0069-E511-AD2B-02163E01437A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/B8D49AF0-0069-E511-9E90-02163E01288C.root' ] )
