import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '74X_mcRun2_asymptotic_v2'

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
                                                                                                    
CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True
                                                                                                   
#*********************************** CHOOSE SAMPLE **************************************************#

import sys
SAMPLE = str(sys.argv[2])
configXsecs = {
                  "WZ" : 47.13,
                  "ZZ" : 16.52,
              }
configNevents = {
                  "WZ" : 978512,
                  "ZZ" : 996944,
                }
usedXsec    = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

#************************************ CHOOSE YOUR HLT     *******************************************#

TRIGGER = str(sys.argv[3])
triggerPath = {
                "el" : "HLT_Ele105_CaloIdVT_GsfTrkIdT_v*",
                "mu" : "HLT_Mu45_eta2p1_v*",
              }
usedHLT = triggerPath[TRIGGER]

process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
process.hltFilter.triggerConditions =  ( usedHLT, )

#*********************************** POOL SOURCE ****************************************************#

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.source = cms.Source ("PoolSource",
    fileNames = cms.untracked.vstring(
         '/store/mc/RunIISpring15MiniAODv2/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/06181A51-9072-E511-88C0-3306CB18721E.root')
)

#********************************  MODULES *********************************************************#

process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")

process.bestLeptonicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "leptonicVSelector"           ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.bestHadronicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "hadronicV"                   ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay           = cms.string  ( "bestLeptonicV bestHadronicV" ),
                                          checkCharge     = cms.bool    (  False                        ),
                                          cut             = cms.string  ( "mass > 400."                 ),
                                          roles           = cms.vstring ( 'leptonicV', 'hadronicV'      ))

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src             = cms.InputTag( "graviton"                    ),
                                          minNumber       = cms.uint32  (  1                            ),
                                          filter          = cms.bool    (  True                         ))

process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool      (  False                      ),
                                          isData          = cms.bool      (  False                      ),
                                          originalNEvents = cms.int32     (  usedNevents                ),
                                          crossSectionPb  = cms.double    (  usedXsec                   ),
                                          targetLumiInvPb = cms.double    (  2093.917                   ),
                                          EDBRChannel     = cms.string    (  CHANNEL                    ),
                                          gravitonSrc     = cms.string    ( "graviton"                  ),
                                          metSrc          = cms.string    ( "slimmedMETs"               ),
                                          puWeights       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/pileupWeights69mb.root"),
                                          vertex          = cms.InputTag  ( "goodOfflinePrimaryVertex"  ))

#***************************************** SEQUENCES **********************************************# 
process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")
process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.leptonSequence = cms.Sequence(    process.hltSequence              +
                                          process.egmGsfElectronIDs        + 
                                          process.goodLeptonsProducer      +  
                                          process.leptonicVSequence        + 
                                          process.bestLeptonicV            )

process.jetSequence = cms.Sequence(       process.fatJetsSequence          +
                                          process.hadronicVSequence        +
                                          process.bestHadronicV            )

process.gravitonSequence = cms.Sequence(  process.graviton                 +
                                          process.gravitonFilter           )

process.analysis = cms.Path(              process.leptonSequence           +
                                          process.jetSequence              +
                                          process.gravitonSequence         +
                                          process.treeDumper               )

#************************************ TRIGGER REPORT DATA *******************************************#
# Supported for VZ channel only                                   

process.load("ExoDiBosonResonances.EDBRCommon.trigReportData_cff")
process.endpath = cms.EndPath( process.trigReportData )

#****************************************************************************************************#

#***************************************** FILTER MODE **********************************************#

filterMode = True       
if filterMode == False:
    process.hltFilter.triggerConditions = ('*',)
    process.goodLeptons.filter = False
    process.leptonicVSelector.cut = '70. < mass < 110.'
    process.graviton.cut = ''

#****************************************************************************************************#

if VZ_JetMET == True :
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
    process.graviton.decay = cms.string("goodMET hadronicV")
    process.graviton.cut   = cms.string("")
    process.graviton.roles = cms.vstring('goodMET', 'hadronicV')

    process.leptonSequence.remove(  process.leptonicVSequence,
                                    process.leptonicVSelector,
                                    process.leptonicVFilter)

    process.leptonSequence.replace( process.leptonSequence,
                                    process.leptonSequence +
                                    process.metSequence    )

print "++++++++++ CUTS ++++++++++\n"
print "HLT = "            + str(process.hltFilter.triggerConditions)
print "Graviton cut = "   + str(process.graviton.cut)
print "Leptonic V cut = " + str(process.leptonicVSelector.cut)
print "Hadronic V cut = " + str(process.hadronicV.cut)
print "\n++++++++++++++++++++++++++"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_Di_boson.root")
                                  )
