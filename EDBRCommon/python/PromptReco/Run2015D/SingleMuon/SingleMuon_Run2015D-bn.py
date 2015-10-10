import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/42D48419-CE68-E511-9D6E-02163E011DEB.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/507DE925-CE68-E511-B784-02163E0118BF.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/6ED7CA1C-CE68-E511-9E9C-02163E0136A5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/751/00000/A2FA8E29-CE68-E511-ADD1-02163E011FC7.root' ] )
