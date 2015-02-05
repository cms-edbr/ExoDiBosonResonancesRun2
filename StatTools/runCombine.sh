#!/bin/bash 
#
# Follow instrutions below to setup the Higgs Combine tool
#
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#SLC6_release
#
# This macro executes the Higgs Combine tool inside a valid working area
#
# The output trees are merge into a single tree named CombineEHP.root
#
# Another macro (plotLimit.C) reads this tree 

combine -M Asymptotic -d ehp1000_card.txt -m 1000 -n Ehp
combine -M Asymptotic -d ehp2000_card.txt -m 2000 -n Ehp
combine -M Asymptotic -d ehp3000_card.txt -m 3000 -n Ehp
combine -M Asymptotic -d ehp4000_card.txt -m 4000 -n Ehp

hadd CombineEHP.root higgsCombineEhp.Asymptotic.mH1000.root higgsCombineEhp.Asymptotic.mH2000.root higgsCombineEhp.Asymptotic.mH3000.root higgsCombineEhp.Asymptotic.mH4000.root 
