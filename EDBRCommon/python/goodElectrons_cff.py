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

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

def addElectronIDs(process):
   
    switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
    process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)
    
    my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V2_cff']
    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

    process.goodElectrons.src = "slimmedElectrons"
    process.eleSequence = cms.Sequence(process.egmGsfElectronIDSequence+process.goodElectrons)

    return process
#
# END ELECTRON ID SECTION
#
