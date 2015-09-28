import FWCore.ParameterSet.Config as cms

corrJetsProducer = cms.EDProducer ( "CorrJetsProducer",
                                    jets    = cms.InputTag( "cleanJets"                ),
                                    vertex  = cms.InputTag( "goodOfflinePrimaryVertex" ), 
                                    rho     = cms.InputTag( "fixedGridRhoFastjetAll"   ),
                                    payload = cms.string  ( "AK8PFchs"                 ),
                                    isData  = cms.bool    (  False                     ))

hadronicV = cms.EDFilter( "CandViewSelector",
                          src = cms.InputTag("corrJetsProducer:corrJets"),
                          cut = cms.string('userFloat("ak8PFJetsCHSCorrPrunedMass") > 20. & '
                                           'userFloat("ak8PFJetsCHSCorrPrunedMass") < 95.'),
                          filter = cms.bool(True) )

hadronicVSequence = cms.Sequence( corrJetsProducer + hadronicV )
