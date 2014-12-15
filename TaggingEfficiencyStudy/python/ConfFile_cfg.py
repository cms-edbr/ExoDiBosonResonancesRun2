import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
"/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/00000/6C316E89-836F-E411-A3D7-00266CFFA6A8.root",
"/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/00000/8047AB86-836F-E411-80B8-002481E0DC4E.root",
"/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/10000/5E8C5398-0A70-E411-9538-0025904B1420.root",
"/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/10000/CA90E2E0-3976-E411-B96E-002590AC4C72.root",
"/store/mc/Phys14DR/RSGravitonToZZ_kMpl01_M_3000_Tune4C_13TeV_pythia8/MINIAODSIM/PU20bx25_PHYS14_25_V1-v1/10000/E2D1D38A-0A70-E411-BF6E-0025907FD424.root",    )
)


process.cleanPatJets = cms.EDProducer("PATJetCleaner",
    src = cms.InputTag("slimmedJetsAK8"), 

    # preselection (any string-based cut on pat::Jet)
    preselection = cms.string(''),

    # overlap checking configurables
    checkOverlaps = cms.PSet(
        muons = cms.PSet(
           src       = cms.InputTag("slimmedMuons"),
           algorithm = cms.string("byDeltaR"),
           preselection        = cms.string("pt > 20 && abs(eta) < 2.4"),
           deltaR              = cms.double(0.8),
           checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
           pairCut             = cms.string(""),
           requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared
        ),
        electrons = cms.PSet(
           src       = cms.InputTag("slimmedElectrons"),
           algorithm = cms.string("byDeltaR"),
           preselection        = cms.string("pt > 20 && abs(eta) < 2.4"),
           deltaR              = cms.double(0.8),
           checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
           pairCut             = cms.string(""),
           requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared
        ),
    ),
    # finalCut (any string-based cut on pat::Jet)
    finalCut = cms.string(''),
)

process.demo = cms.EDAnalyzer('TaggingEfficiencyStudy'
)


process.p = cms.Path(process.cleanPatJets + process.demo)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("histos.root")
                                   )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.cerr.FwkReport.limit = 99999999
