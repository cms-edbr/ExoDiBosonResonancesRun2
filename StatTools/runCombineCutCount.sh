#!/bin/bash 
#
# Follow instrutions below to setup the Higgs Combine tool
#
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#SLC6_release
#
# This macro executes the Higgs Combine tool inside a valid working area
#
# The output trees are merged and analyzed by another macro "plotLimit.C" 

eval `scramv1 runtime -sh`

combine -M Asymptotic -d dataCards/MHP1000_card.txt -m 1000 -n MHP
combine -M Asymptotic -d dataCards/MHP1200_card.txt -m 1200 -n MHP
combine -M Asymptotic -d dataCards/MHP1400_card.txt -m 1400 -n MHP
combine -M Asymptotic -d dataCards/MHP1600_card.txt -m 1600 -n MHP
combine -M Asymptotic -d dataCards/MHP1800_card.txt -m 1800 -n MHP
combine -M Asymptotic -d dataCards/MHP2000_card.txt -m 2000 -n MHP
combine -M Asymptotic -d dataCards/MHP2500_card.txt -m 2500 -n MHP
combine -M Asymptotic -d dataCards/MHP3000_card.txt -m 3000 -n MHP
combine -M Asymptotic -d dataCards/MHP3500_card.txt -m 3500 -n MHP
combine -M Asymptotic -d dataCards/MHP4000_card.txt -m 4000 -n MHP

hadd combineMHP.root *.root   

# ROOT6
source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.03.04/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

root -b -q 'plotLimit.C("MHP")'

# remove useless files
rm roostats-*
rm *.root
