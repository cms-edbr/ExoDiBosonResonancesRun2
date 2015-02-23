import FWCore.ParameterSet.Config as cms

isolatedElectrons = cms.EDFilter("PATElectronSelector",
                             src = cms.InputTag("slimmedElectrons"),
                             cut = cms.string("(pfIsolationVariables().sumChargedHadronPt"                +\
                                              "    + max(0.0, pfIsolationVariables().sumNeutralHadronEt"  +\
                                              "              +pfIsolationVariables().sumPhotonEt"         +\
                                              "          -0.5*pfIsolationVariables().sumPUPt))/pt < 0.33" 
                                             )
                             )

goodElectrons = cms.EDFilter("PATElectronSelector",
                             src = cms.InputTag("isolatedElectrons"),
                             cut = cms.string("pt > 40 & abs(eta) < 2.5 & "+\
                                              "(abs(superCluster().position().eta()) < 1.442 || "+\
                                              "abs(superCluster().position().eta()) > 1.566)"  
                                             )
                             )

eleSequence = cms.Sequence(isolatedElectrons+goodElectrons)

#
# START ELECTRON ID SECTION
#
# Set up everything that is needed to compute electron IDs and
# add the ValueMaps with ID decisions into the event data stream
#

# Load tools and function definitions
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
 
def addElectronIDs(process):
   
    process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi")
    process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('slimmedElectrons')
    
    from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry
    process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)
    
    process.load('RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV51_cff')
    setupVIDSelection(process.egmGsfElectronIDs,process.heepElectronID_HEEPV51_miniAOD)   

    process.eleSequence = cms.Sequence(process.egmGsfElectronIDSequence+process.goodElectrons)

    return process
#
# END ELECTRON ID SECTION
#
