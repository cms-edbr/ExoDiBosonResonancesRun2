import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/4409152D-F967-E511-846A-02163E0135EB.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/5265BF40-F967-E511-A158-02163E01417E.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/541C8D23-F967-E511-9CC2-02163E0138B9.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/5843AE1D-F967-E511-AD52-02163E011FE0.root' ] )
