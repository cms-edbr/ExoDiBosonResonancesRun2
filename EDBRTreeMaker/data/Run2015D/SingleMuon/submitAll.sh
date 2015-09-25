#!/bin/bash 
#
# Submit SingleMuon jobs to lxbatch
#

sed -i '20 s/Run2015D-af/Run2015D-aa/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMaa < submitJob.sh
sed -i '20 s/Run2015D-aa/Run2015D-ab/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMab < submitJob.sh
sed -i '20 s/Run2015D-ab/Run2015D-ac/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMac < submitJob.sh
sed -i '20 s/Run2015D-ac/Run2015D-ad/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMad < submitJob.sh
sed -i '20 s/Run2015D-ad/Run2015D-ae/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMae < submitJob.sh
sed -i '20 s/Run2015D-ae/Run2015D-af/' submitJob.sh; bsub -q 8nh -M 2000 -J SingleMaf < submitJob.sh
