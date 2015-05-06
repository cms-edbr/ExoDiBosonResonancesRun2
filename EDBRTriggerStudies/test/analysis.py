import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

#***************************************** Filter Mode **********************************************#
#                                                                                                    #
# True : Events are filtered before the analyzer. TTree is filled with good valudes only             #
# False: Events are filtered inside the analyzed. TTree is filled with dummy values when numCands==0 #
#                                                                                                    #
filterMode = False # True                      
#                                                                                                    #
#****************************************************************************************************#

option = 'RECO' # 'GEN' or 'RECO'
### GEN level studies
if option == 'GEN':
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMuons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genFatJets_cff")
### RECO level studies
if option == 'RECO':
    process.load("ExoDiBosonResonances.EDBRCommon.goodMuons_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")

### Hadronic and leptonic boson.
### Naturally, you should choose the one channel you need
#process.load("ExoDiBosonResonances.EDBRCommon.leptonicW_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.hadronicW_cff")
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")

# Updates
if option == 'RECO':
    process.goodMuons.src = "slimmedMuons"
    process.goodElectrons.src = "slimmedElectrons"
    process.goodJets.src = "slimmedJetsAK8"
    #process.Wtoenu.MET  = "slimmedMETs"
    #process.Wtomunu.MET = "slimmedMETs"

if option == 'RECO':
    process.hadronicV.cut = \
        'pt > 100 &'+\
        '(userFloat("ak8PFJetsCHSPrunedLinks") > 50.0) &'+\
        '(userFloat("ak8PFJetsCHSPrunedLinks") < 110.0)'
if option == 'GEN':
    process.hadronicV.cut = \
        'pt > 100 &'+\
        '(userFloat("ak8GenJetsPrunedLinks") > 50.0) &'+\
        '(userFloat("ak8GenJetsPrunedLinks") < 110.0)'


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

### We should add some modules to remove multiple candidates at some point...

process.gravitonFilter =  cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("graviton"),
                                       minNumber = cms.uint32(1),
                                       filter = cms.bool(True)
                                       )

process.leptonSequence = cms.Sequence(process.muSequence +
                                      process.eleSequence +
                                      process.leptonicVSequence +
                                      process.leptonicVSelector +
                                      process.leptonicVFilter )

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
print "\n++++++++++++++++++++++++++"
   
process.treeDumper = cms.EDAnalyzer("EDBRTreeMaker",
                                    originalNEvents = cms.int32(1),
                                    crossSectionPb = cms.double(1),
                                    targetLumiInvPb = cms.double(1.0),
                                    EDBRChannel = cms.string("VZ_CHANNEL"),
                                    isGen = cms.bool(False),
                                    hadronicVSrc = cms.string("hadronicV"),
                                    leptonicVSrc = cms.string("leptonicV"),
                                    gravitonSrc = cms.string("graviton"),
                                    metSrc = cms.string("slimmedMETs"),
                                    electronIDs = cms.InputTag("cutBasedElectronID-CSA14-PU20bx25-V0-standalone-veto"),

                                    triggerSummaryAOD  = cms.InputTag("hltTriggerSummaryAOD"),
                                    HltPaths               = cms.vstring("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v1"),
                                    hltResultsCollection   = cms.InputTag( "TriggerResults", "", "HLT" ),
                                    HltFilters             = cms.vstring("hltDiEle33CaloIdLNewPixelMatchUnseededFilter"),
                                    
                                    TriggerResultsTag = cms.untracked.InputTag("TriggerResults", "", "HLT"),
                                    TriggerOSATag = cms.untracked.InputTag("selectedPatTrigger", "", "PAT"),
                                    PathName = cms.untracked.string("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v1"),
                                    triggerPrescales =  cms.untracked.InputTag("PackedTriggerPrescales", "", "PAT"),

                                    rhoTag = cms.untracked.InputTag("fixedGridRhoFastjetAll", "", "RECO")
                                    )


if option=='GEN':
    process.treeDumper.metSrc = 'genMetTrue'
    process.treeDumper.isGen  = True

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

### In case you need to select the decay channel at GEN level
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")

process.analysis = cms.Path(process.leptonicDecay + 
                            process.hadronicDecay + 
                            process.leptonSequence +
                            process.jetSequence +
                            process.gravitonSequence +
                            process.treeDumper)

if option=='RECO':
    process.analysis.replace(process.leptonSequence, process.goodOfflinePrimaryVertex + process.leptonSequence)

### Source
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.DYJetsToLL_HT-600toInf")
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.RSGravToZZ_kMpl01_M-1000")
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.Technicolor_pp_WP_ZW_eeqq_BM1_13tev-single")
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8_Phys14")
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.RSGravToZZ_kMpl01_M-1000_Tune4C_13TeV-pythia8_Phys14")
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.DYJetsToLL_HT-200to400_PHYS14")
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.DYJetsToLL_HT-400to600_PHYS14")

#process.source.fileNames = ["/store/user/jruizvar/RSGravToZZ/M1000/RSGravToZZ_kMpl01_M-1000_Tune4C_13TeV-pythia8_MINIAODSIM_PU20bx25_1.root"]
##process.source.fileNames = ["/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/1898E9B3-9C6B-E411-88A4-00266CF327E0.root"]

process.maxEvents.input = -1

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
#                                   fileName = cms.string("treeEDBR_RSGravToZZ_kMpl01_M-4500.root")
                                   fileName = cms.string("trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_newHEEPwIso_2002.root")
#                                   fileName = cms.string("trigEDBR_RSGravToZZ_kMpl01_M-1000_Phys14_newHEEPwIso_1802.root")
#                                   fileName = cms.string("trigDYJetsToLL_HT-200to400_Phys14_newHEEPwIso_1802.root")
                                   )
