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
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/252/00000/6258DF96-A227-E511-BE8A-02163E01259F.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/491/00000/4A5A5D00-C628-E511-ACC7-02163E01414A.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/493/00000/0C69AF3D-CF28-E511-B56A-02163E01414A.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/497/00000/607EA0EA-E028-E511-BD54-02163E0133FF.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/498/00000/8064CCF6-ED28-E511-87D2-02163E014437.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/499/00000/70310B47-F728-E511-B2EF-02163E0118A2.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/500/00000/0273C876-0E29-E511-8B38-02163E012712.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/521/00000/D28AB765-6629-E511-8AAD-02163E0133D1.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/522/00000/805EB9CD-6129-E511-BF1C-02163E0129A3.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/548/00000/B6D08898-232A-E511-A833-02163E011DDE.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/560/00000/BA599BB8-E129-E511-B26A-02163E0134CC.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/561/00000/5ACDA1DE-FB29-E511-8D8C-02163E0133B5.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/561/00000/CA80E14E-1E2A-E511-8C7D-02163E0122C2.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/30DDF910-5E2A-E511-9F4D-02163E01206A.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/3CE07240-742A-E511-BA88-02163E01258B.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/5CF006D1-602A-E511-95CE-02163E0126E1.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/8EE9BBAA-7E2A-E511-AEF7-02163E0143C0.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/B41B8802-672A-E511-A9EA-02163E012787.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/DCC900B5-972A-E511-9785-02163E012283.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/F0A7C9F3-6B2A-E511-A73B-02163E0126A0.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/562/00000/FE5AD795-6E2A-E511-9C40-02163E012787.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/604/00000/AE22AF42-902A-E511-8A22-02163E012B30.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/612/00000/50DA7894-932A-E511-801E-02163E0136A2.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/628/00000/40EF63A0-B52A-E511-8B57-02163E0133F0.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/638/00000/0CDDB666-E72A-E511-9BFD-02163E011DE5.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/638/00000/B2FC1038-372B-E511-AA94-02163E013481.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/642/00000/2C622272-D02A-E511-9F20-02163E013645.root',
       '/store/data/Run2015B/SingleElectron/MINIAOD/PromptReco-v1/000/251/721/00000/CADC920F-E02B-E511-BB9B-02163E01412F.root' ] );

secFiles.extend( [
               ] )

