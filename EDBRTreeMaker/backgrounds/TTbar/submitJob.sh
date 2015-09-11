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
#         3) Submission example to the 1 day queue with a 5MB memory limit 
#            bsub -q 1nd -M 5000 -J TTaw < submitJob.sh

export X509_USER_PROXY=/afs/cern.ch/user/j/jruizvar/x509up_u9472
cd /afs/cern.ch/work/j/jruizvar/private/Summer15/50ns/CMSSW_7_4_12/src/ExoDiBosonResonances/EDBRTreeMaker/backgrounds/TTbar
eval `scramv1 runtime -sh`

cmsRun analysis50ns-TT.py TTaw
