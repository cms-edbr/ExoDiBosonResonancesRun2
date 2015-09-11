#!/bin/bash 
#
# Submit all TTbar jobs to lxbatch
#

sed -i '20 s/TTaw/TTaa/' submitJob.sh; bsub -q 1nd -M 5000 -J TTaa < submitJob.sh 
sed -i '20 s/TTaa/TTab/' submitJob.sh; bsub -q 1nd -M 5000 -J TTab < submitJob.sh
sed -i '20 s/TTab/TTac/' submitJob.sh; bsub -q 1nd -M 5000 -J TTac < submitJob.sh
sed -i '20 s/TTac/TTad/' submitJob.sh; bsub -q 1nd -M 5000 -J TTad < submitJob.sh
sed -i '20 s/TTad/TTae/' submitJob.sh; bsub -q 1nd -M 5000 -J TTae < submitJob.sh
sed -i '20 s/TTae/TTaf/' submitJob.sh; bsub -q 1nd -M 5000 -J TTaf < submitJob.sh
sed -i '20 s/TTaf/TTag/' submitJob.sh; bsub -q 1nd -M 5000 -J TTag < submitJob.sh
sed -i '20 s/TTag/TTah/' submitJob.sh; bsub -q 1nd -M 5000 -J TTah < submitJob.sh
sed -i '20 s/TTah/TTai/' submitJob.sh; bsub -q 1nd -M 5000 -J TTai < submitJob.sh
sed -i '20 s/TTai/TTaj/' submitJob.sh; bsub -q 1nd -M 5000 -J TTaj < submitJob.sh
sed -i '20 s/TTaj/TTak/' submitJob.sh; bsub -q 1nd -M 5000 -J TTak < submitJob.sh
sed -i '20 s/TTak/TTal/' submitJob.sh; bsub -q 1nd -M 5000 -J TTal < submitJob.sh
sed -i '20 s/TTal/TTam/' submitJob.sh; bsub -q 1nd -M 5000 -J TTam < submitJob.sh
sed -i '20 s/TTam/TTan/' submitJob.sh; bsub -q 1nd -M 5000 -J TTan < submitJob.sh
sed -i '20 s/TTan/TTao/' submitJob.sh; bsub -q 1nd -M 5000 -J TTao < submitJob.sh
sed -i '20 s/TTao/TTap/' submitJob.sh; bsub -q 1nd -M 5000 -J TTap < submitJob.sh
sed -i '20 s/TTap/TTaq/' submitJob.sh; bsub -q 1nd -M 5000 -J TTaq < submitJob.sh
sed -i '20 s/TTaq/TTar/' submitJob.sh; bsub -q 1nd -M 5000 -J TTar < submitJob.sh
sed -i '20 s/TTar/TTas/' submitJob.sh; bsub -q 1nd -M 5000 -J TTas < submitJob.sh
sed -i '20 s/TTas/TTat/' submitJob.sh; bsub -q 1nd -M 5000 -J TTat < submitJob.sh
sed -i '20 s/TTat/TTau/' submitJob.sh; bsub -q 1nd -M 5000 -J TTau < submitJob.sh
sed -i '20 s/TTau/TTav/' submitJob.sh; bsub -q 1nd -M 5000 -J TTav < submitJob.sh
sed -i '20 s/TTav/TTaw/' submitJob.sh; bsub -q 1nd -M 5000 -J TTaw < submitJob.sh
