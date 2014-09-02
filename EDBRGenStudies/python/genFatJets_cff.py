import FWCore.ParameterSet.Config as cms

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

fatJetsSequence = cms.Sequence(goodJets + cleanJets + jetsWithTau)
