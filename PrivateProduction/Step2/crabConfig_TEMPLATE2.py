from CRABClient.client_utilities import getBasicConfig
config = getBasicConfig()

config.General.requestName = 'CRABREQUESTNAME_RAWSIM'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2.py'

config.Data.inputDataset = '/Technicolor/tomei-PARAMPUBLISH_GENSIM-e0d228ab1da7f5ff14c93b8b88050c93/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.outLFN = '/store/user/tomei' # or '/store/group/<subdir>'
config.Data.publication = True
config.Data.publishDataName = 'PARAMPUBLISH_RAWSIM'

config.JobType.allowNonProductionCMSSW = True 

config.Site.whitelist = ["T2_BR_SPRACE"]
config.Site.storageSite = 'T2_BR_SPRACE'
