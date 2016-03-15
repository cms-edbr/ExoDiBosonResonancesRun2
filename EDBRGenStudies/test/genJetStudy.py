import FWCore.ParameterSet.Config as cms

process = cms.Process("MCMatch")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1'

# Input source
import sys
SAMPLE = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.simulation.Fall15MiniAOD76X."+SAMPLE)
process.maxEvents.input = -1

process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

process.patJetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
                                    src     = cms.InputTag("slimmedJetsAK8"),
                                    levels  = ['L1FastJet','L2Relative','L3Absolute'],
                                    payload = 'AK8PFchs')

process.patJetsReapplyJEC = updatedPatJets.clone(
                                    jetSource = cms.InputTag("slimmedJetsAK8"),
                                    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC")) )

process.goodJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                                    filterParams = pfJetIDSelector.clone(),
                                    #src = cms.InputTag("patJetsReapplyJEC"),
                                    src = cms.InputTag("slimmedJetsAK8"),
                                    filter = cms.bool(True) )

process.corrJetsProducer = cms.EDProducer ( "CorrJetsProducer",
                                    jets    = cms.InputTag( "goodJets"                      ),
                                    vertex  = cms.InputTag( "offlineSlimmedPrimaryVertices" ), 
                                    rho     = cms.InputTag( "fixedGridRhoFastjetAll"        ),
                                    payload = cms.string  ( "AK8PFchs"                      ),
                                    isData  = cms.bool    (  False                          ))

process.ana = cms.EDAnalyzer(      "EDBRGenJetstudies",
                                    puWeights = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/pileupWeights69mb.root"))

process.p = cms.Path(               process.hadronicDecay               + 
                                    process.patJetCorrFactorsReapplyJEC +
                                    process.patJetsReapplyJEC           +
                                    process.goodJets                    +
                                    process.corrJetsProducer            +
                                    process.ana                         )

process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("tree_"+SAMPLE+".root") )
