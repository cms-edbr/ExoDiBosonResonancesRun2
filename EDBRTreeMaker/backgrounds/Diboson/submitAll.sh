#!/bin/bash 
#
# Submit all Diboson jobs to lxbatch
#

sed -i '20 s/ZZ-ac/WW-aa/' submitJob.sh; bsub -q 8nh -M 5000 -J WWaa < submitJob.sh
sed -i '20 s/WW-aa/WW-ab/' submitJob.sh; bsub -q 8nh -M 5000 -J WWab < submitJob.sh
sed -i '20 s/WW-ab/WW-ac/' submitJob.sh; bsub -q 8nh -M 5000 -J WWac < submitJob.sh
sed -i '20 s/WW-ac/WZ-aa/' submitJob.sh; bsub -q 8nh -M 5000 -J WZaa < submitJob.sh
sed -i '20 s/WZ-aa/WZ-ab/' submitJob.sh; bsub -q 8nh -M 5000 -J WZab < submitJob.sh
sed -i '20 s/WZ-ab/WZ-ac/' submitJob.sh; bsub -q 8nh -M 5000 -J WZac < submitJob.sh
sed -i '20 s/WZ-ac/ZZ-aa/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZaa < submitJob.sh
sed -i '20 s/ZZ-aa/ZZ-ab/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZab < submitJob.sh
sed -i '20 s/ZZ-ab/ZZ-ac/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZac < submitJob.sh
