from CRABClient.UserUtilities import config
config = config()

config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-background.py'
config.JobType.pyCfgParams = ['','TT','mu']
config.JobType.maxJobRuntimeMin = 120

config.Data.inputDataset   = '/TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'
config.Data.unitsPerJob    = 700 
config.Data.splitting      = 'LumiBased'
config.Data.outLFNDirBase  = '/store/user/jruizvar/mc/2015/EDBRtrees/mu'
config.Data.publication    = False

config.Site.storageSite    =  'T2_BR_SPRACE'
config.Site.whitelist      = ['T2_BR_SPRACE','T2_CH_CERN','T2_DE_DESY','T2_ES_CIEMAT','T2_FR_IPHC','T2_AT_Vienna','T2_IT_Legnaro','T2_IT_Pisa','T2_IT_Rome','T2_RU_IHEP']
