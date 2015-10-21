from CRABClient.UserUtilities import config
config = config()
    
config.JobType.pluginName      = 'Analysis'
config.JobType.psetName        = 'analysis-Diboson.py'
config.JobType.pyCfgParams     = ['','ZZ','mu']

config.Data.inputDataset  = '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM'
config.Data.unitsPerJob   = 5
config.Data.splitting     = 'FileBased'
config.Data.outLFNDirBase = '/store/user/jruizvar/mc/2015/EDBRtrees'

config.Site.storageSite = 'T2_BR_SPRACE'
