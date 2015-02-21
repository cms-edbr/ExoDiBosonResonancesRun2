#!/bin/bash 
#
# Follow instrutions below to setup the Higgs Combine tool
#
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#SLC6_release
#
# This macro executes the Higgs Combine tool inside a valid working area
#
# The output trees are merged and analyzed by another macro "plotLimit.C" 

combine -M Asymptotic -d dataCards/EHP1000_shape_card.txt -m 1000 -n EHP
combine -M Asymptotic -d dataCards/EHP2000_shape_card.txt -m 2000 -n EHP
combine -M Asymptotic -d dataCards/EHP3000_shape_card.txt -m 3000 -n EHP
combine -M Asymptotic -d dataCards/EHP4000_shape_card.txt -m 4000 -n EHP
hadd combineEHP.root higgsCombineEHP.Asymptotic.mH1000.root higgsCombineEHP.Asymptotic.mH2000.root higgsCombineEHP.Asymptotic.mH3000.root higgsCombineEHP.Asymptotic.mH4000.root
 
combine -M Asymptotic -d dataCards/ELP1000_shape_card.txt -m 1000 -n ELP
combine -M Asymptotic -d dataCards/ELP2000_shape_card.txt -m 2000 -n ELP
combine -M Asymptotic -d dataCards/ELP3000_shape_card.txt -m 3000 -n ELP
combine -M Asymptotic -d dataCards/ELP4000_shape_card.txt -m 4000 -n ELP
hadd combineELP.root higgsCombineELP.Asymptotic.mH1000.root higgsCombineELP.Asymptotic.mH2000.root higgsCombineELP.Asymptotic.mH3000.root higgsCombineELP.Asymptotic.mH4000.root 

combine -M Asymptotic -d dataCards/MHP1000_shape_card.txt -m 1000 -n MHP
combine -M Asymptotic -d dataCards/MHP2000_shape_card.txt -m 2000 -n MHP
combine -M Asymptotic -d dataCards/MHP3000_shape_card.txt -m 3000 -n MHP
combine -M Asymptotic -d dataCards/MHP4000_shape_card.txt -m 4000 -n MHP
hadd combineMHP.root higgsCombineMHP.Asymptotic.mH1000.root higgsCombineMHP.Asymptotic.mH2000.root higgsCombineMHP.Asymptotic.mH3000.root higgsCombineMHP.Asymptotic.mH4000.root
 
combine -M Asymptotic -d dataCards/MLP1000_shape_card.txt -m 1000 -n MLP
combine -M Asymptotic -d dataCards/MLP2000_shape_card.txt -m 2000 -n MLP
combine -M Asymptotic -d dataCards/MLP3000_shape_card.txt -m 3000 -n MLP
combine -M Asymptotic -d dataCards/MLP4000_shape_card.txt -m 4000 -n MLP
hadd combineMLP.root higgsCombineMLP.Asymptotic.mH1000.root higgsCombineMLP.Asymptotic.mH2000.root higgsCombineMLP.Asymptotic.mH3000.root higgsCombineMLP.Asymptotic.mH4000.root 

# ROOT6
source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.03.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

root -b -q 'plotLimit.C("EHP")'
root -b -q 'plotLimit.C("ELP")'
root -b -q 'plotLimit.C("MHP")'
root -b -q 'plotLimit.C("MLP")'

# remove useless files
rm roostats-*
rm *000.root


