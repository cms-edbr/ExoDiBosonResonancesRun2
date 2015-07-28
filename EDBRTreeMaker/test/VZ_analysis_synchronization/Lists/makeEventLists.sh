#!/bin/bash 
#
# Create lists of events passing VZ analysis preselection
#

root -b -q 'scanTree.C(600, 11)'
root -b -q 'scanTree.C(800, 11)'
root -b -q 'scanTree.C(1000, 11)'
root -b -q 'scanTree.C(1200, 11)'
root -b -q 'scanTree.C(1400, 11)'
root -b -q 'scanTree.C(1600, 11)'
root -b -q 'scanTree.C(1800, 11)'
root -b -q 'scanTree.C(2000, 11)'
root -b -q 'scanTree.C(2500, 11)'
root -b -q 'scanTree.C(3000, 11)'
root -b -q 'scanTree.C(3500, 11)'
root -b -q 'scanTree.C(4000, 11)'
root -b -q 'scanTree.C(4500, 11)'

root -b -q 'scanTree.C(600, 13)'
root -b -q 'scanTree.C(800, 13)'
root -b -q 'scanTree.C(1000, 13)'
root -b -q 'scanTree.C(1200, 13)'
root -b -q 'scanTree.C(1400, 13)'
root -b -q 'scanTree.C(1600, 13)'
root -b -q 'scanTree.C(1800, 13)'
root -b -q 'scanTree.C(2000, 13)'
root -b -q 'scanTree.C(2500, 13)'
root -b -q 'scanTree.C(3000, 13)'
root -b -q 'scanTree.C(3500, 13)'
root -b -q 'scanTree.C(4000, 13)'
root -b -q 'scanTree.C(4500, 13)'
