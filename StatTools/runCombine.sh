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

combine -M Asymptotic -d dataCards/CMS_ZZ_600_ELP_13TeV.txt  -m 600  -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_800_ELP_13TeV.txt  -m 800  -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_1000_ELP_13TeV.txt -m 1000 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_1200_ELP_13TeV.txt -m 1200 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_1400_ELP_13TeV.txt -m 1400 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_1600_ELP_13TeV.txt -m 1600 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_1800_ELP_13TeV.txt -m 1800 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_2000_ELP_13TeV.txt -m 2000 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_2500_ELP_13TeV.txt -m 2500 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_3000_ELP_13TeV.txt -m 3000 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_3500_ELP_13TeV.txt -m 3500 -n ELP
combine -M Asymptotic -d dataCards/CMS_ZZ_4000_ELP_13TeV.txt -m 4000 -n ELP

combine -M Asymptotic -d dataCards/CMS_ZZ_600_EHP_13TeV.txt  -m 600  -n EHP
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

combine -M Asymptotic -d dataCards/CMS_ZZ_600_MLP_13TeV.txt  -m 600  -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_800_MLP_13TeV.txt  -m 800  -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_1000_MLP_13TeV.txt -m 1000 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_1200_MLP_13TeV.txt -m 1200 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_1400_MLP_13TeV.txt -m 1400 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_1600_MLP_13TeV.txt -m 1600 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_1800_MLP_13TeV.txt -m 1800 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_2000_MLP_13TeV.txt -m 2000 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_2500_MLP_13TeV.txt -m 2500 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_3000_MLP_13TeV.txt -m 3000 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_3500_MLP_13TeV.txt -m 3500 -n MLP
combine -M Asymptotic -d dataCards/CMS_ZZ_4000_MLP_13TeV.txt -m 4000 -n MLP

combine -M Asymptotic -d dataCards/CMS_ZZ_600_MHP_13TeV.txt  -m 600  -n MHP
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

cd dataCards
combineCards.py EHP=CMS_ZZ_600_EHP_13TeV.txt  ELP=CMS_ZZ_600_ELP_13TeV.txt  > CMS_ZZ_600_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_800_EHP_13TeV.txt  ELP=CMS_ZZ_800_ELP_13TeV.txt  > CMS_ZZ_800_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_1000_EHP_13TeV.txt ELP=CMS_ZZ_1000_ELP_13TeV.txt > CMS_ZZ_1000_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_1200_EHP_13TeV.txt ELP=CMS_ZZ_1200_ELP_13TeV.txt > CMS_ZZ_1200_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_1400_EHP_13TeV.txt ELP=CMS_ZZ_1400_ELP_13TeV.txt > CMS_ZZ_1400_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_1600_EHP_13TeV.txt ELP=CMS_ZZ_1600_ELP_13TeV.txt > CMS_ZZ_1600_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_1800_EHP_13TeV.txt ELP=CMS_ZZ_1800_ELP_13TeV.txt > CMS_ZZ_1800_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_2000_EHP_13TeV.txt ELP=CMS_ZZ_2000_ELP_13TeV.txt > CMS_ZZ_2000_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_2500_EHP_13TeV.txt ELP=CMS_ZZ_2500_ELP_13TeV.txt > CMS_ZZ_2500_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_3000_EHP_13TeV.txt ELP=CMS_ZZ_3000_ELP_13TeV.txt > CMS_ZZ_3000_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_3500_EHP_13TeV.txt ELP=CMS_ZZ_3500_ELP_13TeV.txt > CMS_ZZ_3500_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_4000_EHP_13TeV.txt ELP=CMS_ZZ_4000_ELP_13TeV.txt > CMS_ZZ_4000_ENP_13TeV.txt
combineCards.py EHP=CMS_ZZ_4500_EHP_13TeV.txt ELP=CMS_ZZ_4500_ELP_13TeV.txt > CMS_ZZ_4500_ENP_13TeV.txt

