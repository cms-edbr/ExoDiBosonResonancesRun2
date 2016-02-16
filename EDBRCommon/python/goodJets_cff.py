import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetCorrFactorsUpdated
from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetsUpdated
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import cleanPatJets 
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

patJetCorrFactorsReapplyJEC = patJetCorrFactorsUpdated.clone(
                                    src     = cms.InputTag("slimmedJetsAK8"),
                                    levels  = ['L1FastJet','L2Relative','L3Absolute'],
                                    payload = 'AK8PFchs')

patJetsReapplyJEC = patJetsUpdated.clone(
                                    jetSource = cms.InputTag("slimmedJetsAK8"),
                                    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC") ))

goodJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                         filterParams = pfJetIDSelector.clone(),
                         src = cms.InputTag("patJetsReapplyJEC"),
                         filter = cms.bool(True) )

bestLeptonicVdaughters = cms.EDProducer("LeptonicVdaughters", src = cms.InputTag("bestLeptonicV"))

### Cleaning
cleanPatJets.src = "goodJets"
cleanPatJets.checkOverlaps.muons.src = "bestLeptonicVdaughters:Muons"
cleanPatJets.checkOverlaps.muons.deltaR = 0.8
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True
cleanPatJets.checkOverlaps.electrons.src = "bestLeptonicVdaughters:Electrons"
cleanPatJets.checkOverlaps.electrons.deltaR = 0.8
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True
cleanPatJets.checkOverlaps.photons = cms.PSet()
cleanPatJets.checkOverlaps.taus = cms.PSet()
cleanPatJets.checkOverlaps.tkIsoElectrons = cms.PSet()
cleanPatJets.finalCut = ""

# module to filter on the number of Jets
countCleanJets = cms.EDFilter("PATCandViewCountFilter",
                               minNumber = cms.uint32(1),
                               maxNumber = cms.uint32(999999),
                               src = cms.InputTag("cleanPatJets"))

fatJetsSequence = cms.Sequence( patJetCorrFactorsReapplyJEC +
                                patJetsReapplyJEC           +
                                goodJets                    +
                                bestLeptonicVdaughters      + 
                                cleanPatJets                + 
                                countCleanJets              )
