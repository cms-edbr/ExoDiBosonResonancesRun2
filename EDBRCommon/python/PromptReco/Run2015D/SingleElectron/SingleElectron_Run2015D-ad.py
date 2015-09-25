import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/60AF0A39-7460-E511-89A3-02163E0144EA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/60F5DB35-7460-E511-AC79-02163E011D99.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/728240EF-7060-E511-8685-02163E0133E9.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/72A4046D-6C60-E511-81A4-02163E0137CA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/760FB377-6C60-E511-B1D2-02163E014718.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/7E3C579C-6E60-E511-8D94-02163E014229.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/8AEF5285-7560-E511-B15E-02163E011E10.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/900D3A3F-7460-E511-8214-02163E014230.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/90D9F435-7460-E511-B389-02163E011E08.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/256/729/00000/96E81D79-7560-E511-A30A-02163E0143CD.root' ] );
