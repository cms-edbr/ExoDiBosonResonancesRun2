from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'HT-Range' # Defined in crabSubmit.sh
config.General.workArea = 'DYJetsToLL_CrabArea'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'DYJetsToLL_Analysis.py'

config.section_("Data")
config.Data.inputDataset = 'MINIAODSIM' # Defined in crabSubmit.sh
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

config.section_("Site")
config.Site.storageSite = 'T2_BR_SPRACE'
