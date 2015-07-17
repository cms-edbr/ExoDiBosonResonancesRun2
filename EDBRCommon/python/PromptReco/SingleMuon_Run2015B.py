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
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/252/00000/7E4A8F57-A127-E511-9BF5-02163E014629.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/493/00000/6A4D2AB2-E828-E511-B82B-02163E0121E9.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/497/00000/668C5130-FE28-E511-8F78-02163E0133B0.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/498/00000/50CD6709-0C29-E511-8F8B-02163E0134FD.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/499/00000/402D1C6D-1729-E511-ABF5-02163E011DFF.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/500/00000/62310AED-3729-E511-AC61-02163E012712.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/500/00000/A2A303EC-3729-E511-9ECE-02163E011A29.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/521/00000/425B1189-6729-E511-AF38-02163E013728.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/522/00000/F6930521-5D29-E511-B517-02163E011D37.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/548/00000/44CE0650-EF29-E511-BA0D-02163E012601.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/560/00000/A886DB09-E029-E511-8A06-02163E0125C8.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/561/00000/F6A7CE0F-132A-E511-A423-02163E011D88.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/7CC342FD-A02A-E511-BE8D-02163E01182A.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/96297F29-862A-E511-85C1-02163E013901.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/C6637305-A12A-E511-AD71-02163E0138F6.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/E0561625-7C2A-E511-9016-02163E0133D1.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/EA8BA8F7-A02A-E511-A45F-02163E013473.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/604/00000/1606A3BF-972A-E511-86A7-02163E013515.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/612/00000/7A0CE8FF-A72A-E511-B7DC-02163E011D1C.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/638/00000/10C07DF0-FA2A-E511-846A-02163E01474A.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/642/00000/D20F8A8A-DE2A-E511-9D16-02163E0133FF.root' ] );


secFiles.extend( [
               ] )

