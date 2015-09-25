import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/630/00000/BCD78EF7-2B5F-E511-A3A3-02163E0170B5.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/673/00000/BC23BFB5-145F-E511-B03F-02163E011A4C.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/674/00000/F459D73B-F95E-E511-B5E7-02163E01446D.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/675/00000/086B30F2-9B5F-E511-A3FC-02163E01429F.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/675/00000/5E85670E-9C5F-E511-AD41-02163E011E80.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/675/00000/D084BBEE-9B5F-E511-B416-02163E012042.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/32084875-3A5F-E511-B670-02163E01232B.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/8ADA6E74-3A5F-E511-BE8C-02163E013627.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/CEAE1A74-3A5F-E511-821F-02163E013938.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/D278497C-3A5F-E511-AC54-02163E0125A9.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/677/00000/E8CA6697-3A5F-E511-AE24-02163E011BD1.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/0AB3E73A-5B60-E511-A8AF-02163E0146CB.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/163B2B19-5A60-E511-9012-02163E0137DF.root' ] );
