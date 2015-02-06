#!/bin/bash 
#
# Follow instrutions below to setup the Higgs Combine tool
#
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#SLC6_release
#
# This macro executes the Higgs Combine tool inside a valid working area
#
# The output trees are merged and analyzed by another macro "plotLimit.C" 

combine -M Asymptotic -d dataCards/ehp1000_card.txt -m 1000 -n EHP
combine -M Asymptotic -d dataCards/ehp2000_card.txt -m 2000 -n EHP
combine -M Asymptotic -d dataCards/ehp3000_card.txt -m 3000 -n EHP
combine -M Asymptotic -d dataCards/ehp4000_card.txt -m 4000 -n EHP
hadd combineEHP.root higgsCombineEHP.Asymptotic.mH1000.root higgsCombineEHP.Asymptotic.mH2000.root higgsCombineEHP.Asymptotic.mH3000.root higgsCombineEHP.Asymptotic.mH4000.root
 
combine -M Asymptotic -d dataCards/elp1000_card.txt -m 1000 -n ELP
combine -M Asymptotic -d dataCards/elp2000_card.txt -m 2000 -n ELP
combine -M Asymptotic -d dataCards/elp3000_card.txt -m 3000 -n ELP
combine -M Asymptotic -d dataCards/elp4000_card.txt -m 4000 -n ELP
hadd combineELP.root higgsCombineELP.Asymptotic.mH1000.root higgsCombineELP.Asymptotic.mH2000.root higgsCombineELP.Asymptotic.mH3000.root higgsCombineELP.Asymptotic.mH4000.root 

combine -M Asymptotic -d dataCards/mhp1000_card.txt -m 1000 -n MHP
combine -M Asymptotic -d dataCards/mhp2000_card.txt -m 2000 -n MHP
combine -M Asymptotic -d dataCards/mhp3000_card.txt -m 3000 -n MHP
combine -M Asymptotic -d dataCards/mhp4000_card.txt -m 4000 -n MHP
hadd combineMHP.root higgsCombineMHP.Asymptotic.mH1000.root higgsCombineMHP.Asymptotic.mH2000.root higgsCombineMHP.Asymptotic.mH3000.root higgsCombineMHP.Asymptotic.mH4000.root
 
combine -M Asymptotic -d dataCards/mlp1000_card.txt -m 1000 -n MLP
combine -M Asymptotic -d dataCards/mlp2000_card.txt -m 2000 -n MLP
combine -M Asymptotic -d dataCards/mlp3000_card.txt -m 3000 -n MLP
combine -M Asymptotic -d dataCards/mlp4000_card.txt -m 4000 -n MLP
hadd combineMLP.root higgsCombineMLP.Asymptotic.mH1000.root higgsCombineMLP.Asymptotic.mH2000.root higgsCombineMLP.Asymptotic.mH3000.root higgsCombineMLP.Asymptotic.mH4000.root 

rm roostats-*

root -b -q 'plotLimit.C("EHP")'
root -b -q 'plotLimit.C("ELP")'
root -b -q 'plotLimit.C("MHP")'
root -b -q 'plotLimit.C("MLP")'
