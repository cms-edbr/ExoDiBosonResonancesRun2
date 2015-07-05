import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Delivers L1GtStableParametersRcd record in the EventSetup
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtConfig_cff")

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
#                                                                                                    #
CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True
#                                                                                                    #
#****************************************************************************************************#

#*********************************** THE SAMPLES ****************************************************#
# choose the sample                                                                     

#SAMPLE="RSGravToZZToLLQQ_M-600" 
#SAMPLE="RSGravToZZToLLQQ_M-800" 
#SAMPLE="RSGravToZZToLLQQ_M-1000" 
#SAMPLE="RSGravToZZToLLQQ_M-1200" 
#SAMPLE="RSGravToZZToLLQQ_M-1400" 
#SAMPLE="RSGravToZZToLLQQ_M-1600" 
#SAMPLE="RSGravToZZToLLQQ_M-1800" 
#SAMPLE="RSGravToZZToLLQQ_M-2000" 
#SAMPLE="RSGravToZZToLLQQ_M-2500" 
#SAMPLE="RSGravToZZToLLQQ_M-3000" 
#SAMPLE="RSGravToZZToLLQQ_M-3500" 
#SAMPLE="RSGravToZZToLLQQ_M-4000" 
SAMPLE="RSGravToZZToLLQQ_M-4500" 
#SAMPLE="RSGravToZZ_kMpl01_M-1000" 
#SAMPLE="RSGravToZZ_kMpl01_M-1800"
#SAMPLE="RSGravToZZ_kMpl01_M-2000_PHYS14"
#SAMPLE="RSGravToZZ_kMpl01_M-3000_PHYS14"
#SAMPLE="RSGravToZZ_kMpl01_M-4000_PHYS14"
##SAMPLE="DYJetsToLL_HT-100to200_PHYS14"
#SAMPLE="DYJetsToLL_HT-200to400_PHYS14"
#SAMPLE="DYJetsToLL_HT-400to600_PHYS14"
#SAMPLE="DYJetsToLL_HT-600toInf_PHYS14"
#SAMPLE="ZJetsToNuNu_HT-100to200_PHYS14"
#SAMPLE="ZJetsToNuNu_HT-200to400_PHYS14"
#SAMPLE="ZJetsToNuNu_HT-400to600_PHYS14"
#SAMPLE="ZJetsToNuNu_HT-600toInf_PHYS14"
#SAMPLE="WJetsToLNu_HT-100to200_PHYS14"
#SAMPLE="WJetsToLNu_HT-200to400_PHYS14"
#SAMPLE="WJetsToLNu_HT-400to600_PHYS14"
#SAMPLE="WJetsToLNu_HT-600toInf_PHYS14"

### Source
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RunIIDR74X."+SAMPLE)
process.maxEvents.input = -1

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

configXsecs = {  "RSGravToZZToLLQQ_M-600"         : 0.908025,
                 "RSGravToZZToLLQQ_M-800"         : 0.274593,
                 "RSGravToZZToLLQQ_M-1000"        : 0.0811175,
                 "RSGravToZZToLLQQ_M-1200"        : 0.0295627,
                 "RSGravToZZToLLQQ_M-1400"        : 0.01232,
                 "RSGravToZZToLLQQ_M-1600"        : 0.00605376,
                 "RSGravToZZToLLQQ_M-1800"        : 0.00283966,
                 "RSGravToZZToLLQQ_M-2000"        : 0.00156097,
                 "RSGravToZZToLLQQ_M-2500"        : 0.000372413,
                 "RSGravToZZToLLQQ_M-3000"        : 8.28108e-05,
                 "RSGravToZZToLLQQ_M-3500"        : 2.76551e-05,
                 "RSGravToZZToLLQQ_M-4000"        : 8.54621e-06,
                 "RSGravToZZToLLQQ_M-4500"        : 2.65225e-06,
                 "RSGravToZZ_kMpl01_M-1000"       : 1.202,
                 "RSGravToZZ_kMpl01_M-1800"       : 0.05024,
                 "RSGravToZZ_kMpl01_M-2000_PHYS14": 0.02284,
                 "RSGravToZZ_kMpl01_M-3000_PHYS14": 0.001454,
                 "RSGravToZZ_kMpl01_M-4000_PHYS14": 0.0001357,
                 "ZJetsToNuNu_HT-100to200_PHYS14" : 372.6,
                 "ZJetsToNuNu_HT-200to400_PHYS14" : 100.8,
                 "ZJetsToNuNu_HT-400to600_PHYS14" : 11.99,
                 "ZJetsToNuNu_HT-600toInf_PHYS14" : 4.113,
                 "WJetsToLNu_HT-100to200_PHYS14"  : 1817.0,
                 "WJetsToLNu_HT-200to400_PHYS14"  : 471.6,
                 "WJetsToLNu_HT-400to600_PHYS14"  : 55.61,
                 "WJetsToLNu_HT-600toInf_PHYS14"  : 18.81,
                 "DYJetsToLL_HT-100to200_PHYS14"  : 194.3,
                 "DYJetsToLL_HT-200to400_PHYS14"  : 52.24,
                 "DYJetsToLL_HT-400to600_PHYS14"  : 6.546,
                 "DYJetsToLL_HT-600toInf_PHYS14"  : 2.179,
              }

