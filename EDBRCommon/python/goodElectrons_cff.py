import FWCore.ParameterSet.Config as cms

goodElectrons = cms.EDFilter("PATElectronSelector",
                             src = cms.InputTag("goodLeptons:goodElectrons"),
                             cut = cms.string(""),
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
                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']

    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

    return process

#
# END ELECTRON ID SECTION
#
