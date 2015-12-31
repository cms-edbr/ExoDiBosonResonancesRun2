import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '74X_dataRun2_v5'

# Use private JECs
usePrivateSQlite = False 
if usePrivateSQlite:
    from CondCore.DBCommon.CondDBSetup_cfi import *
    process.jec = cms.ESSource("PoolDBESSource",
        CondDBSetup,
        connect = cms.string("sqlite_file:Summer15_25nsV6_DATA.db"),
        toGet =  cms.VPSet(
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_Summer15_25nsV6_DATA_AK8PFchs"),
                label= cms.untracked.string("AK8PFchs")
            ),
        )
    )
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
                                                                                                    
CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True
                                                                                                   
#************************************ CHOOSE YOUR HLT     *******************************************#

triggerPath = {
                "el" : "HLT_Ele105_CaloIdVT_GsfTrkIdT_v*",
                "mu" : "HLT_Mu45_eta2p1_v*",
              }
import sys
TRIGGER = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
process.hltFilter.triggerConditions =  ( triggerPath[TRIGGER], )
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")

if TRIGGER == "el" :
    process.kinElectrons.filter   = cms.bool(True)
    process.idElectrons.filter    = cms.bool(True)
    process.isoElectrons.filter   = cms.bool(True)
    process.leptonicVFilter.src   = "Ztoee"
    process.leptonicVSelector.src = "Ztoee"

if TRIGGER == "mu" :
    process.kinMuons.filter       = cms.bool(True)
    process.idMuons.filter        = cms.bool(True)
    process.isoMuons.filter       = cms.bool(True)
    process.leptonicVFilter.src   = "Ztomumu"
    process.leptonicVSelector.src = "Ztomumu"

#*********************************** POOL SOURCE ****************************************************#

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.source = cms.Source ("PoolSource",
    fileNames = cms.untracked.vstring(
         '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v4/000/258/159/00000/6CA1C627-246C-E511-8A6A-02163E014147.root',
    )
)

#************************************* JSON file ***************************************************#
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/
# last modified 18-Dic-2015 

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(
    filename = '../Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_Silver_v2.txt').getVLuminosityBlockRange()

#********************************  MODULES *********************************************************#

process.corrJetsProducer.isData = True

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
                                          isGen           = cms.bool    (  False                        ),
                                          originalNEvents = cms.int32   (  1                            ),
                                          crossSectionPb  = cms.double  (  1.                           ),
                                          targetLumiInvPb = cms.double  (  1.                           ),
                                          EDBRChannel     = cms.string  (  CHANNEL                      ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex"    ))

#***************************************** SEQUENCES **********************************************# 
process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#Change vertex collection in Dxy cut
process.egmGsfElectronIDs.physicsObjectIDs[0].idDefinition.cutFlow[9].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"

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
                                   fileName = cms.string("treeEDBR_data.root")
                                  )
