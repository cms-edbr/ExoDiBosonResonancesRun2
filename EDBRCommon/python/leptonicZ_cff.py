import FWCore.ParameterSet.Config as cms

Ztomumu = cms.EDProducer(   "CandViewCombiner",
                            decay = cms.string("goodLeptons:Muons@+ goodLeptons:Muons@-"),
                            cut = cms.string("") )

Ztoee = cms.EDProducer(     "CandViewCombiner",
                            decay = cms.string("goodLeptons:Electrons@+ goodLeptons:Electrons@-"),
                            cut = cms.string("") )

leptonicV = cms.EDProducer( "CandViewMerger",
                            src = cms.VInputTag( "Ztoee", "Ztomumu"),
                            cut = cms.string("") )

leptonicVSequence = cms.Sequence(Ztomumu + Ztoee + leptonicV)
