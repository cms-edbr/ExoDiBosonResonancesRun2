import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1'

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
                                                                                                    
CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True
                                                                                                   
#*********************************** CHOOSE SAMPLE **************************************************#

import sys
SAMPLE = str(sys.argv[2])
configXsecs = {
                  #"HT-100to200" : 221.37, # 139.4 x 1.588
                  #"HT-200to400" : 61.47,  # 42.75 x 1.438
                  #"HT-400to600" : 8.212,  # 5.497 x 1.494
                  #"HT-600toInf" : 2.517,  # 2.21  x 1.139
                  "HT-100to200" : 181.30, # 147.40 x 1.23
                  "HT-200to400" : 50.42,  # 40.99  x 1.23
                  "HT-400to600" : 6.984,  # 5.678  x 1.23
                  "HT-600toInf" : 2.704,  # 2.198  x 1.23
                  "WW"          : 118.7,
                  "WZ"          : 47.13,
                  "ZZ"          : 16.52,
                  "TT"          : 831.76,
              }
configNevents = {
                  "HT-100to200" : 2655294,
                  "HT-200to400" : 962195,
                  "HT-400to600" : 1069003,
                  "HT-600toInf" : 1031103,
                  "WW"          : 988418,
                  "WZ"          : 1000000,
                  "ZZ"          : 985600,
                  "TT"          : 19090400,
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
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")
if TRIGGER == "el" :
    process.kinElectrons.filter   = cms.bool(True)
    process.idElectrons.filter    = cms.bool(True)
    process.leptonicVFilter.src   = "Ztoee"
    process.ZdaughterCharge.src   = "Ztoee"

if TRIGGER == "mu" :
    process.kinMuons.filter       = cms.bool(True)
    process.idMuons.filter        = cms.bool(True)
    process.leptonicVFilter.src   = "Ztomumu"
    process.ZdaughterCharge.src   = "Ztomumu"
    process.leptonicVSelector.src = "ZdaughterIso"
    process.leptonicVSequence.replace( process.ZdaughterCharge, 
                                       process.ZdaughterCharge + process.ZdaughterIso )

#*********************************** POOL SOURCE ****************************************************#

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source ("PoolSource",
    fileNames = cms.untracked.vstring(
         '/store/mc/RunIIFall15MiniAODv2/TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/04D51FB4-B2B8-E511-A399-047D7B881D6A.root')
         #'/store/mc/RunIIFall15MiniAODv1/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/345E23FA-FCA7-E511-9212-02163E01654F.root')
)

#********************************  MODULES *********************************************************#

process.bestLeptonicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "leptonicVSelector"           ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.bestHadronicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "hadronicV"                   ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay           = cms.string  ( "bestLeptonicV bestHadronicV" ),
                                          checkCharge     = cms.bool    (  False                        ),
                                          cut             = cms.string  ( ""                            ),
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
                                          targetLumiInvPb = cms.double    (  2630.245                   ),
                                          EDBRChannel     = cms.string    (  CHANNEL                    ),
                                          puWeights       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/pileupWeights69mb.root"),
                                          vertex          = cms.InputTag  ( "goodOfflinePrimaryVertex"  ))

#***************************************** SEQUENCES **********************************************# 
process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = [
                  'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff',
                  'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff'
                ]
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#Change vertex collection in Dxy cut
process.egmGsfElectronIDs.physicsObjectIDs[0].idDefinition.cutFlow[9].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"
process.egmGsfElectronIDs.physicsObjectIDs[1].idDefinition.cutFlow[6].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"
process.egmGsfElectronIDs.physicsObjectIDs[1].idDefinition.cutFlow[7].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"

process.leptonSequence = cms.Sequence(    process.hltSequence              +
                                          process.goodLeptonsProducer      +  
                                          process.leptonicVSequence        + 
                                          process.bestLeptonicV            )

process.leptonSequence.replace(           process.goodOfflinePrimaryVertex,
                                          process.goodOfflinePrimaryVertex +
                                          process.egmGsfElectronIDs        )

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
                                   fileName = cms.string("treeEDBR_background.root")
                                  )
