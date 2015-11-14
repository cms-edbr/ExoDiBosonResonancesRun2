#!/bin/bash 
#
# Run analyzer over BulkG samples

cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-800  mu &> BulkGrav800.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1000 mu &> BulkGrav1000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1200 mu &> BulkGrav1200.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1400 mu &> BulkGrav1400.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1600 mu &> BulkGrav1600.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1800 mu &> BulkGrav1800.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-2000 mu &> BulkGrav2000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-2500 mu &> BulkGrav2500.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-3000 mu &> BulkGrav3000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-3500 mu &> BulkGrav3500.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-4000 mu &> BulkGrav4000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-4500 mu &> BulkGrav4500.log &
