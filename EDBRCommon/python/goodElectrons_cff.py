import FWCore.ParameterSet.Config as cms

isolatedElectrons = cms.EDFilter("PATElectronSelector",
                             src = cms.InputTag("slimmedElectrons"),
                             cut = cms.string("(pfIsolationVariables().sumChargedHadronPt"                +\
                                              "    + max(0.0, pfIsolationVariables().sumNeutralHadronEt"  +\
                                              "              +pfIsolationVariables().sumPhotonEt"         +\
                                              "          -0.5*pfIsolationVariables().sumPUPt))/pt < 0.33" 
                                             )
                             )

goodElectrons = cms.EDFilter("PATElectronSelector",
                             src = cms.InputTag("isolatedElectrons"),
                             cut = cms.string("pt > 40 & abs(eta) < 2.5 & "+\
                                              "(abs(superCluster().position().eta()) < 1.442 || "+\
                                              "abs(superCluster().position().eta()) > 1.566)"  
                                             )
                             )

eleSequence = cms.Sequence(isolatedElectrons+goodElectrons)
