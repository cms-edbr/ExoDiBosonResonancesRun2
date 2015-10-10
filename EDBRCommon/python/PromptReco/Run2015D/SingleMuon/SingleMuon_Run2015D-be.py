import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/613/00000/FED78E9E-5867-E511-AD04-02163E014145.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/614/00000/023C2B75-5567-E511-B688-02163E011CF0.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/02179A27-F967-E511-9F31-02163E01372F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/257/645/00000/04E3C316-F967-E511-AC4B-02163E0145C9.root' ] )
