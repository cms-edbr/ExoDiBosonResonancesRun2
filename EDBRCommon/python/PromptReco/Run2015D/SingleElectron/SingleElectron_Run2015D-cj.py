import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/FC860E17-F769-E511-AF43-02163E012289.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/129/00000/4ABFCF42-BF6A-E511-9A2C-02163E011F00.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/129/00000/4C1C6E45-BF6A-E511-AB19-02163E01449D.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/129/00000/781B363E-BF6A-E511-BFDB-02163E013797.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/129/00000/D0BED458-BF6A-E511-A0FD-02163E01441F.root' ] )
