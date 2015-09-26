import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/14722E35-7460-E511-9802-02163E012096.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/2463D28B-6E60-E511-B7FA-02163E01427D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/2A9EFFF6-A360-E511-83F1-02163E013759.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/32AC4D36-7460-E511-993D-02163E0137F5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/403A25AA-6E60-E511-9687-02163E0124F4.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/4415FD67-7760-E511-B802-02163E011E08.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/54D573D9-7860-E511-B4C1-02163E011C91.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/5AA35F52-7260-E511-B56F-02163E01469A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/5C287754-7260-E511-8327-02163E014640.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/5E29296D-7260-E511-8EC7-02163E0145F6.root' ] );
