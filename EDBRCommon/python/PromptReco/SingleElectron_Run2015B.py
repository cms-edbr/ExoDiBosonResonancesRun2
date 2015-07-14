import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/096/00000/22D22D7F-5626-E511-BDE3-02163E011FAB.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/161/00000/7019DC27-9C26-E511-84FF-02163E011CC2.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/162/00000/9CC606D8-4127-E511-8F35-02163E013830.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/163/00000/9C435096-9F26-E511-A1D7-02163E012AB6.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/164/00000/4633CC68-A326-E511-95D0-02163E0124EA.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/167/00000/E661FBF2-A726-E511-8B8B-02163E01207C.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/168/00000/FCB6CB61-BC26-E511-8858-02163E01375B.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/244/00000/084C9A66-9227-E511-91E0-02163E0133F0.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/244/00000/12EE24E2-8F27-E511-80D1-02163E013793.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/251/00000/3A0E6309-8827-E511-B96D-02163E013432.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/252/00000/36D5A4A8-A227-E511-9AAA-02163E0135F3.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/252/00000/6258DF96-A227-E511-BE8A-02163E01259F.root' ] );


secFiles.extend( [
               ] )
