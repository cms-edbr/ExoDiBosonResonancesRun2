import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/229DE51E-CE68-E511-B33B-02163E011DD4.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/32D50B1A-CE68-E511-8257-02163E011B1F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/42D48419-CE68-E511-9D6E-02163E011DEB.root' ] )