combineCards.py MHP=CMS_ZZ_600_MHP_13TeV.txt  MLP=CMS_ZZ_600_MLP_13TeV.txt  > CMS_ZZ_600_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_800_MHP_13TeV.txt  MLP=CMS_ZZ_800_MLP_13TeV.txt  > CMS_ZZ_800_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_1000_MHP_13TeV.txt MLP=CMS_ZZ_1000_MLP_13TeV.txt > CMS_ZZ_1000_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_1200_MHP_13TeV.txt MLP=CMS_ZZ_1200_MLP_13TeV.txt > CMS_ZZ_1200_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_1400_MHP_13TeV.txt MLP=CMS_ZZ_1400_MLP_13TeV.txt > CMS_ZZ_1400_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_1600_MHP_13TeV.txt MLP=CMS_ZZ_1600_MLP_13TeV.txt > CMS_ZZ_1600_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_1800_MHP_13TeV.txt MLP=CMS_ZZ_1800_MLP_13TeV.txt > CMS_ZZ_1800_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_2000_MHP_13TeV.txt MLP=CMS_ZZ_2000_MLP_13TeV.txt > CMS_ZZ_2000_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_2500_MHP_13TeV.txt MLP=CMS_ZZ_2500_MLP_13TeV.txt > CMS_ZZ_2500_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_3000_MHP_13TeV.txt MLP=CMS_ZZ_3000_MLP_13TeV.txt > CMS_ZZ_3000_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_3500_MHP_13TeV.txt MLP=CMS_ZZ_3500_MLP_13TeV.txt > CMS_ZZ_3500_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_4000_MHP_13TeV.txt MLP=CMS_ZZ_4000_MLP_13TeV.txt > CMS_ZZ_4000_MNP_13TeV.txt
combineCards.py MHP=CMS_ZZ_4500_MHP_13TeV.txt MLP=CMS_ZZ_4500_MLP_13TeV.txt > CMS_ZZ_4500_MNP_13TeV.txt
cd ..

combine -M Asymptotic -d dataCards/CMS_ZZ_600_ENP_13TeV.txt  -m 600  -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_800_ENP_13TeV.txt  -m 800  -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_1000_ENP_13TeV.txt -m 1000 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_1200_ENP_13TeV.txt -m 1200 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_1400_ENP_13TeV.txt -m 1400 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_1600_ENP_13TeV.txt -m 1600 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_1800_ENP_13TeV.txt -m 1800 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_2000_ENP_13TeV.txt -m 2000 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_2500_ENP_13TeV.txt -m 2500 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_3000_ENP_13TeV.txt -m 3000 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_3500_ENP_13TeV.txt -m 3500 -n ENP
combine -M Asymptotic -d dataCards/CMS_ZZ_4000_ENP_13TeV.txt -m 4000 -n ENP

combine -M Asymptotic -d dataCards/CMS_ZZ_600_MNP_13TeV.txt  -m 600  -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_800_MNP_13TeV.txt  -m 800  -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_1000_MNP_13TeV.txt -m 1000 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_1200_MNP_13TeV.txt -m 1200 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_1400_MNP_13TeV.txt -m 1400 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_1600_MNP_13TeV.txt -m 1600 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_1800_MNP_13TeV.txt -m 1800 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_2000_MNP_13TeV.txt -m 2000 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_2500_MNP_13TeV.txt -m 2500 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_3000_MNP_13TeV.txt -m 3000 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_3500_MNP_13TeV.txt -m 3500 -n MNP
combine -M Asymptotic -d dataCards/CMS_ZZ_4000_MNP_13TeV.txt -m 4000 -n MNP

hadd combineELP.root *ELP*mH?00.root *ELP*mH??00.root 
hadd combineEHP.root *EHP*mH?00.root *EHP*mH??00.root 
hadd combineMLP.root *MLP*mH?00.root *MLP*mH??00.root 
hadd combineMHP.root *MHP*mH?00.root *MHP*mH??00.root 
hadd combineENP.root *ENP*mH?00.root *ENP*mH??00.root 
hadd combineMNP.root *MNP*mH?00.root *MNP*mH??00.root 

root -b -q 'plotLimit.C("ELP")'
root -b -q 'plotLimit.C("EHP")'
root -b -q 'plotLimit.C("MLP")'
root -b -q 'plotLimit.C("MHP")'
root -b -q 'plotLimit.C("ENP")'
root -b -q 'plotLimit.C("MNP")'

# remove useless files
#rm roostats-*
#rm *.root
