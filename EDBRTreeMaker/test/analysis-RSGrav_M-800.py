import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Delivers "L1GtStableParametersRcd" record in the EventSetup
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtConfig_cff")

#***************************************** FILTER MODE **********************************************#
#                                                                                                    #
# True : Events are filtered before the analyzer. TTree is filled with good valudes only             #
# False: Events are filtered inside the analyzed. TTree is filled with dummy values when numCands==0 #
#                                                                                                    #
filterMode = True                      
#filterMode = False
#                                                                                                    #
#****************************************************************************************************#

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
#                                                                                                    #
#VZ_semileptonic = False
VZ_semileptonic = True
#VZ_JetMET  = True
VZ_JetMET  = False
#                                                                                                    #
#****************************************************************************************************#

#*********************************** THE SAMPLES *****************************************************#
# choose the sample                                                                     

#SAMPLE="RSGravToZZToLLQQ_M-600" 
SAMPLE="RSGravToZZToLLQQ_M-800" 
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

configXsecs = {  "RSGravToZZToLLQQ_M-600"         : 0.908025,
                 "RSGravToZZToLLQQ_M-800"         : 0.274593,
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

#************************************** SELECT GEN OR RECO ******************************************# 
option = 'RECO' 
#option = 'GEN'
### GEN level studies
if option == 'GEN':
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMuons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genFatJets_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMET_cff")
### RECO level studies
if option == 'RECO':
    process.load("ExoDiBosonResonances.EDBRCommon.goodMuons_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
### Hadronic and leptonic boson.
### Naturally, you should choose the one channel you need
#process.load("ExoDiBosonResonances.EDBRCommon.leptonicW_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.hadronicW_cff")
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")

if option == 'RECO':
    process.hadronicV.cut = \
        'pt > 100 &'+\
        '(userFloat("ak8PFJetsCHSSoftDropMass") > 50.0) &'+\
        '(userFloat("ak8PFJetsCHSSoftDropMass") < 110.0)'
    process.goodMET.cut = "pt > 250"	
if option == 'GEN':
    process.hadronicV.cut = \
        'pt > 100 &'+\
        '(userFloat("ak8GenJetsSoftDropMass") > 50.0) &'+\
        '(userFloat("ak8GenJetsSoftDropMass") < 110.0)'
#*******************************************************************************************************#

process.goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
                                       src = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                       cut = cms.string("chi2!=0 && ndof >= 4.0 && abs(z) <= 24.0 && abs(position.Rho) <= 2.0"),
                                       filter = cms.bool(True)
                                       )

WBOSONCUT = "pt > 100.0 & sqrt(2.0*daughter(0).pt()*daughter(1).pt()*(1.0-cos(daughter(0).phi()-daughter(1).phi()))) > 50.0"
ZBOSONCUT = "pt > 100.0 & 70.0 < mass < 110.0"

process.leptonicVSelector = cms.EDFilter("CandViewSelector",
                                       src = cms.InputTag("leptonicV"),
                                       cut = cms.string( ZBOSONCUT ), #Change in case of WChannel
                                       filter = cms.bool(True)
                                       )

process.leptonicVFilter = cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("leptonicV"),
                                       minNumber = cms.uint32(1),
                                       filter = cms.bool(True)
                                       )
process.hadronicVFilter = cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("hadronicV"),
                                       minNumber = cms.uint32(1),
                                       filter = cms.bool(True)
                                       )

process.graviton = cms.EDProducer("CandViewCombiner",
                                       decay = cms.string("leptonicV hadronicV"),
                                       checkCharge = cms.bool(False),
                                       cut = cms.string("mass > 180"),
                                       roles = cms.vstring('leptonicV', 'hadronicV'),
                                       )
if VZ_JetMET == True :
   process.graviton.decay = cms.string("goodMET hadronicV")
   process.graviton.cut   = cms.string("")
   process.graviton.roles = cms.vstring('goodMET', 'hadronicV')

### We should add some modules to remove multiple candidates at some point...

