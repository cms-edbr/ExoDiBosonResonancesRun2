import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/161/00000/54D118C2-9C26-E511-A013-02163E01374D.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/162/00000/1E96352E-4327-E511-A85D-02163E01474A.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/163/00000/62776591-9F26-E511-931A-02163E0144D2.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/164/00000/DC7D98A3-A226-E511-A9E1-02163E014729.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/167/00000/90B78DBB-A726-E511-AD91-02163E012BD2.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/168/00000/281C137F-D526-E511-90AE-02163E0119CD.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/244/00000/5E425D83-6B27-E511-98E0-02163E01345F.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/251/00000/0EA22A54-9027-E511-A3D4-02163E0133E3.root',
       '/store/data/Run2015B/MET/MINIAOD/PromptReco-v1/000/251/252/00000/E44E4C4F-9127-E511-8DD4-02163E013901.root' ] );


secFiles.extend( [
               ] )
