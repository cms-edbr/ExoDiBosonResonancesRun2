import FWCore.ParameterSet.Config as cms



CUT = "abs(pdgId()) == 23  & (abs(daughter(0).pdgId())==12 || abs(daughter(0).pdgId())==14 || abs(daughter(0).pdgId())==16 ) & ( abs( daughter(1).pdgId() )==12 || abs( daughter(1).pdgId() )==14 || abs( daughter(1).pdgId() )==16 ) & mother(0).pdgId()==5100039"


METDecay = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("prunedGenParticles"),
    cut = cms.string(CUT),
    filter = cms.bool(True)
  )

