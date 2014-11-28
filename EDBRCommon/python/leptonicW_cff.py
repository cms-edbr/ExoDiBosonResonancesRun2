import FWCore.ParameterSet.Config as cms

#Wtomunu = cms.EDProducer("CandViewShallowCloneCombiner",
#                         decay = cms.string("goodMuons slimmedMETs"),
#                         checkCharge = cms.bool(False),
#                         cut = cms.string("mt > 50 & pt > 80")
#                         )

#Wtoenu = cms.EDProducer("CandViewCombiner",
#                        decay = cms.string("goodElectrons slimmedMETs"),
#                        checkCharge = cms.bool(False),
#                        cut = cms.string("mt > 50 & pt > 80")
#                        )

Wtomunu = cms.EDProducer("EDBRWLeptonicProducer",
                         leptons = cms.InputTag("goodMuons"),
                         MET = cms.InputTag("slimmedMETs"),
                         cut = cms.string("")
                         )


Wtoenu = cms.EDProducer("EDBRWLeptonicProducer",
                        leptons = cms.InputTag("goodElectrons"),
                        MET = cms.InputTag("slimmedMETs"),
                        cut = cms.string("")
                        )

leptonicV = cms.EDProducer("CandViewMerger",
                           src = cms.VInputTag( "Wtoenu", "Wtomunu"),
                           cut = cms.string("")
                           ) 

leptonicVSequence = cms.Sequence(Wtomunu + Wtoenu + leptonicV)
