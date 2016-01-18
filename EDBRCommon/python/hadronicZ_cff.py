import FWCore.ParameterSet.Config as cms

corrJetsProducer = cms.EDProducer ( "CorrJetsProducer",
                                    jets    = cms.InputTag( "cleanJets"                ),
                                    vertex  = cms.InputTag( "goodOfflinePrimaryVertex" ), 
                                    rho     = cms.InputTag( "fixedGridRhoFastjetAll"   ),
                                    payload = cms.string  ( "AK8PFchs"                 ),
                                    isData  = cms.bool    (  False                     ))

nsubjettiness = cms.EDFilter(      "CandViewSelector",
                                    src = cms.InputTag("corrJetsProducer:corrJets"),
                                    cut = cms.string('(userFloat("NjettinessAK8:tau2")/userFloat("NjettinessAK8:tau1"))<0.75'),
                                    filter = cms.bool(True) )

hadronicV = cms.EDFilter(          "CandViewSelector",
                                    src = cms.InputTag("nsubjettiness"),
                                    cut = cms.string('abs(eta)<2.4'),
                                    filter = cms.bool(True) )

hadronicVSequence = cms.Sequence(   corrJetsProducer + 
                                    nsubjettiness    +
                                    hadronicV        )
