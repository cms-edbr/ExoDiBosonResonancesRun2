#!/bin/bash 
#
# Submit jobs to crab. Usage: 
#
#       cmsenv; source /cvmfs/cms.cern.ch/crab3/crab.sh; source submitAll.sh

crab submit Data.inputDataset='/SingleMuon/Run2015C_25ns-05Oct2015-v1/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2015D-05Oct2015-v1/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2015D-PromptReco-v4/MINIAOD'

# Switch to electron channel
sed -i '6 s/mu/el/' crabConfig.py

crab submit Data.inputDataset='/SingleElectron/Run2015C_25ns-05Oct2015-v1/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2015D-04Dec2015-v2/MINIAOD'

# Switch back to muon channel
sed -i '6 s/el/mu/' crabConfig.py
