import FWCore.ParameterSet.Config as cms

daughterID      =  "(daughter(0).userInt('isHighPt')==1 || \
                     daughter(1).userInt('isHighPt')==1)"

daughterKin     =  "((daughter(0).pt > 50 & abs(daughter(0).eta) < 2.1) || \
                     (daughter(1).pt > 50 & abs(daughter(1).eta) < 2.1))"

daughterIso     =  "? deltaR(daughter(0).eta,daughter(0).phi,daughter(1).eta,daughter(1).phi)>0.3 ? \
                     daughter(0).userInt('passTrackIso') * daughter(1).userInt('passTrackIso') : \
                    (daughter(0).userFloat('trackIso')-daughter(1).userFloat('innerIso'))/daughter(0).pt < 0.2  & \
                    (daughter(1).userFloat('trackIso')-daughter(0).userFloat('innerIso'))/daughter(1).pt < 0.2  "

daughterCharge  =  "((daughter(0).charge == -daughter(1).charge) || \
                     (daughter(0).pdgId  == -daughter(1).pdgId))"

Ztoee = cms.EDProducer(           "CandViewCombiner",
                                   decay = cms.string("isoElectrons isoElectrons"),
                                   cut = cms.string("(daughter(0).pt > 115 || daughter(1).pt > 115)"),
                                   checkCharge = cms.bool(False) )

Ztomumu = cms.EDProducer(         "CandViewCombiner",
                                   decay = cms.string("isoMuons isoMuons"),
                                   cut = cms.string( daughterID +" & "+ daughterKin +" & "+ daughterIso),
                                   checkCharge = cms.bool(False) )

leptonicV = cms.EDProducer(       "CandViewMerger",
                                   src = cms.VInputTag( "Ztoee", "Ztomumu"),
                                   cut = cms.string("") )

leptonicVFilter = cms.EDFilter(   "CandViewCountFilter",
                                   src = cms.InputTag("leptonicV"),
                                   minNumber = cms.uint32(1),
                                   filter = cms.bool(True) )

ZdaughterCharge = cms.EDFilter(   "CandViewSelector",
                                   src = cms.InputTag("leptonicV"),
                                   cut = cms.string( daughterCharge ),
                                   filter = cms.bool(True) )

leptonicVSelector = cms.EDFilter( "CandViewSelector",
                                   src = cms.InputTag("ZdaughterCharge"),
                                   cut = cms.string( "pt > 170. & 70. < mass < 110."),
                                   filter = cms.bool(True) )

leptonicVSequence = cms.Sequence(  Ztoee             + 
                                   Ztomumu           + 
                                   leptonicV         + 
                                   leptonicVFilter   +
                                   ZdaughterCharge   +
                                   leptonicVSelector )