process.gravitonFilter =  cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("graviton"),
                                       minNumber = cms.uint32(1),
                                       filter = cms.bool(True)
                                       )

process.leptonSequence = cms.Sequence(process.muSequence +
                                      process.eleSequence)


if VZ_semileptonic == True :
   process.leptonSequence.replace(process.eleSequence, process.eleSequence + process.leptonicVSequence + process.leptonicVSelector + process.leptonicVFilter)

process.jetSequence = cms.Sequence(process.fatJetsSequence +
                                   process.hadronicV +
                                   process.hadronicVFilter)

process.gravitonSequence = cms.Sequence(process.graviton +
                                        process.gravitonFilter)

### If you're running in signal, you may want to not filter at this level
### but only later at the tree analysis.
if filterMode == False:
    process.goodOfflinePrimaryVertex.filter = False
    process.Ztomumu.cut = ''
    process.Ztoee.cut = ''
    process.leptonicVSelector.filter = False
    process.leptonicVSelector.cut = ''
    process.hadronicV.cut = ''
    process.graviton.cut = ''
    process.leptonicVFilter.minNumber = 0
    process.hadronicVFilter.minNumber = 0
    process.gravitonFilter.minNumber = 0

print "++++++++++ CUTS ++++++++++\n"
print "Graviton cut = "+str(process.graviton.cut)
print "Leptonic V cut = "+str(process.leptonicVSelector.cut)
print "Hadronic V cut = "+str(process.hadronicV.cut)
##print "MET cut = "+str(process.goodMET.cut)
print "\n++++++++++++++++++++++++++"

CHANNEL = "VZ_CHANNEL"
if VZ_JetMET == True : 
   CHANNEL = "VZnu_CHANNEL"  
   
process.miniIsolation = cms.EDProducer("miniPFIsolationProducer",
                                      r_iso_min = cms.double(0.05),
                                      r_iso_max = cms.double(0.2),
                                      kt_scale  = cms.double(10.),
                                      charged_only = cms.bool(False),
                                      electrons = cms.InputTag("goodElectrons"),
                                      muons = cms.InputTag("goodMuons"),
                                      pfCands = cms.InputTag("packedPFCandidates")
                                      )

process.treeDumper = cms.EDAnalyzer("EDBRTreeMaker",
                                    originalNEvents = cms.int32(usedNevents),
                                    crossSectionPb = cms.double(usedXsec),
                                    targetLumiInvPb = cms.double(1000.0),
                                    EDBRChannel = cms.string(CHANNEL),
                                    isGen = cms.bool(False),
                                    gravitonSrc = cms.string("graviton"),
                                    metSrc = cms.string("slimmedMETs"),
                                    elmediumID = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium"),
                                    eltightID  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight"),
                                    elheepID   = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV51"),
                                    hltToken = cms.InputTag("TriggerResults","","HLT"),
                                    elPaths = cms.vstring("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_*","HLT_Ele95_*"), 
                                    muPaths = cms.vstring("HLT_Mu30_TkMu11_v*","HLT_Mu40_v*","HLT_IsoMu24_*IterTrk02_v*") 
                                    )

if option=='GEN':
    process.treeDumper.metSrc = 'genMetTrue'
    process.treeDumper.isGen  = True

### In case you need to select the decay channel at GEN level
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectMETDecay")

process.analysis = cms.Path(process.leptonSequence    +
                            process.metSequence       + 
                            process.jetSequence       +
                            process.gravitonSequence  +
                            process.miniIsolation     +
                            process.treeDumper)


if VZ_semileptonic == True :
   #process.analysis.replace(process.leptonSequence, process.leptonicDecay + process.hadronicDecay + process.leptonSequence)
   process.analysis.remove(process.metSequence)

if option=='RECO':
    from ExoDiBosonResonances.EDBRCommon.goodElectrons_cff import addElectronIDs
    process.analysis.replace(process.leptonSequence, process.goodOfflinePrimaryVertex + process.leptonSequence)
    process = addElectronIDs(process)

### Source
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RunIIDR74X."+SAMPLE)

process.maxEvents.input = -1

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+".root")
                                   )
