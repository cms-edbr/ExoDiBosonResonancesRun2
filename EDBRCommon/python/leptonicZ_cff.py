import FWCore.ParameterSet.Config as cms

Ztomumu = cms.EDProducer("CandViewCombiner",
                         decay = cms.string("goodMuons@+ goodMuons@-"),
                         cut = cms.string("70.0 < mass < 110.0 & pt > 80.0")
                         )

Ztoee = cms.EDProducer("CandViewCombiner",
                       decay = cms.string("goodElectrons@+ goodElectrons@-"),
                       cut = cms.string("70.0 < mass < 110.0 & pt > 80.0")
                       )

leptonicV = cms.EDProducer("CandViewMerger",
                           src = cms.VInputTag( "Ztoee", "Ztomumu"),
                           cut = cms.string("")
                           ) 

leptonicVSequence = cms.Sequence(Ztomumu + Ztoee + leptonicV)
