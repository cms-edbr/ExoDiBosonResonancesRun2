#!/bin/bash
echo "Creating python files for LHE files:"
ls *.lhe
echo "***********************"
for i in `ls *lhe`; do
    base=${i%.*}
    echo $base
    sed 's/INPUTLHEFILENAME/'${base}'/g' step1_TEMPLATE.py > step1_${base}.py
    sed 's/PARAMPUBLISH/'${base}'_GENSIM/g;s/CMSSWPYNAME/step1_'${base}'.py/g;s/CRABREQUESTNAME/step1_'${base}'/g' crabConfig_TEMPLATE.py > crabConfig_${base}.py
done
