import FWCore.ParameterSet.Config as cms
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

goodJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                        filterParams = pfJetIDSelector.clone(),
                        src = cms.InputTag("slimmedJetsAK8"),
                        filter = cms.bool(True) )

### Cleaning
# We want to make sure that the jets are not the electrons or muons done previously

bestLeptonicVdaughters = cms.EDProducer("LeptonicVdaughters", src = cms.InputTag("bestLeptonicV"))

import PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi as jetCleaner_cfi

cleanJets = jetCleaner_cfi.cleanPatJets.clone()
cleanJets.src = "goodJets"
cleanJets.checkOverlaps.muons.src = "bestLeptonicVdaughters:Muons"
cleanJets.checkOverlaps.muons.deltaR = 0.8
cleanJets.checkOverlaps.muons.requireNoOverlaps = True
cleanJets.checkOverlaps.electrons.src = "bestLeptonicVdaughters:Electrons"
cleanJets.checkOverlaps.electrons.deltaR = 0.8
cleanJets.checkOverlaps.electrons.requireNoOverlaps = True
cleanJets.checkOverlaps.photons = cms.PSet()
cleanJets.checkOverlaps.taus = cms.PSet()
cleanJets.checkOverlaps.tkIsoElectrons = cms.PSet()
cleanJets.finalCut = "pt > 20 & abs(eta) < 2.4"

# module to filter on the number of Jets
countCleanJets = cms.EDFilter("PATCandViewCountFilter",
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(999999),
    src = cms.InputTag("cleanJets")
)

fatJetsSequence = cms.Sequence(bestLeptonicVdaughters + goodJets + cleanJets + countCleanJets)
