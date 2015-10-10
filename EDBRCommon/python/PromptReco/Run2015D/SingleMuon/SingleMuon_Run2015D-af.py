import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/676/00000/FCCE68ED-EC5F-E511-8F08-02163E01465A.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/32084875-3A5F-E511-B670-02163E01232B.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/8ADA6E74-3A5F-E511-BE8C-02163E013627.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/CEAE1A74-3A5F-E511-821F-02163E013938.root' ] )
