Instructions to setup the ExoDiBosonResonances code
========

```
cmsrel CMSSW_7_0_9
cd CMSSW_7_0_9/src
cmsenv
git cms-init # This will allow you to checkout packages in official CMSSW.
git clone git@github.com:cms-edbr/ExoDiBosonResonancesRun2.git ExoDiBosonResonances
# Before compiling, you need to setup the N-subjettiness
cd $CMSSW_BASE/src
cp $CMSSW_BASE/src/ExoDiBosonResonances/EDBRJets/tools/* $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/
# Tell SCRAM that those tools are going to be setup
scram setup fastjet-contrib
scram setup fastjet-contrib-archive
# Then compile:
scram b -j 9
```

#IMPORTANT: 

These instructions should always be up-to-date with the ones in our Twiki:

`https://twiki.cern.ch/twiki/bin/view/CMS/ExoDiBosonResonancesRun2`
