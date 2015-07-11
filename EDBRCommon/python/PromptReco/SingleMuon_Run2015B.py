import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/162/00000/160C08A3-4227-E511-B829-02163E01259F.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/164/00000/544E58CD-A226-E511-834E-02163E0134D6.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/167/00000/EE9594B8-A826-E511-A18B-02163E011A7D.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/168/00000/4E8E390B-EA26-E511-9EDA-02163E013567.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/168/00000/60FF8405-EA26-E511-A892-02163E01387D.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/244/00000/68275270-7C27-E511-B1F0-02163E011A46.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/244/00000/B6304C6F-7C27-E511-9C77-02163E01250E.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/251/00000/EEBF2AF4-8D27-E511-91F7-02163E014527.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/252/00000/0438FA5A-A127-E511-BA6F-02163E013414.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/252/00000/7E4A8F57-A127-E511-9BF5-02163E014629.root' ] );


secFiles.extend( [
               ] )
