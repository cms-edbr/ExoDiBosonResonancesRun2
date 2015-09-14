#!/bin/bash 
#
# Submit all DY jobs to lxbatch
#

sed -i '20 s/600toInf-ac/100to200-aa/' submitJob.sh; bsub -q 8nh -M 2000 -J DY100aa < submitJob.sh
sed -i '20 s/100to200-aa/100to200-ab/' submitJob.sh; bsub -q 8nh -M 2000 -J DY100ab < submitJob.sh
sed -i '20 s/100to200-ab/100to200-ac/' submitJob.sh; bsub -q 8nh -M 2000 -J DY100ac < submitJob.sh
sed -i '20 s/100to200-ac/100to200-ad/' submitJob.sh; bsub -q 8nh -M 2000 -J DY100ad < submitJob.sh
sed -i '20 s/100to200-ad/100to200-ae/' submitJob.sh; bsub -q 8nh -M 2000 -J DY100ae < submitJob.sh
sed -i '20 s/100to200-ae/100to200-af/' submitJob.sh; bsub -q 8nh -M 2000 -J DY100af < submitJob.sh
sed -i '20 s/100to200-af/200to400-aa/' submitJob.sh; bsub -q 8nh -M 2000 -J DY200aa < submitJob.sh
sed -i '20 s/200to400-aa/200to400-ab/' submitJob.sh; bsub -q 8nh -M 2000 -J DY200ab < submitJob.sh
sed -i '20 s/200to400-ab/200to400-ac/' submitJob.sh; bsub -q 8nh -M 2000 -J DY200ac < submitJob.sh
sed -i '20 s/200to400-ac/400to600-aa/' submitJob.sh; bsub -q 8nh -M 2000 -J DY400aa < submitJob.sh
sed -i '20 s/400to600-aa/400to600-ab/' submitJob.sh; bsub -q 8nh -M 2000 -J DY400ab < submitJob.sh
sed -i '20 s/400to600-ab/400to600-ac/' submitJob.sh; bsub -q 8nh -M 2000 -J DY400ac < submitJob.sh
sed -i '20 s/400to600-ac/600toInf-aa/' submitJob.sh; bsub -q 8nh -M 2000 -J DY600aa < submitJob.sh
sed -i '20 s/600toInf-aa/600toInf-ab/' submitJob.sh; bsub -q 8nh -M 2000 -J DY600ab < submitJob.sh
sed -i '20 s/600toInf-ab/600toInf-ac/' submitJob.sh; bsub -q 8nh -M 2000 -J DY600ac < submitJob.sh
