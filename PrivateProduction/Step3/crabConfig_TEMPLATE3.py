from CRABClient.client_utilities import getBasicConfig
config = getBasicConfig()

config.General.requestName = 'CRABREQUESTNAME_AODSIM'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step3.py'

config.Data.inputDataset = '/Technicolor/tomei-PARAMPUBLISH_RAWSIM-93287157e65f618f37e0483d88ad08d4/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.outLFN = '/store/user/tomei' # or '/store/group/<subdir>'
config.Data.publication = True
config.Data.publishDataName = 'PARAMPUBLISH_AODSIM'

config.JobType.allowNonProductionCMSSW = True 

config.Site.whitelist = ["T2_BR_SPRACE"]
config.Site.storageSite = 'T2_BR_SPRACE'
