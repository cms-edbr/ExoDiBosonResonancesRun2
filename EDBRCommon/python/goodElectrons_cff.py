import FWCore.ParameterSet.Config as cms

goodElectrons = cms.EDFilter("PATElectronSelector",
                             src = cms.InputTag("goodLeptons:goodElectrons"),
                             cut = cms.string("pt > 115 & abs(eta) < 2.5 & "
                             #cut = cms.string("pt > 40 & abs(eta) < 2.5 & "
                                              "(abs(superCluster().position().eta()) < 1.442 ||"
                                              " abs(superCluster().position().eta()) > 1.566)  "),
                             filter = cms.bool(False)
                            )

eleSequence = cms.Sequence(goodElectrons)

#
# START ELECTRON ID SECTION
#

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

def addElectronIDs(process):
   
    switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)

    my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V2_cff',
                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_modHEEPV60_cff',
                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']

    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

    # switch off isolation for HEEP
    #process.egmGsfElectronIDs.physicsObjectIDs[4].idDefinition.cutFlow[8].isIgnored = True

    return process

#
# END ELECTRON ID SECTION
#
