import FWCore.ParameterSet.Config as cms

trigReport = cms.EDAnalyzer("TrigReportData",
                            trigResult = cms.InputTag("TriggerResults::TEST")
                           )

trigReportData = cms.Sequence(trigReport)
