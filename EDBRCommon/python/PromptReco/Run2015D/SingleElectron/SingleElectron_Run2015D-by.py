import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/40E9883A-B468-E511-9555-02163E0143FD.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/70233065-B468-E511-A181-02163E01432A.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/86033F42-B468-E511-AE42-02163E01411F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/9C22122A-B568-E511-B07C-02163E014144.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/A84AD53D-B468-E511-9484-02163E01353F.root' ] )
