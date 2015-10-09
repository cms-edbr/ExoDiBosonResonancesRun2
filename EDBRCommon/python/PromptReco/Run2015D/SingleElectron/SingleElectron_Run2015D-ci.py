import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/D08B9BE4-0069-E511-8B9C-02163E013956.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/E85215F5-0069-E511-B6FD-02163E011A35.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/E886B9E5-0069-E511-993F-02163E01423C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/EA25DFE7-0069-E511-B660-02163E0137FF.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/10437787-0869-E511-A6DB-02163E014120.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/819/00000/443BF7D1-0769-E511-9A34-02163E013829.root' ] )
