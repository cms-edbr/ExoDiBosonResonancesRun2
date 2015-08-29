import FWCore.ParameterSet.Config as cms

process = cms.Process("MCMatch")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# Input source
import sys
SAMPLE = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RunIIDR74X50ns."+SAMPLE)
process.maxEvents.input = -1

process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")

process.goodVertices = cms.EDFilter(    "VertexSelector",
                                         src = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                         cut = cms.string( "chi2 != 0 "
                                                           "& ndof >= 4.0 "
                                                           "& abs(z) <= 24.0 "
                                                           "& abs(position.Rho) <= 2.0 "),
                                         filter = cms.bool(True) )

process.goodMuons = cms.EDFilter(       "CandViewSelector",
                                         src = cms.InputTag("slimmedMuons"),
                                         cut = cms.string( "pt>20 & abs(eta)<2.4" ),
                                         filter = cms.bool(True) )

process.Ztomumu = cms.EDProducer(       "CandViewCombiner",
                                         decay = cms.string("goodMuons@+ goodMuons@-"),
                                         cut = cms.string("70 < mass < 110") )

process.dilepton = cms.EDFilter(        "CandViewCountFilter",
                                         src = cms.InputTag("Ztomumu"),
                                         minNumber = cms.uint32(1),
                                         filter = cms.bool(True) )

process.ana = cms.EDAnalyzer(            "EDBRGenStudies" )

process.p = cms.Path(                    process.leptonicDecay   + 
                                         process.goodVertices    +
                                         process.goodMuons       +
                                         process.Ztomumu         + 
                                         process.dilepton        +
                                         process.ana             )

process.TFileService = cms.Service(     "TFileService",
                                         fileName = cms.string("tree_"+SAMPLE+".root") )
