import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# find the global tag in the DAS under the Configs for given dataset
process.GlobalTag.globaltag = 'MCRUN2_74_V9::All'

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
#                                                                                                    #
CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True
#                                                                                                    #
#****************************************************************************************************#

#*********************************** THE SAMPLES ****************************************************#
# choose the sample                                                                     

SAMPLE="SingleElectron_Run2015B" 

### Source
process.load("ExoDiBosonResonances.EDBRCommon.PromptReco."+SAMPLE)
process.maxEvents.input = -1

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

configXsecs = {  "SingleElectron_Run2015B"         : 1.0,
              }

configNevents = {"SingleElectron_Run2015B"         : 1,
                }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

#*********************************** JSON file ****************************************************#
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/
# last modified 15-Jul-2015 
import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_246908-251252_13TeV_PromptReco_Collisions15.json').getVLuminosityBlockRange()

#*******************************************************************************************************#

### Hadronic and leptonic boson.
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.leptonicW_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.hadronicW_cff")

WBOSONCUT = "pt > 200. & sqrt(2.0*daughter(0).pt()*daughter(1).pt()*(1.0-cos(daughter(0).phi()-daughter(1).phi()))) > 50."
ZBOSONCUT = "pt > 200. & 70. < mass < 110."

process.leptonicVSelector = cms.EDFilter( "CandViewSelector",
                                          src = cms.InputTag("leptonicV"),
                                          cut = cms.string( ZBOSONCUT ), #Change in case of WChannel
                                          filter = cms.bool(True) )

process.leptonicVFilter = cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("leptonicV"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

process.hadronicVFilter = cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("hadronicV"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay = cms.string("leptonicV hadronicV"),
                                          checkCharge = cms.bool(False),
                                          cut = cms.string("mass > 400"),
                                          roles = cms.vstring('leptonicV', 'hadronicV') )

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("graviton"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool    (  False                                                                      ),
                                          originalNEvents = cms.int32   (  usedNevents                                                                ),
                                          crossSectionPb  = cms.double  (  usedXsec                                                                   ),
                                          targetLumiInvPb = cms.double  (  1000.0                                                                     ),
                                          EDBRChannel     = cms.string  (  CHANNEL                                                                    ),
                                          gravitonSrc     = cms.string  ( "graviton"                                                                  ),
                                          metSrc          = cms.string  ( "slimmedMETs"                                                               ),
                                          elPaths         = cms.vstring ( "HLT_Ele105_CaloIdVT_GsfTrkIdT_v*"                                          ), 
                                          muPaths         = cms.vstring ( "HLT_Mu45_eta2p1_v*"                                                        ), 
                                          hltToken        = cms.InputTag( "TriggerResults","","HLT"                                                   ),
                                          hltObjects      = cms.InputTag( "selectedPatTrigger"                                                        ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex"                                                  ),
                                          elmediumID      = cms.InputTag( "egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium" ),
                                          eltightID       = cms.InputTag( "egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight"  ),
                                          heepV60ID       = cms.InputTag( "egmGsfElectronIDs:heepElectronID-HEEPV60"                                  )

#************************************** SELECT GEN OR RECO ******************************************# 

option = 'RECO' # 'GEN' 

### GEN level studies
if option == 'GEN':
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMuons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genFatJets_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMET_cff")
    process.treeDumper.metSrc = 'genMetTrue'
    process.treeDumper.isGen  = True
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8GenJetsSoftDropMass") > 50.) '
                                       '& (userFloat("ak8GenJetsSoftDropMass") < 110.)')

### RECO level studies
if option == 'RECO':
    process.load("ExoDiBosonResonances.EDBRCommon.goodMuons_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") > 50.) '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") < 110.)')

#***************************************** SEQUENCES **********************************************# 

process.leptonSequence = cms.Sequence(    process.muSequence        +
                                          process.eleSequence       +
                                          process.leptonicVSequence + 
                                          process.leptonicVSelector + 
                                          process.leptonicVFilter   )

process.jetSequence = cms.Sequence(       process.fatJetsSequence   +
                                          process.hadronicV         +
                                          process.hadronicVFilter   )

process.gravitonSequence = cms.Sequence(  process.graviton          +
                                          process.gravitonFilter    )

process.analysis = cms.Path(              process.leptonSequence    +
                                          process.jetSequence       +
                                          process.gravitonSequence  +
                                          process.treeDumper        )

if option=='RECO':
    from ExoDiBosonResonances.EDBRCommon.goodElectrons_cff import addElectronIDs
    process = addElectronIDs(process)
    process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
    process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")
    process.analysis.replace(process.leptonSequence, 
                             process.hltSequence              +
                             process.egmGsfElectronIDSequence + 
                             process.goodLeptonsProducer      +  
                             process.leptonSequence           ) 

#************************************ TRIGGER REPORT DATA *******************************************#
#                                                                                                    #
# Only supported for VZ channel, running on DATA or MC background                                    #
#
process.load("ExoDiBosonResonances.EDBRCommon.trigReportData_cff")
process.endpath = cms.EndPath( process.trigReportData )
#                                                                                                    #
#****************************************************************************************************#

#***************************************** FILTER MODE **********************************************#
#                                                                                                    #
# True : Events are filtered before the analyzer. TTree is filled with good valudes only             #
# False: Events are filtered inside the analyzed. TTree is filled with dummy values when numCands==0 #
#                                                                                                    #
filterMode = True #False       
### If you're running in signal, you may want to not filter at this level
### but only later at the tree analysis.
if filterMode == False:
    process.goodLeptons.filter = False
    process.goodElectrons.cut = ''
    process.goodMuons.cut = ''
    process.Ztomumu.cut = ''
    process.Ztoee.cut = ''
    process.leptonicVSelector.filter = False
    process.leptonicVSelector.cut = ''
    process.hadronicV.cut = ''
    process.graviton.cut = ''
    process.leptonicVFilter.minNumber = 0
    process.hadronicVFilter.minNumber = 0
    process.gravitonFilter.minNumber  = 0
    process.analysis.remove( process.hltSequence )
    del process.endpath
#                                                                                                    #
#****************************************************************************************************#

if VZ_JetMET == True :
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
