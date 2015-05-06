Instructions to setup the ExoDiBosonResonances code
========

```
cmsrel CMSSW_7_2_5
cd CMSSW_7_2_5/src
cmsenv
git cms-init # This will allow you to checkout packages in official CMSSW.
git cms-merge-topic Sam-Harper:HEEPID72X  # HEEP Electron Identification
git clone -b Phys14 git@github.com:cms-edbr/ExoDiBosonResonancesRun2.git ExoDiBosonResonances
scram b -j 9
```

#IMPORTANT: 

These instructions should always be up-to-date with the ones in our Twiki:

`https://twiki.cern.ch/twiki/bin/view/CMS/ExoDiBosonResonancesRun2`
