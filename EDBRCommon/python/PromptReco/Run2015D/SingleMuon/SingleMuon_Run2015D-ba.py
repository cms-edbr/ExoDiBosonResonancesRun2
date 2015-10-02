import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/394/00000/3CC60488-2A64-E511-AA83-02163E0134E0.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/395/00000/345B40D7-1C64-E511-97E8-02163E01299A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/461/00000/722DBCB6-1465-E511-AA5D-02163E01420C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/531/00000/1C4F6F7B-6166-E511-AEF2-02163E011FB1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/531/00000/609D0C74-6166-E511-90C5-02163E0141CC.root' ] )
