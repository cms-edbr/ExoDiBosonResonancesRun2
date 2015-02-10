from CRABClient.client_utilities import getBasicConfig
config = getBasicConfig()

config.General.requestName = 'CRABREQUESTNAME'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'PrivateMC'
config.JobType.generator = 'lhe'
config.JobType.psetName = 'CMSSWPYNAME'

config.Data.primaryDataset = 'Technicolor' # Put something descriptive here, like 'Technicolor' or 'BulkGraviton'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 200
NJOBS = 250  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFN = '/store/user/tomei' # or '/store/group/<subdir>' - but make sure to use your HN name
config.Data.publication = True
config.Data.publishDataName = 'PARAMPUBLISH'

config.JobType.allowNonProductionCMSSW = True 

# Your favourite T2 for production
config.Site.whitelist = ["T2_BR_SPRACE"]
config.Site.storageSite = 'T2_BR_SPRACE'
