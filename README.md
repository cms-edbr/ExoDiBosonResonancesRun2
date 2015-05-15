Instructions to setup the ExoDiBosonResonances code
========

```
cmsrel CMSSW_7_4_2
cd CMSSW_7_4_2/src
cmsenv
git cms-init # This will allow you to checkout packages in official CMSSW.
git cms-merge-topic ikrav:egm_id_74X_v0 # Recommended Electron Identification
git clone -b Analysis74X git@github.com:cms-edbr/ExoDiBosonResonancesRun2.git ExoDiBosonResonances
scram b -j 9
```

#IMPORTANT: 

These instructions should always be up-to-date with the ones in our Twiki:

`https://twiki.cern.ch/twiki/bin/view/CMS/ExoDiBosonResonancesRun2`
