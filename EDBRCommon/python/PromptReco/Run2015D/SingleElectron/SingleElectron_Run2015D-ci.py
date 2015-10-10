import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/C49C2190-F669-E511-8058-02163E0146DA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/DE879FAD-F669-E511-88E8-02163E013412.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/E4A4601E-F769-E511-9F7D-02163E014428.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/E8D1AE90-F669-E511-AD09-02163E0146DA.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/969/00000/EC4B139F-F669-E511-8646-02163E0118AC.root' ] )
