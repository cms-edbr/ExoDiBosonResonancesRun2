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

root -b -q 'shapeAnalysis.C("EHP", 600)'
root -b -q 'shapeAnalysis.C("EHP", 800)'
root -b -q 'shapeAnalysis.C("EHP", 1000)'
root -b -q 'shapeAnalysis.C("EHP", 1200)'
root -b -q 'shapeAnalysis.C("EHP", 1400)'
root -b -q 'shapeAnalysis.C("EHP", 1600)'
root -b -q 'shapeAnalysis.C("EHP", 1800)'
root -b -q 'shapeAnalysis.C("EHP", 2000)'
root -b -q 'shapeAnalysis.C("EHP", 2500)'
root -b -q 'shapeAnalysis.C("EHP", 3000)'
root -b -q 'shapeAnalysis.C("EHP", 3500)'
root -b -q 'shapeAnalysis.C("EHP", 4000)'
root -b -q 'shapeAnalysis.C("EHP", 4500)'

root -b -q 'shapeAnalysis.C("ELP", 600)'
root -b -q 'shapeAnalysis.C("ELP", 800)'
root -b -q 'shapeAnalysis.C("ELP", 1000)'
root -b -q 'shapeAnalysis.C("ELP", 1200)'
root -b -q 'shapeAnalysis.C("ELP", 1400)'
root -b -q 'shapeAnalysis.C("ELP", 1600)'
root -b -q 'shapeAnalysis.C("ELP", 1800)'
root -b -q 'shapeAnalysis.C("ELP", 2000)'
root -b -q 'shapeAnalysis.C("ELP", 2500)'
root -b -q 'shapeAnalysis.C("ELP", 3000)'
root -b -q 'shapeAnalysis.C("ELP", 3500)'
root -b -q 'shapeAnalysis.C("ELP", 4000)'
root -b -q 'shapeAnalysis.C("ELP", 4500)'

root -b -q 'shapeAnalysis.C("MHP", 600)'
root -b -q 'shapeAnalysis.C("MHP", 800)'
root -b -q 'shapeAnalysis.C("MHP", 1000)'
root -b -q 'shapeAnalysis.C("MHP", 1200)'
root -b -q 'shapeAnalysis.C("MHP", 1400)'
root -b -q 'shapeAnalysis.C("MHP", 1600)'
root -b -q 'shapeAnalysis.C("MHP", 1800)'
root -b -q 'shapeAnalysis.C("MHP", 2000)'
root -b -q 'shapeAnalysis.C("MHP", 2500)'
root -b -q 'shapeAnalysis.C("MHP", 3000)'
root -b -q 'shapeAnalysis.C("MHP", 3500)'
root -b -q 'shapeAnalysis.C("MHP", 4000)'
root -b -q 'shapeAnalysis.C("MHP", 4500)'

root -b -q 'shapeAnalysis.C("MLP", 600)'
root -b -q 'shapeAnalysis.C("MLP", 800)'
root -b -q 'shapeAnalysis.C("MLP", 1000)'
root -b -q 'shapeAnalysis.C("MLP", 1200)'
root -b -q 'shapeAnalysis.C("MLP", 1400)'
root -b -q 'shapeAnalysis.C("MLP", 1600)'
root -b -q 'shapeAnalysis.C("MLP", 1800)'
root -b -q 'shapeAnalysis.C("MLP", 2000)'
root -b -q 'shapeAnalysis.C("MLP", 2500)'
root -b -q 'shapeAnalysis.C("MLP", 3000)'
root -b -q 'shapeAnalysis.C("MLP", 3500)'
root -b -q 'shapeAnalysis.C("MLP", 4000)'
root -b -q 'shapeAnalysis.C("MLP", 4500)'
