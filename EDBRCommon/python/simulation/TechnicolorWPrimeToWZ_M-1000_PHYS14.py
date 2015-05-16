import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_1.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_10.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_11.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_12.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_13.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_14.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_15.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_16.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_17.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_18.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_19.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_2.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_20.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_21.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_22.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_23.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_24.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_25.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_3.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_4.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_5.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_6.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_7.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_8.root',
       '/store/user/tomei/Technicolor/pp_WP_ZW_eeqq_BM1_13tev-single_MINIAODSIM/150114_120524/0000/patTuple_9.root' ] );


secFiles.extend( [
               ] )

