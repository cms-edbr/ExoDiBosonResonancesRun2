from CRABClient.UserUtilities import config
config = config()
    
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-data.py'
config.JobType.pyCfgParams = ['','mu']
config.JobType.maxJobRuntimeMin = 180

config.Data.inputDataset   = '/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD'
config.Data.unitsPerJob    = 150
config.Data.splitting      = 'LumiBased'
config.Data.lumiMask       = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_Silver_v2.txt"
config.Data.outLFNDirBase  = '/store/user/jruizvar/data/2015/EDBRtrees'
config.Data.publication    = False
config.Data.allowNonValidInputDataset = True

config.Site.storageSite    =  'T2_BR_SPRACE'
