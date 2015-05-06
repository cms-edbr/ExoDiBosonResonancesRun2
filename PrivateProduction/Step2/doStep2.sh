#!/bin/bash
INPUT=$1
base=$INPUT
echo $base
sed 's/PARAMPUBLISH/'${base}'/g;s/CRABREQUESTNAME/step2_'${base}'/g' crabConfig_TEMPLATE2.py > crabConfig_${base}_RAWSIM.py
