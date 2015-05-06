import FWCore.ParameterSet.Config as cms

from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJets
from RecoJets.Configuration.RecoGenJets_cff import ak8GenJets
from RecoJets.JetProducers.SubJetParameters_cfi import SubJetParameters

ak8GenJetsPruned = ak8GenJets.clone(
	SubJetParameters,
	usePruning = cms.bool(True),
	useExplicitGhosts = cms.bool(True),
	writeCompound = cms.bool(True),
	jetCollInstanceName=cms.string("SubJets")
	)

ak8GenJetsPrunedLinks = cms.EDProducer("RecoJetDeltaRValueMapProducer",
					       src = cms.InputTag("ak8GenJets"),
					       matched = cms.InputTag("ak8GenJetsPruned"),
					       distMax = cms.double(0.8),
					       value = cms.string('mass')
					       )

from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import patJets as patJets

goodJets = patJets.clone(
    jetSource = "ak8GenJets",
    embedCaloTowers = cms.bool(False),
    embedPFCandidates = cms.bool(False),
    addJetCorrFactors = cms.bool(False),
    addBTagInfo = cms.bool(False),
    addDiscriminators = cms.bool(False), 
    addAssociatedTracks = cms.bool(False),
    addJetCharge = cms.bool(False),
    addJetID = cms.bool(False),
    addGenPartonMatch = cms.bool(False),
    addGenJetMatch = cms.bool(False),
    getJetMCFlavour = cms.bool(False)
)

goodJets.userData.userFloats.src = cms.VInputTag("ak8GenJetsPrunedLinks",)

## Cleaning                                                                                                                                                                                                                          
# We want to make sure that the jets are not the electrons or muons done previously                                                                                                                                                   
import PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi as jetCleaner_cfi

cleanJets = jetCleaner_cfi.cleanPatJets.clone()
cleanJets.src = "goodJets"
cleanJets.checkOverlaps.muons.src = "goodMuons"
cleanJets.checkOverlaps.muons.deltaR = 0.8
cleanJets.checkOverlaps.muons.requireNoOverlaps = True
cleanJets.checkOverlaps.electrons.src = "goodElectrons"
cleanJets.checkOverlaps.electrons.deltaR = 0.8
cleanJets.checkOverlaps.electrons.requireNoOverlaps = True
cleanJets.checkOverlaps.photons = cms.PSet()
cleanJets.checkOverlaps.taus = cms.PSet()
cleanJets.checkOverlaps.tkIsoElectrons = cms.PSet()
cleanJets.finalCut = "pt > 20 & abs(eta) < 2.4"

jetsWithTau = cms.EDProducer("EDBRNJettinessAdder",
                             src = cms.InputTag("cleanJets"),
                             cone = cms.double(0.8)
                             )

fatJetsSequence = cms.Sequence(genParticlesForJets + ak8GenJetsPruned + ak8GenJetsPrunedLinks + goodJets + cleanJets + jetsWithTau)
