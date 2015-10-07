import FWCore.ParameterSet.Config as cms

Ztoee = cms.EDProducer(           "CandViewCombiner",
                                   decay = cms.string("goodElectrons@+ goodElectrons@-"),
                                   cut = cms.string("") )

Ztomumu = cms.EDProducer(         "CandViewCombiner",
                                   decay = cms.string("goodMuons@+ goodMuons@-"),
                                   cut = cms.string("") )

leptonicV = cms.EDProducer(       "CandViewMerger",
                                   src = cms.VInputTag( "Ztoee", "Ztomumu"),
                                   cut = cms.string("") )

leptonicVFilter = cms.EDFilter(   "CandViewCountFilter",
                                   src = cms.InputTag("leptonicV"),
                                   minNumber = cms.uint32(1),
                                   filter = cms.bool(True) )

leptonicVSelector = cms.EDFilter( "CandViewSelector",
                                   src = cms.InputTag("leptonicV"),
                                   cut = cms.string( "pt > 200. & 70. < mass < 110."),
                                   filter = cms.bool(True) )

leptonicVSequence = cms.Sequence(  Ztoee             + 
                                   Ztomumu           + 
                                   leptonicV         + 
                                   leptonicVFilter   +  
                                   leptonicVSelector )
