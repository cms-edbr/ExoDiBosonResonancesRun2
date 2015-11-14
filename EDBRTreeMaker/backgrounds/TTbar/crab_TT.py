from CRABClient.UserUtilities import config
config = config()
    
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-TT.py'
config.JobType.pyCfgParams = ['','mu']
config.JobType.maxJobRuntimeMin = 180

config.Data.inputDataset   = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM'
config.Data.unitsPerJob    = 3
config.Data.splitting      = 'FileBased'
config.Data.outLFNDirBase  = '/store/user/jruizvar/mc/2015/EDBRtrees/mu'

config.Site.storageSite    =  'T2_BR_SPRACE'
config.Site.blacklist      = ['T2_BR_SPRACE']
