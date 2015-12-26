from CRABClient.UserUtilities import config
config = config()

config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-background.py'
config.JobType.pyCfgParams = ['','TT','mu']
config.JobType.maxJobRuntimeMin = 120

config.Data.inputDataset   = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM'
config.Data.unitsPerJob    = 3
config.Data.splitting      = 'FileBased'
config.Data.outLFNDirBase  = '/store/user/jruizvar/mc/2015/EDBRtrees/mu'
config.Data.publication    = False

config.Site.storageSite    =  'T2_BR_SPRACE'
config.Site.whitelist      = ['T2_BR_SPRACE']