configNevents = {"RSGravToZZToLLQQ_M-600"         : 30857,
                 "RSGravToZZToLLQQ_M-800"         : 31071,
                 "RSGravToZZToLLQQ_M-1000"        : 31229,
                 "RSGravToZZToLLQQ_M-1200"        : 31222,
                 "RSGravToZZToLLQQ_M-1400"        : 31127,
                 "RSGravToZZToLLQQ_M-1600"        : 31091,
                 "RSGravToZZToLLQQ_M-1800"        : 31075,
                 "RSGravToZZToLLQQ_M-2000"        : 31091,
                 "RSGravToZZToLLQQ_M-2500"        : 31147,
                 "RSGravToZZToLLQQ_M-3000"        : 31389,
                 "RSGravToZZToLLQQ_M-3500"        : 31034,
                 "RSGravToZZToLLQQ_M-4000"        : 31334,
                 "RSGravToZZToLLQQ_M-4500"        : 30787,
                 "RSGravToZZ_kMpl01_M-1000"       : 29586,
                 "RSGravToZZ_kMpl01_M-1800"       : 100000,
                 "RSGravToZZ_kMpl01_M-2000_PHYS14": 29744,
                 "RSGravToZZ_kMpl01_M-3000_PHYS14": 29209,
                 "RSGravToZZ_kMpl01_M-4000_PHYS14": 30000,
                 "ZJetsToNuNu_HT-100to200_PHYS14" : 4986424,
                 "ZJetsToNuNu_HT-200to400_PHYS14" : 4546470,
                 "ZJetsToNuNu_HT-400to600_PHYS14" : 4433784,
                 "ZJetsToNuNu_HT-600toInf_PHYS14" : 4463806,
                 "WJetsToLNu_HT-100to200_PHYS14"  : 5262265,
                 "WJetsToLNu_HT-200to400_PHYS14"  : 4936077,
                 "WJetsToLNu_HT-400to600_PHYS14"  : 4640594,
                 "WJetsToLNu_HT-600toInf_PHYS14"  : 4581841,
                 "DYJetsToLL_HT-100to200_PHYS14"  : 4054159,
                 "DYJetsToLL_HT-200to400_PHYS14"  : 4666496,
                 "DYJetsToLL_HT-400to600_PHYS14"  : 4931372,
                 "DYJetsToLL_HT-600toInf_PHYS14"  : 4493574,
                }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

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
                                          originalNEvents = cms.int32(usedNevents),
                                          crossSectionPb  = cms.double(usedXsec),
                                          targetLumiInvPb = cms.double(1000.0),
                                          EDBRChannel = cms.string(CHANNEL),
                                          isGen       = cms.bool(False),
                                          gravitonSrc = cms.string("graviton"),
                                          metSrc      = cms.string("slimmedMETs"),
                                          vertex      = cms.InputTag("goodOfflinePrimaryVertex"),
                                          elmediumID  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"),
                                          eltightID   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight"),
                                          elheepID    = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV51"),
                                          hltToken    = cms.InputTag("TriggerResults","","HLT"),
                                          elPaths     = cms.vstring("HLT_Ele105_CaloIdVT_GsfTrkIdT_v*"), 
                                          muPaths     = cms.vstring("HLT_Mu45_eta2p1_v*") ) 

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

#************************************ TRIGGER REPORT ANALYZER ***************************************#
#                                                                                                    #
# Only supported for VZ channel                                                                      #
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.trigReportAnalyzer_cff")
process.analysis.replace(process.hltSequence,
                         process.leptonicDecay +
                         process.hadronicDecay +
                         process.hltSequence   )

process.endpath = cms.EndPath( process.trigReportAnalyzer )
#                                                                                                    #
#****************************************************************************************************#

#***************************************** FILTER MODE **********************************************#
#                                                                                                    #
# True : Events are filtered before the analyzer. TTree is filled with good valudes only             #
# False: Events are filtered inside the analyzed. TTree is filled with dummy values when numCands==0 #
#                                                                                                    #
filterMode = True   # False       
### If you're running in signal, you may want to not filter at this level
### but only later at the tree analysis.
if filterMode == False:
    process.goodLeptons.filter = False
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
