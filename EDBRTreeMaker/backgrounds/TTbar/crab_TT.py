from CRABClient.UserUtilities import config
config = config()
    
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-TT.py'
config.JobType.pyCfgParams = ['','el']

config.Data.inputDataset   = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM'
config.Data.unitsPerJob    = 4
config.Data.splitting      = 'FileBased'
config.Data.outLFNDirBase  = '/store/user/jruizvar/mc/2015/EDBRtrees/el'

config.Site.storageSite    = 'T2_BR_SPRACE'
