import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

#***************************************** Filter Mode **********************************************#
#                                                                                                    #
# True : Events are filtered before the analyzer. TTree is filled with good values only              #
# False: Events are filtered inside the analyzed. TTree is filled with dummy values when numCands==0 #
#                                                                                                    #
filterMode = True # True                      
#                                                                                                    #
#****************************************************************************************************#

SAMPLE="RSGravToZZ_kMpl01_M-2000_PHYS14"
#SAMPLE="DYJetsToLL_HT-100to200_PHYS14"
#SAMPLE="DYJetsToLL_HT-200to400_PHYS14"
#SAMPLE="DYJetsToLL_HT-400to600_PHYS14"
#SAMPLE="DYJetsToLL_HT-600toInf_PHYS14"

configXsecs = {"DYJetsToLL_HT-100to200_PHYS14" : 194.3,
               "DYJetsToLL_HT-200to400_PHYS14" : 53.24,
               "DYJetsToLL_HT-400to600_PHYS14" : 6.546,
               "DYJetsToLL_HT-600toInf_PHYS14" : 2.179,
               "RSGravToZZ_kMpl01_M-2000_PHYS14" : 1,
         }
configNevents = {"DYJetsToLL_HT-100to200_PHYS14" : 4054159,
                 "DYJetsToLL_HT-200to400_PHYS14" : 4666496,
                 "DYJetsToLL_HT-400to600_PHYS14" : 4931372,
                 "DYJetsToLL_HT-600toInf_PHYS14" : 4493574,
                 "RSGravToZZ_kMpl01_M-2000_PHYS14" : 1,
                 }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'PHYS14_25_V2::All'

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

### Adding softdrop manually
process.load("ExoDiBosonResonances.EDBRJets.redoSubstructure_cff")
process.load("ExoDiBosonResonances.EDBRJets.redoPatJets_cff")
process.goodJets.src = cms.InputTag("selectedPatJetsAK8")

#process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#process.GlobalTag.globaltag = 'PHYS14_25_V2'

process.jetSequence = cms.Sequence(process.substructureSequence +
                                   process.redoPatJets + 
                                   process.fatJetsSequence +
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

process.hadronicV.cut = str("pt > 100")

print "++++++++++ CUTS ++++++++++\n"
print "Graviton cut = "+str(process.graviton.cut)
print "Leptonic V cut = "+str(process.leptonicVSelector.cut)
print "Hadronic V cut = "+str(process.hadronicV.cut)
print "\n++++++++++++++++++++++++++"
print "Running over SAMPLE: "+SAMPLE
print "Number of events: "+str(usedNevents)
print "Cross sect. (pb): "+str(usedXsec)
   
process.treeDumper = cms.EDAnalyzer("EDBRTreeMaker",
                                    originalNEvents = cms.int32(usedNevents),
                                    crossSectionPb = cms.double(usedXsec),
                                    targetLumiInvPb = cms.double(3000.0),
                                    EDBRChannel = cms.string("VZ_CHANNEL"),
                                    isGen = cms.bool(False),
                                    hadronicVSrc = cms.string("hadronicV"),
                                    leptonicVSrc = cms.string("leptonicV"),
                                    gravitonSrc = cms.string("graviton"),
                                    metSrc = cms.string("slimmedMETs"),
                                    electronIDs = cms.InputTag("cutBasedElectronID-CSA14-PU20bx25-V0-standalone-veto")
                                    )


if option=='GEN':
    process.treeDumper.metSrc = 'genMetTrue'
    process.treeDumper.isGen  = True

### In case you need to select the decay channel at GEN level
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")

process.analysis = cms.Path(#process.leptonicDecay + 
                            #process.hadronicDecay + 
                            process.leptonSequence +
                            process.jetSequence +
                            process.gravitonSequence +
                            process.treeDumper)

if option=='RECO':
    process.analysis.replace(process.leptonSequence, process.goodOfflinePrimaryVertex + process.leptonSequence)

### Source
process.load("ExoDiBosonResonances.EDBRCommon.simulation."+SAMPLE)
#process.load("ExoDiBosonResonances.EDBRCommon.simulation.RSGravToZZ_kMpl01_M-2000_PHYS14")
#process.source.fileNames = ["/store/user/jruizvar/RSGravToZZ/M1000/RSGravToZZ_kMpl01_M-1000_Tune4C_13TeV-pythia8_MINIAODSIM_PU20bx25_1.root"]
#process.source.fileNames = ["/store/mc/Phys14DR/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/1898E9B3-9C6B-E411-88A4-00266CF327E0.root"]

process.maxEvents.input = -1

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+".root")
                                   )

# Other statements
#process.patJetsAK8.addJetCorrFactors = False                                                                             
#process.patJetsAK8.jetCorrFactorsSource = cms.VInputTag()

#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'PHYS14_25_V2', '')
