#!/bin/bash 
#
# Submit SingleElectron jobs to lxbatch
#

sed -i '20 s/Run2015D-ai/Run2015D-aa/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEaa < submitJob.sh
sed -i '20 s/Run2015D-aa/Run2015D-ab/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEab < submitJob.sh
sed -i '20 s/Run2015D-ab/Run2015D-ac/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEac < submitJob.sh
sed -i '20 s/Run2015D-ac/Run2015D-ad/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEad < submitJob.sh
sed -i '20 s/Run2015D-ad/Run2015D-ae/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEae < submitJob.sh
sed -i '20 s/Run2015D-ae/Run2015D-af/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEaf < submitJob.sh
sed -i '20 s/Run2015D-af/Run2015D-ag/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEag < submitJob.sh
sed -i '20 s/Run2015D-ag/Run2015D-ah/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEah < submitJob.sh
sed -i '20 s/Run2015D-ah/Run2015D-ai/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleEai < submitJob.sh
