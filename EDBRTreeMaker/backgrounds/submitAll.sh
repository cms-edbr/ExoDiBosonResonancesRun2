#!/bin/bash 
#
# Submit jobs to crab. Usage: 
#
#       cmsenv; source /cvmfs/cms.cern.ch/crab3/crab.sh; source submitAll.sh

sed -i '6 s/TT/HT-100to200/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=3

sed -i '6 s/100to200/200to400/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/200to400/400to600/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=1

sed -i '6 s/400to600/600toInf/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=1

sed -i '6 s/HT-600toInf/WW/' crabConfig.py
crab submit Data.inputDataset='/WW_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/WW/WZ/' crabConfig.py
crab submit Data.inputDataset='/WZ_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/WZ/ZZ/' crabConfig.py
crab submit Data.inputDataset='/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/ZZ/TT/' crabConfig.py
crab submit Data.inputDataset='/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext3-v1/MINIAODSIM' Data.unitsPerJob=3

# Switch to electron channel
sed -i '6,12 s/mu/el/' crabConfig.py

sed -i '6 s/TT/HT-100to200/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=3

sed -i '6 s/100to200/200to400/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/200to400/400to600/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=1

sed -i '6 s/400to600/600toInf/' crabConfig.py
crab submit Data.inputDataset='/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=1

sed -i '6 s/HT-600toInf/WW/' crabConfig.py
crab submit Data.inputDataset='/WW_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/WW/WZ/' crabConfig.py
crab submit Data.inputDataset='/WZ_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/WZ/ZZ/' crabConfig.py
crab submit Data.inputDataset='/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM' Data.unitsPerJob=2

sed -i '6 s/ZZ/TT/' crabConfig.py
crab submit Data.inputDataset='/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv1-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext3-v1/MINIAODSIM' Data.unitsPerJob=3

# Switch back to muon channel
sed -i '6,12 s/el/mu/' crabConfig.py
