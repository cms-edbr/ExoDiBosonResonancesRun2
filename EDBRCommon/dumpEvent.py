import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("ExoDiBosonResonances.EDBRGenStudies.genMuons_cff")
process.load("ExoDiBosonResonances.EDBRGenStudies.genElectrons_cff")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.Wtomunu = cms.EDProducer("CandViewCombiner",
                                 decay = cms.string("goodMuons genMetTrue"),
                                 checkCharge = cms.bool(False),
                                 cut = cms.string("")
                                 )

process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(10),
  printVertex = cms.untracked.bool(False),
  src = cms.InputTag("prunedGenParticles")
)

#process.p = cms.Path(process.muSequence + process.Wtomunu + process.printTree)
process.leptonicDecay.src = "prunedGenParticles"
process.hadronicDecay.src = "prunedGenParticles"
process.p2 = cms.Path(process.leptonicDecay 
                      + process.hadronicDecay 
                      + process.printTree)
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RSGravToZZ_kMpl01_M-4500")
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.DYJetsToLL_HT-600toInf")
#process.source.fileNames = ["file:pp_ZP_WW_enqq_BM1_13tev.root",]

process.maxEvents.input = 200

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.MessageLogger.cerr.FwkReport.limit = 99999999
