#!/bin/bash 
#
# Submit all Diboson jobs to lxbatch
#

sed -i '20 s/ZZ-af/WW-aa/' submitJob.sh; bsub -q 8nh -M 5000 -J WWaa < submitJob.sh
sed -i '20 s/WW-aa/WW-ab/' submitJob.sh; bsub -q 8nh -M 5000 -J WWab < submitJob.sh
sed -i '20 s/WW-ab/WW-ac/' submitJob.sh; bsub -q 8nh -M 5000 -J WWac < submitJob.sh
sed -i '20 s/WW-ac/WW-ad/' submitJob.sh; bsub -q 8nh -M 5000 -J WWad < submitJob.sh
sed -i '20 s/WW-ad/WW-ae/' submitJob.sh; bsub -q 8nh -M 5000 -J WWae < submitJob.sh
sed -i '20 s/WW-ae/WW-af/' submitJob.sh; bsub -q 8nh -M 5000 -J WWaf < submitJob.sh
sed -i '20 s/WW-af/WZ-aa/' submitJob.sh; bsub -q 8nh -M 5000 -J WZaa < submitJob.sh
sed -i '20 s/WZ-aa/WZ-ab/' submitJob.sh; bsub -q 8nh -M 5000 -J WZab < submitJob.sh
sed -i '20 s/WZ-ab/WZ-ac/' submitJob.sh; bsub -q 8nh -M 5000 -J WZac < submitJob.sh
sed -i '20 s/WZ-ac/WZ-ad/' submitJob.sh; bsub -q 8nh -M 5000 -J WZad < submitJob.sh
sed -i '20 s/WZ-ad/WZ-ae/' submitJob.sh; bsub -q 8nh -M 5000 -J WZae < submitJob.sh
sed -i '20 s/WZ-ae/WZ-af/' submitJob.sh; bsub -q 8nh -M 5000 -J WZaf < submitJob.sh
sed -i '20 s/WZ-af/ZZ-aa/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZaa < submitJob.sh
sed -i '20 s/ZZ-aa/ZZ-ab/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZab < submitJob.sh
sed -i '20 s/ZZ-ab/ZZ-ac/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZac < submitJob.sh
sed -i '20 s/ZZ-ac/ZZ-ad/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZad < submitJob.sh
sed -i '20 s/ZZ-ad/ZZ-ae/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZae < submitJob.sh
sed -i '20 s/ZZ-ae/ZZ-af/' submitJob.sh; bsub -q 8nh -M 5000 -J ZZaf < submitJob.sh
