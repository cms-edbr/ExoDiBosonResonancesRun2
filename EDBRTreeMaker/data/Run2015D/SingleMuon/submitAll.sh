#!/bin/bash 
#
# Submit SingleMuon jobs to lxbatch
#

sed -i '20 s/Run2015D-aj/Run2015D-aa/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMaa < submitJob.sh
sed -i '20 s/Run2015D-aa/Run2015D-ab/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMab < submitJob.sh
sed -i '20 s/Run2015D-ab/Run2015D-ac/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMac < submitJob.sh
sed -i '20 s/Run2015D-ac/Run2015D-ad/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMad < submitJob.sh
sed -i '20 s/Run2015D-ad/Run2015D-ae/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMae < submitJob.sh
sed -i '20 s/Run2015D-ae/Run2015D-af/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMaf < submitJob.sh
sed -i '20 s/Run2015D-af/Run2015D-ag/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMag < submitJob.sh
sed -i '20 s/Run2015D-ag/Run2015D-ah/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMah < submitJob.sh
sed -i '20 s/Run2015D-ah/Run2015D-ai/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMai < submitJob.sh
sed -i '20 s/Run2015D-ai/Run2015D-aj/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMaj < submitJob.sh
