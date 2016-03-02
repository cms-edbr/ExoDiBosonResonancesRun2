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

for (( i=800; i<=4000; i+=100 ))
  do
    combine -M Asymptotic -d dataCards/CMS_ZZ_"$i"_ELP_13TeV.txt -m "$i" -n ELP
    combine -M Asymptotic -d dataCards/CMS_ZZ_"$i"_EHP_13TeV.txt -m "$i" -n EHP
    combine -M Asymptotic -d dataCards/CMS_ZZ_"$i"_MLP_13TeV.txt -m "$i" -n MLP
    combine -M Asymptotic -d dataCards/CMS_ZZ_"$i"_MHP_13TeV.txt -m "$i" -n MHP
    cd dataCards
    combineCards.py EHP=CMS_ZZ_"$i"_EHP_13TeV.txt ELP=CMS_ZZ_"$i"_ELP_13TeV.txt > CMS_ZZ_"$i"_ENP_13TeV.txt
    combineCards.py MHP=CMS_ZZ_"$i"_MHP_13TeV.txt MLP=CMS_ZZ_"$i"_MLP_13TeV.txt > CMS_ZZ_"$i"_MNP_13TeV.txt
    combineCards.py EHP=CMS_ZZ_"$i"_EHP_13TeV.txt ELP=CMS_ZZ_"$i"_ELP_13TeV.txt \
                    MHP=CMS_ZZ_"$i"_MHP_13TeV.txt MLP=CMS_ZZ_"$i"_MLP_13TeV.txt > CMS_ZZ_"$i"_ANP_13TeV.txt
    cd ..
    combine -M Asymptotic -d dataCards/CMS_ZZ_"$i"_ENP_13TeV.txt -m "$i" -n ENP
    combine -M Asymptotic -d dataCards/CMS_ZZ_"$i"_MNP_13TeV.txt -m "$i" -n MNP
    combine -M Asymptotic -d dataCards/CMS_ZZ_"$i"_ANP_13TeV.txt -m "$i" -n ANP
  done

hadd combineELP.root *ELP*mH?00.root *ELP*mH??00.root
hadd combineEHP.root *EHP*mH?00.root *EHP*mH??00.root
hadd combineENP.root *ENP*mH?00.root *ENP*mH??00.root
hadd combineMLP.root *MLP*mH?00.root *MLP*mH??00.root
hadd combineMHP.root *MHP*mH?00.root *MHP*mH??00.root
hadd combineMNP.root *MNP*mH?00.root *MNP*mH??00.root
hadd combineANP.root *ANP*mH?00.root *ANP*mH??00.root

# ROOT6
source /afs/cern.ch/sw/lcg/contrib/gcc/4.9/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.00/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh

root -b -q 'plotLimit.C("ELP")'
root -b -q 'plotLimit.C("EHP")'
root -b -q 'plotLimit.C("ENP")'
root -b -q 'plotLimit.C("MLP")'
root -b -q 'plotLimit.C("MHP")'
root -b -q 'plotLimit.C("MNP")'
root -b -q 'plotLimit.C("ANP")'

# remove useless files
#rm *.root
