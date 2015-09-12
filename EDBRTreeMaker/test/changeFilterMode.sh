#!/bin/bash 
#
# filterMode == True 
#                     * Filter events before the EDBRTreeMaker 
#                     * Endpath with the trigReportAnalyser is included
#
# filterMode == False
#                     * Do not filter events before the EDBRTreeMaker
#                     * Endpath is removed
#                     * hltSequence is removed.
#                       Use this mode for trigger studies
#
# Change filter mode from True to False with the following command:
sed -i '202 s/True/False/' *.py
