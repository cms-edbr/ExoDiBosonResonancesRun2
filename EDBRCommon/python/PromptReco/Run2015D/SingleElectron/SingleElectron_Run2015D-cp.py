import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/136/00000/AC0A382E-BE6A-E511-BA6C-02163E01457B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/136/00000/ECF06A3E-BE6A-E511-B62F-02163E01477D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/157/00000/14B1B25B-076B-E511-81F9-02163E0118AC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/157/00000/520A3457-076B-E511-AAC9-02163E0146DC.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/157/00000/FC1A6750-076B-E511-ADB8-02163E013999.root' ] )
