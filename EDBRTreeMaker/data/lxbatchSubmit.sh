#!/bin/bash 
#
# Submit jobs to lxbatch. More info at https://twiki.cern.ch/twiki/bin/view/Main/BatchJobs
#
# Usage: 
#
#         1) Request a valid proxy
#            voms-proxy-init --voms cms -valid 168:00
#         
#         2) Copy proxy to your home
#            cp /tmp/x509up_u9472 $HOME
#
#         3) Submission example to the 1 day queue with a 10MB memory limit 
#            bsub -q 1nd -M 10000 -J job1 < lxbatchSubmit.sh

export X509_USER_PROXY=/afs/cern.ch/user/j/jruizvar/x509up_u9472
cd /afs/cern.ch/work/j/jruizvar/private/Summer15/50ns/CMSSW_7_4_10_patch1/src/ExoDiBosonResonances/EDBRTreeMaker/data

eval `scramv1 runtime -sh`

#cmsRun analysis-SingleElectron_Run2015B.py
cmsRun analysis-SingleMuon_Run2015B.py
