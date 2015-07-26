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
#         3) Submission example to the 2 days queue 
#            bsub -q 2nd -J job1 < lxbatchSubmit.sh

export X509_USER_PROXY=/afs/cern.ch/user/j/jruizvar/x509up_u9472
cd /afs/cern.ch/work/j/jruizvar/private/Summer15/VZanalysis_backgrounds/CMSSW_7_4_7_patch2/src/ExoDiBosonResonances/EDBRTreeMaker/backgrounds
eval `scramv1 runtime -sh`
cmsRun analysis-DYJetsToLL_HT-100to200.py 

#cmsRun analysis-WW.py 
#cmsRun analysis-WZ.py 
#cmsRun analysis-ZZ.py 
