import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/86033F42-B468-E511-AE42-02163E01411F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/9C22122A-B568-E511-B07C-02163E014144.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/A84AD53D-B468-E511-9484-02163E01353F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/A860E544-B468-E511-9464-02163E014346.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/805/00000/C6A49D3E-B468-E511-BD2D-02163E01203C.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/00003BE2-0069-E511-B3D6-02163E011DB5.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/816/00000/16ACB9E7-0069-E511-9A30-02163E0135EC.root' ] )
