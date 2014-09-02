#!/bin/bash

### Usage ###
### source crabSubmit.sh ###

### Comment ###
### GRID pass phrase required after the first crab submit 

source /cvmfs/cms.cern.ch/crab3/crab.sh

crab submit -c crabConfig.py \
               General.requestName='HT-200to400' \
               Data.inputDataset='/DYJetsToLL_M-50_HT-200to400_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-PU20bx25_POSTLS170_V5-v1/MINIAODSIM' 

crab submit -c crabConfig.py \
               General.requestName='HT-400to600' \
               Data.inputDataset='/DYJetsToLL_M-50_HT-400to600_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-PU20bx25_POSTLS170_V5-v1/MINIAODSIM' 

crab submit -c crabConfig.py \
               General.requestName='HT-600toInf' \
               Data.inputDataset='/DYJetsToLL_M-50_HT-600toInf_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-PU20bx25_POSTLS170_V5-v1/MINIAODSIM' 
