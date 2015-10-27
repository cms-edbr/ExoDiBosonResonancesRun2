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

root -b -q 'shapeAnalysis.C("ENP", 800)'
root -b -q 'shapeAnalysis.C("ENP", 1000)'
root -b -q 'shapeAnalysis.C("ENP", 1200)'
root -b -q 'shapeAnalysis.C("ENP", 1400)'
root -b -q 'shapeAnalysis.C("ENP", 1600)'
root -b -q 'shapeAnalysis.C("ENP", 1800)'
root -b -q 'shapeAnalysis.C("ENP", 2000)'
root -b -q 'shapeAnalysis.C("ENP", 2500)'
root -b -q 'shapeAnalysis.C("ENP", 3000)'
root -b -q 'shapeAnalysis.C("ENP", 3500)'
root -b -q 'shapeAnalysis.C("ENP", 4000)'
root -b -q 'shapeAnalysis.C("ENP", 4500)'

root -b -q 'shapeAnalysis.C("MNP", 800)'
root -b -q 'shapeAnalysis.C("MNP", 1000)'
root -b -q 'shapeAnalysis.C("MNP", 1200)'
root -b -q 'shapeAnalysis.C("MNP", 1400)'
root -b -q 'shapeAnalysis.C("MNP", 1600)'
root -b -q 'shapeAnalysis.C("MNP", 1800)'
root -b -q 'shapeAnalysis.C("MNP", 2000)'
root -b -q 'shapeAnalysis.C("MNP", 2500)'
root -b -q 'shapeAnalysis.C("MNP", 3000)'
root -b -q 'shapeAnalysis.C("MNP", 3500)'
root -b -q 'shapeAnalysis.C("MNP", 4000)'
root -b -q 'shapeAnalysis.C("MNP", 4500)'
