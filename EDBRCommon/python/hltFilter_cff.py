import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt

hltFilter = hlt.triggerResultsFilter.clone(
                                  triggerConditions =      ( 'HLT_Ele105_CaloIdVT_GsfTrkIdT_v*', ),
                                  #triggerConditions =      ( 'HLT_Mu45_eta2p1_v*',             ),
                                  hltResults = cms.InputTag( "TriggerResults", "", "HLT"       ),
                                  l1tResults = cms.InputTag( "gtDigis"                         ),
                                  throw = False )

hltMatchingElectrons = cms.EDProducer("PatElectronHLTmatching",
                                  path       = cms.vstring ("HLT_Ele105_CaloIdVT_GsfTrkIdT_v*" ), 
                                  hltToken   = cms.InputTag("TriggerResults","","HLT"          ),
                                  hltObjects = cms.InputTag("selectedPatTrigger"               ),
                                  leptons    = cms.InputTag("slimmedElectrons"                 ),
                                  maxDeltaR  = cms.double  ( 0.3                               ))

hltMatchingMuons = cms.EDProducer("PatMuonHLTmatching",
                                  path       = cms.vstring ("HLT_Mu45_eta2p1_v*"               ),
                                  hltToken   = cms.InputTag("TriggerResults","","HLT"          ),
                                  hltObjects = cms.InputTag("selectedPatTrigger"               ),
                                  leptons    = cms.InputTag("slimmedMuons"                     ),
                                  maxDeltaR  = cms.double  ( 0.3                               ))

hltSequence = cms.Sequence(       hltFilter            + 
                                  hltMatchingElectrons +
                                  hltMatchingMuons     )
