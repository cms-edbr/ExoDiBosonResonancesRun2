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
                                                                                                   
#*************************************** BLIND ANALYSIS *********************************************#

isBlinded = False

if isBlinded == True :
     JETMASSCUT = 'userFloat("ak8PFJetsCHSPrunedMass") > 20. & userFloat("ak8PFJetsCHSPrunedMass") < 60.'    
else :
     JETMASSCUT = 'userFloat("ak8PFJetsCHSPrunedMass") > 20. & userFloat("ak8PFJetsCHSPrunedMass") < 95.'    

#*********************************** POOL SOURCE ****************************************************#

import sys
SAMPLE = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RunIIDR74X.Diboson."+SAMPLE)

configXsecs = {  "WW-aa" : 118.7 ,
                 "WW-ab" : 118.7 ,
                 "WW-ac" : 118.7 ,
                 "WW-ad" : 118.7 ,
                 "WW-ae" : 118.7 ,
                 "WW-af" : 118.7 ,
                 "WZ-aa" :  66.1 , 
                 "WZ-ab" :  66.1 , 
                 "WZ-ac" :  66.1 , 
                 "WZ-ad" :  66.1 , 
                 "WZ-ae" :  66.1 , 
                 "WZ-af" :  66.1 , 
                 "ZZ-aa" :  15.4 ,
                 "ZZ-ab" :  15.4 ,
                 "ZZ-ac" :  15.4 ,
                 "ZZ-ad" :  15.4 ,
                 "ZZ-ae" :  15.4 ,
                 "ZZ-af" :  15.4 ,
              }

configNevents = {"WW-aa" : 994416,
                 "WW-ab" : 994416,
                 "WW-ac" : 994416,
                 "WW-ad" : 994416,
                 "WW-ae" : 994416,
                 "WW-af" : 994416,
                 "WZ-aa" : 991232,
                 "WZ-ab" : 991232,
                 "WZ-ac" : 991232,
                 "WZ-ad" : 991232,
                 "WZ-ae" : 991232,
                 "WZ-af" : 991232,
                 "ZZ-aa" : 996168,
                 "ZZ-ab" : 996168,
                 "ZZ-ac" : 996168,
                 "ZZ-ad" : 996168,
                 "ZZ-ae" : 996168,
                 "ZZ-af" : 996168,
                }

usedXsec    = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

#********************************  MODULES *********************************************************#

process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")

process.leptonicVFilter = cms.EDFilter(   "CandViewCountFilter",
                                          src             = cms.InputTag( "leptonicV"                   ),
                                          minNumber       = cms.uint32  (  1                            ),
                                          filter          = cms.bool    (  True                         ))

process.leptonicVSelector = cms.EDFilter( "CandViewSelector",
                                          src             = cms.InputTag( "leptonicV"                   ),
                                          cut             = cms.string  ( "pt > 20. & 70. < mass < 110."),
                                          filter          = cms.bool    (  True                         ))

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
                                          isData          = cms.bool    (  False                        ),
                                          originalNEvents = cms.int32   (  usedNevents                  ),
                                          crossSectionPb  = cms.double  (  usedXsec                     ),
                                          targetLumiInvPb = cms.double  (  122.86                       ),
                                          EDBRChannel     = cms.string  (  CHANNEL                      ),
                                          gravitonSrc     = cms.string  ( "graviton"                    ),
                                          metSrc          = cms.string  ( "slimmedMETs"                 ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex"    ),
                                          payload         = cms.string  ( "AK8PFchs"                    ))

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
                                          process.leptonicVFilter          +
                                          process.leptonicVSelector        + 
                                          process.bestLeptonicV            )

process.jetSequence = cms.Sequence(       process.fatJetsSequence          +
                                          process.hadronicV                +
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
