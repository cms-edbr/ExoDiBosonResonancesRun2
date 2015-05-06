import FWCore.ParameterSet.Config as cms

leptonicDecay = cms.EDFilter("CandViewSelector",
                             src = cms.InputTag("prunedGenParticles"),
                             cut = cms.string("22 < abs(pdgId()) < 26                                        &&" + \
                                              "(abs(daughter(0).pdgId())==11||abs(daughter(1).pdgId())==11||"    + \
                                              " abs(daughter(0).pdgId())==13||abs(daughter(1).pdgId())==13 ) &&" + \
                                              "mother(0).pdgId()==5100039"),
                             filter = cms.bool(True)
                            )
