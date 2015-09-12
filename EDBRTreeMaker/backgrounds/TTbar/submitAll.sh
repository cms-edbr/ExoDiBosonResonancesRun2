#!/bin/bash 
#
# Submit all TTbar jobs to lxbatch
#

sed -i '20 s/TT-bg/TT-aa/' submitJob.sh; bsub -q 8hn -M 5000 -J TTaa < submitJob.sh 
sed -i '20 s/TT-aa/TT-ab/' submitJob.sh; bsub -q 8hn -M 5000 -J TTab < submitJob.sh
sed -i '20 s/TT-ab/TT-ac/' submitJob.sh; bsub -q 8hn -M 5000 -J TTac < submitJob.sh
sed -i '20 s/TT-ac/TT-ad/' submitJob.sh; bsub -q 8hn -M 5000 -J TTad < submitJob.sh
sed -i '20 s/TT-ad/TT-ae/' submitJob.sh; bsub -q 8hn -M 5000 -J TTae < submitJob.sh
sed -i '20 s/TT-ae/TT-af/' submitJob.sh; bsub -q 8hn -M 5000 -J TTaf < submitJob.sh
sed -i '20 s/TT-af/TT-ag/' submitJob.sh; bsub -q 8hn -M 5000 -J TTag < submitJob.sh
sed -i '20 s/TT-ag/TT-ah/' submitJob.sh; bsub -q 8hn -M 5000 -J TTah < submitJob.sh
sed -i '20 s/TT-ah/TT-ai/' submitJob.sh; bsub -q 8hn -M 5000 -J TTai < submitJob.sh
sed -i '20 s/TT-ai/TT-aj/' submitJob.sh; bsub -q 8hn -M 5000 -J TTaj < submitJob.sh
sed -i '20 s/TT-aj/TT-ak/' submitJob.sh; bsub -q 8hn -M 5000 -J TTak < submitJob.sh
sed -i '20 s/TT-ak/TT-al/' submitJob.sh; bsub -q 8hn -M 5000 -J TTal < submitJob.sh
sed -i '20 s/TT-al/TT-am/' submitJob.sh; bsub -q 8hn -M 5000 -J TTam < submitJob.sh
sed -i '20 s/TT-am/TT-an/' submitJob.sh; bsub -q 8hn -M 5000 -J TTan < submitJob.sh
sed -i '20 s/TT-an/TT-ao/' submitJob.sh; bsub -q 8hn -M 5000 -J TTao < submitJob.sh
sed -i '20 s/TT-ao/TT-ap/' submitJob.sh; bsub -q 8hn -M 5000 -J TTap < submitJob.sh
sed -i '20 s/TT-ap/TT-aq/' submitJob.sh; bsub -q 8hn -M 5000 -J TTaq < submitJob.sh
sed -i '20 s/TT-aq/TT-ar/' submitJob.sh; bsub -q 8hn -M 5000 -J TTar < submitJob.sh
sed -i '20 s/TT-ar/TT-as/' submitJob.sh; bsub -q 8hn -M 5000 -J TTas < submitJob.sh
sed -i '20 s/TT-as/TT-at/' submitJob.sh; bsub -q 8hn -M 5000 -J TTat < submitJob.sh
sed -i '20 s/TT-at/TT-au/' submitJob.sh; bsub -q 8hn -M 5000 -J TTau < submitJob.sh
sed -i '20 s/TT-au/TT-av/' submitJob.sh; bsub -q 8hn -M 5000 -J TTav < submitJob.sh
sed -i '20 s/TT-av/TT-aw/' submitJob.sh; bsub -q 8hn -M 5000 -J TTaw < submitJob.sh
sed -i '20 s/TT-aw/TT-ax/' submitJob.sh; bsub -q 8hn -M 5000 -J TTax < submitJob.sh
sed -i '20 s/TT-ax/TT-ay/' submitJob.sh; bsub -q 8hn -M 5000 -J TTay < submitJob.sh
sed -i '20 s/TT-ay/TT-az/' submitJob.sh; bsub -q 8hn -M 5000 -J TTaz < submitJob.sh
sed -i '20 s/TT-az/TT-ba/' submitJob.sh; bsub -q 8hn -M 5000 -J TTba < submitJob.sh
sed -i '20 s/TT-ba/TT-bb/' submitJob.sh; bsub -q 8hn -M 5000 -J TTbb < submitJob.sh
sed -i '20 s/TT-bb/TT-bc/' submitJob.sh; bsub -q 8hn -M 5000 -J TTbc < submitJob.sh
sed -i '20 s/TT-bc/TT-bd/' submitJob.sh; bsub -q 8hn -M 5000 -J TTbd < submitJob.sh
sed -i '20 s/TT-bd/TT-be/' submitJob.sh; bsub -q 8hn -M 5000 -J TTbe < submitJob.sh
sed -i '20 s/TT-be/TT-bf/' submitJob.sh; bsub -q 8hn -M 5000 -J TTbf < submitJob.sh
sed -i '20 s/TT-bf/TT-bg/' submitJob.sh; bsub -q 8hn -M 5000 -J TTbg < submitJob.sh
