import FWCore.ParameterSet.Config as cms

Ztoee = cms.EDProducer(           "CandViewCombiner",
                                   decay = cms.string("isoElectrons@+ isoElectrons@-"),
                                   cut = cms.string("(daughter(0).pt > 115 || daughter(1).pt > 115)"),
                                   #checkCharge = cms.bool(False)
                                  )

Ztomumu = cms.EDProducer(         "CandViewCombiner",
                                  decay = cms.string("isoMuons@+ isoMuons@-"),
                                  cut = cms.string("((daughter(0).userInt('isHighPt')==1 || daughter(1).userInt('isHighPt')==1)) && "+
                                                   "((daughter(0).pt > 50 & abs(daughter(0).eta) < 2.1) || (daughter(1).pt > 50 & abs(daughter(1).eta) < 2.1))"),
                                  #checkCharge = cms.bool(False)
                                  )

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
