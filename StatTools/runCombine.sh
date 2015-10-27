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

hadd combineENP.root *ENP*.root 
root -b -q 'plotLimit.C("ENP")'

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

hadd combineMNP.root *MNP*.root 
root -b -q 'plotLimit.C("MNP")'

cd dataCards
combineCards.py ENP=CMS_ZZ_1000_ENP_13TeV.txt MNP=CMS_ZZ_1000_MNP_13TeV.txt > CMS_ZZ_1000_13TeV.txt
combineCards.py ENP=CMS_ZZ_1200_ENP_13TeV.txt MNP=CMS_ZZ_1200_MNP_13TeV.txt > CMS_ZZ_1200_13TeV.txt
combineCards.py ENP=CMS_ZZ_1400_ENP_13TeV.txt MNP=CMS_ZZ_1400_MNP_13TeV.txt > CMS_ZZ_1400_13TeV.txt
combineCards.py ENP=CMS_ZZ_1600_ENP_13TeV.txt MNP=CMS_ZZ_1600_MNP_13TeV.txt > CMS_ZZ_1600_13TeV.txt
combineCards.py ENP=CMS_ZZ_1800_ENP_13TeV.txt MNP=CMS_ZZ_1800_MNP_13TeV.txt > CMS_ZZ_1800_13TeV.txt
combineCards.py ENP=CMS_ZZ_2000_ENP_13TeV.txt MNP=CMS_ZZ_2000_MNP_13TeV.txt > CMS_ZZ_2000_13TeV.txt
combineCards.py ENP=CMS_ZZ_2500_ENP_13TeV.txt MNP=CMS_ZZ_2500_MNP_13TeV.txt > CMS_ZZ_2500_13TeV.txt
combineCards.py ENP=CMS_ZZ_3000_ENP_13TeV.txt MNP=CMS_ZZ_3000_MNP_13TeV.txt > CMS_ZZ_3000_13TeV.txt
combineCards.py ENP=CMS_ZZ_3500_ENP_13TeV.txt MNP=CMS_ZZ_3500_MNP_13TeV.txt > CMS_ZZ_3500_13TeV.txt
combineCards.py ENP=CMS_ZZ_4000_ENP_13TeV.txt MNP=CMS_ZZ_4000_MNP_13TeV.txt > CMS_ZZ_4000_13TeV.txt
combineCards.py ENP=CMS_ZZ_4500_ENP_13TeV.txt MNP=CMS_ZZ_4500_MNP_13TeV.txt > CMS_ZZ_4500_13TeV.txt
cd ..

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

hadd combineALL.root *ALL*.root 
root -b -q 'plotLimit.C("ALL")'

# remove useless files
#rm roostats-*
#rm *.root
