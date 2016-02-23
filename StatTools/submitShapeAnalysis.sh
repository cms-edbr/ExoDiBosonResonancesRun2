#!/bin/bash
#
# Usage: 
#
#         1) Create empty folders to host dataCards and workSpaces
#
#            mkdir dataCards; mkdir workSpaces;
#
#         2) Verify the location of the input files (../trees)
#
#         3) Run this macro:
#
#            source submitShapeAnalysis.sh

root -b -q 'bkgEstimation.C("ELP")'
root -b -q 'bkgEstimation.C("EHP")'
root -b -q 'bkgEstimation.C("MLP")'
root -b -q 'bkgEstimation.C("MHP")'

root -b -q 'signalShapes.C("ELP")'
root -b -q 'signalShapes.C("EHP")'
root -b -q 'signalShapes.C("MLP")'
root -b -q 'signalShapes.C("MHP")'

for (( i=600; i<=4000; i+=100 ))
  do
    root -b -q 'makeDataCards.C("ELP",'"$i"')'
    root -b -q 'makeDataCards.C("EHP",'"$i"')'
    root -b -q 'makeDataCards.C("MLP",'"$i"')'
    root -b -q 'makeDataCards.C("MHP",'"$i"')'
  done
