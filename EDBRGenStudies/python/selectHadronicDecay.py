import FWCore.ParameterSet.Config as cms

hadronicDecay = cms.EDFilter("CandViewSelector",
                             src = cms.InputTag("prunedGenParticles"),
                             cut = cms.string("22 < abs(pdgId()) < 26            &&" + \
                                              " 0 < abs(daughter(0).pdgId()) < 6 &&" + \
                                              "mother(0).pdgId()==5100039"),
                             filter = cms.bool(True)
                            )
