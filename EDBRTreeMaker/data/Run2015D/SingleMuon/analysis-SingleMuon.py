import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '74X_dataRun2_v2'

# Use private JECs since the GTs are not updated
usePrivateSQlite = True 
if usePrivateSQlite:
    import os
    dataBasePath = os.path.expandvars("../../Summer15_25nsV5_DATA.db")
    from CondCore.DBCommon.CondDBSetup_cfi import *
    process.jec = cms.ESSource("PoolDBESSource",
        CondDBSetup,
        connect = cms.string("sqlite:"+dataBasePath),
        toGet =  cms.VPSet(
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_Summer15_25nsV5_DATA_AK8PFchs"),
                label= cms.untracked.string("AK8PFchs")
            ),
        )
    )
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
                                                                                                    
CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True
                                                                                                   
#*************************************** BLIND ANALYSIS *********************************************#

isBlinded = True # False

if isBlinded == True :
     JETMASSCUT = 'pt>200. & userFloat("ak8PFJetsCHSCorrPrunedMass") > 40. & userFloat("ak8PFJetsCHSCorrPrunedMass") < 65.'    
else :
     JETMASSCUT = 'pt>200. & userFloat("ak8PFJetsCHSCorrPrunedMass") > 40. & userFloat("ak8PFJetsCHSCorrPrunedMass") < 105.'    

#*********************************** POOL SOURCE ****************************************************#

import sys
SAMPLE = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.PromptReco.Run2015D.SingleMuon."+SAMPLE)

#************************************* JSON file ***************************************************#
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/
# last modified 25-Sep-2015 

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(
    filename = '../../Cert_246908-257599_13TeV_PromptReco_Collisions15_25ns_JSON.txt').getVLuminosityBlockRange()

#********************************  MODULES *********************************************************#

process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")

process.corrJetsProducer.isData = True

process.bestLeptonicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "leptonicVSelector"           ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.hadronicV.cut = cms.string(       JETMASSCUT                                                     )

process.bestHadronicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "hadronicV"                   ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay           = cms.string  ( "bestLeptonicV bestHadronicV" ),
                                          checkCharge     = cms.bool    (  False                        ),
                                          cut             = cms.string  ( " "                           ),
                                          roles           = cms.vstring ( 'leptonicV', 'hadronicV'      ))

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src             = cms.InputTag( "graviton"                    ),
                                          minNumber       = cms.uint32  (  1                            ),
                                          filter          = cms.bool    (  True                         ))

process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool    (  False                        ),
                                          originalNEvents = cms.int32   (  1                            ),
                                          crossSectionPb  = cms.double  (  1.                           ),
                                          targetLumiInvPb = cms.double  (  1000.                        ),
                                          EDBRChannel     = cms.string  (  CHANNEL                      ),
                                          gravitonSrc     = cms.string  ( "graviton"                    ),
                                          metSrc          = cms.string  ( "slimmedMETs"                 ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex"    ))

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
print "Graviton cut = "+str(process.graviton.cut)
print "Leptonic V cut = "+str(process.leptonicVSelector.cut)
print "Hadronic V cut = "+str(process.hadronicV.cut)
print "\n++++++++++++++++++++++++++"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+".root")
                                  )
