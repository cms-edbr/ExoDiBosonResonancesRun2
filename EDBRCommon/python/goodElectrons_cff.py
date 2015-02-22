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

def addElectronIDs(process):
    # Load tools and function definitions
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
    
    process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi")
    # overwrite a default parameter: for miniAOD, the collection name is a slimmed one
    process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('slimmedElectrons')
    
    from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry
    process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)
    
    # Define which IDs we want to produce
    # Each of these two example IDs contains all four standard 
    # cut-based ID working points (only two WP of the PU20bx25 are actually used here).
    my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V1_miniAOD_cff']
    #Add them to the VID producer
    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
    
    # Do not forget to add the egmGsfElectronIDSequence to the path,
    process.eleSequence = cms.Sequence(process.egmGsfElectronIDSequence+process.isolatedElectrons+process.goodElectrons)

    return process
#
# END ELECTRON ID SECTION
#
