#!/bin/bash 
#
# Run analyzer over BulkG samples

sed -i '20 s/600/800/'   submitJob.sh; bsub -q 1nh -M 2000 -J M800mu < submitJob.sh
sed -i '20 s/800/1000/'  submitJob.sh; bsub -q 1nh -M 2000 -J M1000mu < submitJob.sh
sed -i '20 s/1000/1200/' submitJob.sh; bsub -q 1nh -M 2000 -J M1200mu < submitJob.sh
sed -i '20 s/1200/1400/' submitJob.sh; bsub -q 1nh -M 2000 -J M1400mu < submitJob.sh
sed -i '20 s/1400/1600/' submitJob.sh; bsub -q 1nh -M 2000 -J M1600mu < submitJob.sh
sed -i '20 s/1600/1800/' submitJob.sh; bsub -q 1nh -M 2000 -J M1800mu < submitJob.sh
sed -i '20 s/1800/2000/' submitJob.sh; bsub -q 1nh -M 2000 -J M2000mu < submitJob.sh
sed -i '20 s/2000/2500/' submitJob.sh; bsub -q 1nh -M 2000 -J M2500mu < submitJob.sh
sed -i '20 s/2500/3000/' submitJob.sh; bsub -q 1nh -M 2000 -J M3000mu < submitJob.sh
sed -i '20 s/3000/3500/' submitJob.sh; bsub -q 1nh -M 2000 -J M3500mu < submitJob.sh
sed -i '20 s/3500/4000/' submitJob.sh; bsub -q 1nh -M 2000 -J M4000mu < submitJob.sh
sed -i '20 s/4000/4500/' submitJob.sh; bsub -q 1nh -M 2000 -J M4500mu < submitJob.sh
sed -i '20 s/4500/600/'  submitJob.sh; bsub -q 1nh -M 2000 -J  M600mu < submitJob.sh

sed -i '20 s/mu/el/' submitJob.sh

sed -i '20 s/600/800/'   submitJob.sh; bsub -q 1nh -M 2000 -J M800el  < submitJob.sh
sed -i '20 s/800/1000/'  submitJob.sh; bsub -q 1nh -M 2000 -J M1000el < submitJob.sh
sed -i '20 s/1000/1200/' submitJob.sh; bsub -q 1nh -M 2000 -J M1200el < submitJob.sh
sed -i '20 s/1200/1400/' submitJob.sh; bsub -q 1nh -M 2000 -J M1400el < submitJob.sh
sed -i '20 s/1400/1600/' submitJob.sh; bsub -q 1nh -M 2000 -J M1600el < submitJob.sh
sed -i '20 s/1600/1800/' submitJob.sh; bsub -q 1nh -M 2000 -J M1800el < submitJob.sh
sed -i '20 s/1800/2000/' submitJob.sh; bsub -q 1nh -M 2000 -J M2000el < submitJob.sh
sed -i '20 s/2000/2500/' submitJob.sh; bsub -q 1nh -M 2000 -J M2500el < submitJob.sh
sed -i '20 s/2500/3000/' submitJob.sh; bsub -q 1nh -M 2000 -J M3000el < submitJob.sh
sed -i '20 s/3000/3500/' submitJob.sh; bsub -q 1nh -M 2000 -J M3500el < submitJob.sh
sed -i '20 s/3500/4000/' submitJob.sh; bsub -q 1nh -M 2000 -J M4000el < submitJob.sh
sed -i '20 s/4000/4500/' submitJob.sh; bsub -q 1nh -M 2000 -J M4500el < submitJob.sh
sed -i '20 s/4500/600/'  submitJob.sh; bsub -q 1nh -M 2000 -J  M600el < submitJob.sh

sed -i '20 s/el/mu/' submitJob.sh
