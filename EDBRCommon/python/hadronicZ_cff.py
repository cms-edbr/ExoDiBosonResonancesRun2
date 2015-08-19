import FWCore.ParameterSet.Config as cms

hadronicV = cms.EDFilter( "CandViewSelector",
                          src = cms.InputTag("cleanJets"),
                          cut = cms.string('pt > 200. '
                                           '& (userFloat("ak8PFJetsCHSSoftDropMass") > 50.) '
                                           '& (userFloat("ak8PFJetsCHSSoftDropMass") < 110.)'),
                          filter = cms.bool(True) )

hadronicVSequence = cms.Sequence(hadronicV)
