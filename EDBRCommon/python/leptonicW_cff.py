import FWCore.ParameterSet.Config as cms

#Wtomunu = cms.EDProducer("CandViewShallowCloneCombiner",
#                         decay = cms.string("goodMuons genMetTrue"),
#                         checkCharge = cms.bool(False),
#                         cut = cms.string("mt > 50 & pt > 80")
#                         )

#Wtoenu = cms.EDProducer("CandViewCombiner",
#                        decay = cms.string("goodElectrons genMetTrue"),
#                        checkCharge = cms.bool(False),
#                        cut = cms.string("mt > 50 & pt > 80")
#                        )

Wtomunu = cms.EDProducer("EDBRWLeptonicProducer",
                         leptons = cms.InputTag("goodMuons"),
                         MET = cms.InputTag("genMetTrue"),
                         cut = cms.string("")
                         )


Wtoenu = cms.EDProducer("EDBRWLeptonicProducer",
                        leptons = cms.InputTag("goodElectrons"),
                        MET = cms.InputTag("genMetTrue"),
                        cut = cms.string("")
                        )

leptonicV = cms.EDProducer("CandViewMerger",
                           src = cms.VInputTag( "Wtoenu", "Wtomunu"),
                           cut = cms.string("")
                           ) 

leptonicVSequence = cms.Sequence(Wtomunu + Wtoenu + leptonicV)
