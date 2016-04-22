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
#         3) Submission example to the 1 hour queue with 2 MB memory limit
#            bsub -q 1nh -M 2000 -J Bulk800mu < submitJob.sh

export X509_USER_PROXY=/afs/cern.ch/user/j/jruizvar/x509up_u9472
cd /afs/cern.ch/work/j/jruizvar/private/Spring16/CMSSW_7_6_5/src/ExoDiBosonResonances/EDBRTreeMaker/signals
eval `scramv1 runtime -sh`

cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-800 mu
