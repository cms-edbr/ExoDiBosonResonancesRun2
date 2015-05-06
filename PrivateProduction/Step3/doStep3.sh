#!/bin/bash
INPUT=$1
base=$INPUT
echo $base
sed 's/PARAMPUBLISH/'${base}'/g;s/CRABREQUESTNAME/step3_'${base}'/g' crabConfig_TEMPLATE3.py > crabConfig_${base}_AODSIM.py
