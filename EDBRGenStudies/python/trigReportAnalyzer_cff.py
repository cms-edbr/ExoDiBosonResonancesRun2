import FWCore.ParameterSet.Config as cms

trigReport = cms.EDAnalyzer( "TrigReportAnalyzer",
                             trigResult = cms.InputTag("TriggerResults::TEST"),
                             leptonicZ  = cms.InputTag( "leptonicDecay","","TEST"), 
                             hadronicZ  = cms.InputTag( "hadronicDecay","","TEST") 
                           )

trigReportAnalyzer = cms.Sequence(trigReport)
