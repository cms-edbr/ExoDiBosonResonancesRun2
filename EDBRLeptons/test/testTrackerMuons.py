import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.load("ExoDiBosonResonances.EDBRLeptons.trackerMuons")

process.load("ExoDiBosonResonances.EDBRCommon.simulation.DYJetsToLL_HT-600toInf")
process.source.fileNames = ["/store/relval/CMSSW_7_4_0/RelValZpMM_2250_13TeV_Tauola/MINIAODSIM/MCRUN2_74_V7-v1/00000/3EC6C30E-1CDB-E411-A1EE-0025905B859E.root",]                                      
process.maxEvents.input = 200

process.p = cms.Path(process.trackerMuons)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.MessageLogger.cerr.FwkReport.limit = 99999999

