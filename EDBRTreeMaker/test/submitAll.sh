#!/bin/bash 
#
# Run analyzer over BulkG samples

cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-600  el &> BulkGrav600.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-800  el &> BulkGrav800.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1000 el &> BulkGrav1000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1200 el &> BulkGrav1200.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1400 el &> BulkGrav1400.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1600 el &> BulkGrav1600.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-1800 el &> BulkGrav1800.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-2000 el &> BulkGrav2000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-2500 el &> BulkGrav2500.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-3000 el &> BulkGrav3000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-3500 el &> BulkGrav3500.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-4000 el &> BulkGrav4000.log &
cmsRun analysis-BulkGrav.py BulkGravToZZToZlepZhad_M-4500 el &> BulkGrav4500.log &
