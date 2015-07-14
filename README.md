Instructions to setup the ExoDiBosonResonances code
========

```
cmsrel CMSSW_7_4_7
cd CMSSW_7_4_7/src
cmsenv
git cms-merge-topic jruizvar:HEEPV60_NonIso
git clone -b Analysis74X git@github.com:cms-edbr/ExoDiBosonResonancesRun2.git ExoDiBosonResonances
scram b -j 9
```

#IMPORTANT: 

These instructions should always be up-to-date with the ones in our Twiki:

`https://twiki.cern.ch/twiki/bin/view/CMS/ExoDiBosonResonancesRun2`
