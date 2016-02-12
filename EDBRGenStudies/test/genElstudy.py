import FWCore.ParameterSet.Config as cms

process = cms.Process("MCMatch")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

daughterCharge  = "((daughter(0).charge == -daughter(1).charge) || \
                    (daughter(0).pdgId  == -daughter(1).pdgId))"

# Input source
import sys
SAMPLE = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.simulation.Fall15MiniAOD76X."+SAMPLE)
process.maxEvents.input = -1

process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = [
                  'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff',
                  'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff'
                ]
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.electronsMiniIsolationValueMap = cms.EDProducer("PatElectronMiniIsolationValueMap",
                                         r_iso_min = cms.double(0.05),
                                         r_iso_max = cms.double(0.2),
                                         kt_scale  = cms.double(10.),
                                         charged_only = cms.bool(False),
                                         rho     = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                                         leptons = cms.InputTag("slimmedElectrons"),
                                         pfCands = cms.InputTag("packedPFCandidates"))

process.goodElectrons = cms.EDProducer( "GoodElectronsProducer",
                                         electrons  = cms.InputTag("slimmedElectrons"),
                                         elIsoMap   = cms.InputTag("electronsMiniIsolationValueMap:eArea"),
                                         loose      = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose"),
                                         medium     = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium"),
                                         tight      = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight"),
                                         heep       = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"))

process.Ztoee = cms.EDProducer(         "CandViewCombiner",
                                         decay = cms.string("goodElectrons goodElectrons"),
                                         cut = cms.string("70 < mass < 110"),
                                         checkCharge = cms.bool(False) )

process.dilepton = cms.EDFilter(        "CandViewCountFilter",
                                         src = cms.InputTag("Ztoee"),
                                         minNumber = cms.uint32(1),
                                         filter = cms.bool(True) )

process.ZdaughterCharge = cms.EDFilter( "CandViewSelector",
                                         src = cms.InputTag("Ztoee"),
                                         cut = cms.string( daughterCharge ),
                                         filter = cms.bool(True) )

process.ana = cms.EDAnalyzer(           "EDBRGenElstudies" )

process.p = cms.Path(                    process.leptonicDecay                  + 
                                         process.electronsMiniIsolationValueMap +
                                         process.egmGsfElectronIDs              +
                                         process.goodElectrons                  +
                                         process.Ztoee                          + 
                                         process.dilepton                       +
                                         process.ZdaughterCharge                +
                                         process.ana                            )

process.TFileService = cms.Service(     "TFileService",
                                         fileName = cms.string("tree_"+SAMPLE+".root") )
