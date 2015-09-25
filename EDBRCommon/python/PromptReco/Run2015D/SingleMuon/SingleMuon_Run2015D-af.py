import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/734/00000/C08D5C42-4960-E511-BD77-02163E0145C4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/734/00000/E4FB9549-4960-E511-A4A1-02163E014741.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/801/00000/48894C8A-2960-E511-8D45-02163E01348F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/801/00000/AAF9C683-2960-E511-BF68-02163E014297.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/801/00000/CC461D87-2960-E511-820F-02163E0141EA.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/842/00000/E2BD56BB-4760-E511-B0C8-02163E014750.root' ] );
