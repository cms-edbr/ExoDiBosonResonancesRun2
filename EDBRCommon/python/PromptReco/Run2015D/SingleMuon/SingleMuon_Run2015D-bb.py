import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/9AF1388A-5867-E511-B528-02163E01353F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/9C155A9D-5867-E511-8E63-02163E01257C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/A04C4298-5867-E511-8F31-02163E011F70.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/A64E2594-5867-E511-9989-02163E013677.root' ] )
