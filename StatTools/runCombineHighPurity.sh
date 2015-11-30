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

combine -M Asymptotic -d dataCards/CMS_ZZ_800_EHP_13TeV.txt  -m 800  -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1000_EHP_13TeV.txt -m 1000 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1200_EHP_13TeV.txt -m 1200 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1400_EHP_13TeV.txt -m 1400 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1600_EHP_13TeV.txt -m 1600 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1800_EHP_13TeV.txt -m 1800 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_2000_EHP_13TeV.txt -m 2000 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_2500_EHP_13TeV.txt -m 2500 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_3000_EHP_13TeV.txt -m 3000 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_3500_EHP_13TeV.txt -m 3500 -n EHP
combine -M Asymptotic -d dataCards/CMS_ZZ_4000_EHP_13TeV.txt -m 4000 -n EHP

hadd combineEHP.root *EHP*mH800.root *EHP*mH??00.root 
root -b -q 'plotLimit.C("EHP")'

combine -M Asymptotic -d dataCards/CMS_ZZ_800_MHP_13TeV.txt  -m 800  -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1000_MHP_13TeV.txt -m 1000 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1200_MHP_13TeV.txt -m 1200 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1400_MHP_13TeV.txt -m 1400 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1600_MHP_13TeV.txt -m 1600 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_1800_MHP_13TeV.txt -m 1800 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_2000_MHP_13TeV.txt -m 2000 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_2500_MHP_13TeV.txt -m 2500 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_3000_MHP_13TeV.txt -m 3000 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_3500_MHP_13TeV.txt -m 3500 -n MHP
combine -M Asymptotic -d dataCards/CMS_ZZ_4000_MHP_13TeV.txt -m 4000 -n MHP

hadd combineMHP.root *MHP*mH800.root *MHP*mH??00.root 
root -b -q 'plotLimit.C("MHP")'

cd dataCards
combineCards.py EHP=CMS_ZZ_800_EHP_13TeV.txt  MHP=CMS_ZZ_800_MHP_13TeV.txt  > CMS_ZZ_800_13TeV.txt
combineCards.py EHP=CMS_ZZ_1000_EHP_13TeV.txt MHP=CMS_ZZ_1000_MHP_13TeV.txt > CMS_ZZ_1000_13TeV.txt
combineCards.py EHP=CMS_ZZ_1200_EHP_13TeV.txt MHP=CMS_ZZ_1200_MHP_13TeV.txt > CMS_ZZ_1200_13TeV.txt
combineCards.py EHP=CMS_ZZ_1400_EHP_13TeV.txt MHP=CMS_ZZ_1400_MHP_13TeV.txt > CMS_ZZ_1400_13TeV.txt
combineCards.py EHP=CMS_ZZ_1600_EHP_13TeV.txt MHP=CMS_ZZ_1600_MHP_13TeV.txt > CMS_ZZ_1600_13TeV.txt
combineCards.py EHP=CMS_ZZ_1800_EHP_13TeV.txt MHP=CMS_ZZ_1800_MHP_13TeV.txt > CMS_ZZ_1800_13TeV.txt
combineCards.py EHP=CMS_ZZ_2000_EHP_13TeV.txt MHP=CMS_ZZ_2000_MHP_13TeV.txt > CMS_ZZ_2000_13TeV.txt
combineCards.py EHP=CMS_ZZ_2500_EHP_13TeV.txt MHP=CMS_ZZ_2500_MHP_13TeV.txt > CMS_ZZ_2500_13TeV.txt
combineCards.py EHP=CMS_ZZ_3000_EHP_13TeV.txt MHP=CMS_ZZ_3000_MHP_13TeV.txt > CMS_ZZ_3000_13TeV.txt
combineCards.py EHP=CMS_ZZ_3500_EHP_13TeV.txt MHP=CMS_ZZ_3500_MHP_13TeV.txt > CMS_ZZ_3500_13TeV.txt
combineCards.py EHP=CMS_ZZ_4000_EHP_13TeV.txt MHP=CMS_ZZ_4000_MHP_13TeV.txt > CMS_ZZ_4000_13TeV.txt
combineCards.py EHP=CMS_ZZ_4500_EHP_13TeV.txt MHP=CMS_ZZ_4500_MHP_13TeV.txt > CMS_ZZ_4500_13TeV.txt
cd ..

combine -M Asymptotic -d dataCards/CMS_ZZ_800_13TeV.txt  -m 800  -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_1000_13TeV.txt -m 1000 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_1200_13TeV.txt -m 1200 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_1400_13TeV.txt -m 1400 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_1600_13TeV.txt -m 1600 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_1800_13TeV.txt -m 1800 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_2000_13TeV.txt -m 2000 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_2500_13TeV.txt -m 2500 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_3000_13TeV.txt -m 3000 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_3500_13TeV.txt -m 3500 -n ALL
combine -M Asymptotic -d dataCards/CMS_ZZ_4000_13TeV.txt -m 4000 -n ALL

hadd combineALL.root *ALL*mH800.root *ALL*mH??00.root 
root -b -q 'plotLimit.C("ALL")'

# remove useless files
#rm roostats-*
#rm *.root
