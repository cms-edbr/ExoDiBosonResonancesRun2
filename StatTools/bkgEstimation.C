//
//        Requires pre-compiled PDFs library  
//
//        Requires ROOT 6.04/02 (or above) to take advantage of R__LOAD_LIBRARY
//        https://root.cern.ch/root/html604/notes/release-notes.html#interpreter  
//
//        Examples of usage:
// 
//        root -b -q 'bkgEstimation.C("ENP")'   // Electron No Purity
//        root -b -q 'bkgEstimation.C("EHP")'   // Electron High Purity
//        root -b -q 'bkgEstimation.C("ELP")'   // Electron Low Purity
//        root -b -q 'bkgEstimation.C("MNP")'   // Muon No Purity
//        root -b -q 'bkgEstimation.C("MHP")'   // Muon High Purity
//        root -b -q 'bkgEstimation.C("MLP")'   // Muon Low Purity

R__LOAD_LIBRARY(PDFs/HWWLVJRooPdfs_cxx.so)
R__LOAD_LIBRARY(PDFs/PdfDiagonalizer_cc.so)

void bkgEstimation(std::string key)
{
  using namespace RooFit;

  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);

  RooRealVar candMass("candMass","M_{VZ}",                     550., 5000., "GeV");
  RooRealVar massVhad("massVhad","pruned m_{jet}",              20.,  220., "GeV");
  RooRealVar tau21("tau21","tau21",                              0.,  0.75       );
  RooRealVar lep("lep","lep",                                    10,    15       );
  RooRealVar totalWeight("totalWeight", "total weight",          0.,    10.      );
  RooRealVar pileupWeight("pileupWeight","pileup",               0.,    10.      );
  RooArgSet  variables(candMass,massVhad,tau21,lep,totalWeight);

  std::map<std::string, std::string> selection;
  selection["ENP"] = "lep<12 && tau21<0.75";
  selection["MNP"] = "lep>12 && tau21<0.75";
  selection["EHP"] = "lep<12 && tau21<0.45";
  selection["MHP"] = "lep>12 && tau21<0.45";
  selection["ELP"] = "lep<12 && tau21>0.45";
  selection["MLP"] = "lep>12 && tau21>0.45";

  TCut selectedCategory = selection[key].c_str();
  TCut lowerSIG = "massVhad>65.  && massVhad<105" + selectedCategory;
  TCut upperSIG = "massVhad>105. && massVhad<135" + selectedCategory;
  TCut lowerSB  = "massVhad<65."  + selectedCategory;
  TCut upperSB  = "massVhad>135." + selectedCategory;
  TCut allSB    = lowerSB or upperSB;

  //*******************************************************//
  //                                                       //     
  //                      Input files                      //
  //                                                       //     
  //*******************************************************//

  TChain treeData("treeDumper/EDBRCandidates");
  TChain treeMC1( "treeDumper/EDBRCandidates");
  TChain treeMC2( "treeDumper/EDBRCandidates");
  std::string lepton_scale;

  if( key[0]=='E' ){ 
      treeData.Add(     "trees/treeEDBR_SingleElectron1.root"                ); 
      treeData.Add(     "trees/treeEDBR_SingleElectron2.root"                ); 
      treeMC2.Add(      "trees/treeEDBR_TT_el.root"                          );
      treeMC2.Add(      "trees/treeEDBR_WW_el.root"                          );
      treeMC2.Add(      "trees/treeEDBR_WZ_el.root"                          );
      treeMC2.Add(      "trees/treeEDBR_ZZ_el.root"                          );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT100to200_el.root"       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT200to400_el.root"       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT400to600_el.root"       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT600toInf_el.root"       );
      lepton_scale    = "1.005";
  }

  if( key[0]=='M' ){
      treeData.Add(     "trees/treeEDBR_SingleMuon1.root"                    ); 
      treeData.Add(     "trees/treeEDBR_SingleMuon2.root"                    ); 
      treeMC2.Add(      "trees/treeEDBR_TT_mu.root"                          );
      treeMC2.Add(      "trees/treeEDBR_WW_mu.root"                          );
      treeMC2.Add(      "trees/treeEDBR_WZ_mu.root"                          );
      treeMC2.Add(      "trees/treeEDBR_ZZ_mu.root"                          );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT100to200_mu.root"       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT200to400_mu.root"       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT400to600_mu.root"       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT600toInf_mu.root"       );
      lepton_scale    = "1.03";
  }

  // dataset to host data in sideband
  RooDataSet sbObs("sbObs","sbObs", variables, Cut(allSB), Import(treeData));

  // MC datasets
  RooDataSet bkg1( "bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC1));
  RooDataSet bkg2( "bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC2));
  RooRealVar nbkg1("nbkg1","nbkg1",bkg1.sumEntries(),bkg1.sumEntries()/10,bkg1.sumEntries()*10);
  RooRealVar nbkg2("nbkg2","nbkg2",bkg2.sumEntries(),bkg2.sumEntries()/10,bkg1.sumEntries()*10);

/////////////////////////////////////////////////////////////////////////////////////
//        _   _                                                                    //
//       | \ | |                          | (_)         | | (_)                    //
//       |  \| | ___  _ __ _ __ ___   __ _| |_ ___  __ _| |_ _  ___  _ __          //
//       | . ` |/ _ \| '__| '_ ` _ \ / _` | | / __|/ _` | __| |/ _ \| '_ \         //
//       | |\  | (_) | |  | | | | | | (_| | | \__ \ (_| | |_| | (_) | | | |        //
//       |_| \_|\___/|_|  |_| |_| |_|\__,_|_|_|___/\__,_|\__|_|\___/|_| |_|        //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////

  // Error Function * Exponential
  RooRealVar c1("c1","slope of the exp",             -0.020,  -1.,    0.);
  RooRealVar c2("c2","slope of the exp",             -0.020,  -1.,    0.);
  RooRealVar offset1("offset1","offset of the erf",    20.0,   1.,  200.);
  RooRealVar offset2("offset2","offset of the erf",    20.0,   1.,  200.);
  RooRealVar width1("width1",  "width of the erf",     50.0,   1.,  200.);
  RooRealVar width2("width2",  "width of the erf",     50.0,   1.,  200.);
  RooErfExpPdf model1("model1","fiting mj spectrum1",massVhad,c1,offset1,width1);
  RooErfExpPdf model2("model2","fiting mj spectrum2",massVhad,c2,offset2,width2);
  RooExtendPdf emodel1("emodel1","extended dom backgrounds",model1,nbkg1);
  RooExtendPdf emodel2("emodel2","extended sub backgrounds",model2,nbkg2);
  emodel1.fitTo(bkg1, PrintLevel(-1));
  emodel2.fitTo(bkg2, PrintLevel(-1));
  c1.setConstant(true);
  c2.setConstant(true);
  offset1.setConstant(true);
  offset2.setConstant(true);
  width1.setConstant(true);
  width2.setConstant(true);

  // Final background model
  RooAddPdf model_ext("model_ext","sum of extended models",RooArgList(emodel1,emodel2));

  // IMPORTANT! The final result strongly depends on the upper sideband limit
  //            For electron (muons) a limit at 165 (150) seems to work  
  std::map<std::string, double> massVhadUpp;
  massVhadUpp["EHP"] = massVhadUpp["ELP"] = massVhadUpp["ENP"] = 165.;
  massVhadUpp["MHP"] = massVhadUpp["MLP"] = massVhadUpp["MNP"] = 150.;
  massVhad.setRange("lowerSB",      20.,               65.);
  massVhad.setRange("lowerSIG",     65.,              105.);
  massVhad.setRange("upperSIG",    105.,              135.);
  massVhad.setRange("upperSB",     135.,  massVhadUpp[key]);

  RooFitResult* erf = model_ext.fitTo(sbObs,Extended(kTRUE),Range("lowerSB,upperSB"),PrintLevel(-1),Save());

  // Calculate integral of the model
  RooAbsReal* domBkgIntegralSR = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* subBkgIntegralSR = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooFormulaVar domBkgSRyield("domBkgSRyield","@0*@1",RooArgList(*domBkgIntegralSR,nbkg1));
  RooFormulaVar subBkgSRyield("subBkgSRyield","@0*@1",RooArgList(*subBkgIntegralSR,nbkg2));
  RooFormulaVar lowerSIGyield("lowerSIGyield","extrapolation to lowerSIG","@0+@1", RooArgList(domBkgSRyield,subBkgSRyield));
  Double_t bkgYield       =     lowerSIGyield.getVal(); 
  RooRealVar ZZ_bkg_eig_norm("ZZ_bkg_eig_norm","expected yield in lowerSIG",bkgYield,0.,1.e4);
  RooRealVar bkgYield_error("bkgYield_error","background yield error",1+lowerSIGyield.getPropagatedError(*erf)/bkgYield,1.,2.);

///////////////////////////////////////////////////////////////////////////////
//                           _____ _                                         //
//                          / ____| |                                        //
//                         | (___ | |__   __ _ _ __   ___                    //
//                          \___ \| '_ \ / _` | '_ \ / _ \                   // 
//                          ____) | | | | (_| | |_) |  __/                   //
//                         |_____/|_| |_|\__,_| .__/ \___|                   //
//                                            | |                            //
//                                            |_|                            // 
///////////////////////////////////////////////////////////////////////////////

  // Declare PDFs (3 levelled-exponentials) 
  RooRealVar s0("s0","slope of the exp0", 100.,    0., 1000.);
  RooRealVar s1("s1","slope of the exp1", 100.,    0., 1000.);
  RooRealVar s2("s2","slope of the exp2", 100.,    0., 1000.);
  RooRealVar a0("a0","parameter of exp0", 0.1 , 0.001,   10.);
  RooRealVar a1("a1","parameter of exp1", 0.1 , 0.001,   10.);
  RooRealVar a2("a2","parameter of exp2", 0.1 , 0.001,   10.);
  RooExpTailPdf       nsBkg_pdf("nsBkg_pdf", "fit bkg  in nominal  reg",   candMass,s0,a0);
  RooExpTailPdf       sbBkg_pdf("sbBkg_pdf", "fit bkg  in sideband reg",   candMass,s1,a1);
  RooExpTailPdf       sbObs_pdf("sbObs_pdf", "fit data in sideband reg",   candMass,s2,a2);
  RooAlpha4ExpTailPdf alpha_pdf("alpha_pdf", "alpha ratio",                   candMass,s0,a0,s1,a1);
  RooProdPdf             ZZ_bkg("ZZ_bkg", "Data-driven bakground estimation", alpha_pdf, sbObs_pdf);

  // Fit 1) Dominant backgrounds in lowerSIG
  // Fit 2) Dominant backgrounds in lowerSB and upperSB
  // Fit 3) Blinded data in lowerSB and upperSB
  RooDataSet nsBkg("nsBkg", "nsBkg", variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC1));
  RooDataSet sbBkg("sbBkg", "sbBkg", variables, Cut(allSB),    WeightVar(totalWeight), Import(treeMC1));
  RooCategory reg("reg","reg");
  reg.defineType("nsMC");
  reg.defineType("sbMC");
  reg.defineType("sbDA");
  RooDataSet bigSample("bigSample","bigSample",variables,WeightVar(totalWeight),Index(reg),Import("nsMC",nsBkg),Import("sbMC",sbBkg),Import("sbDA",sbObs));
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(nsBkg_pdf,sbBkg_pdf,sbObs_pdf), reg); 

  candMass.setRange("range", 550., 4000);
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE), PrintLevel(-1));

  s0.setConstant(true);
  s1.setConstant(true);
  s2.setConstant(true);
  a0.setConstant(true);
  a1.setConstant(true);
  a2.setConstant(true);

  // create workspace
  RooWorkspace *w = new RooWorkspace("ZZ_13TeV","workspace") ;
  w->import(ZZ_bkg);
  w->import(ZZ_bkg_eig_norm);
  w->import(bkgYield_error);
  
  // diagonalization
  PdfDiagonalizer diago("eig", w, *fitres);
  RooAbsPdf *ZZ_bkg_eig = diago.diagonalize(*w->pdf("ZZ_bkg"));
  w->import(*ZZ_bkg_eig, RecycleConflictNodes());

  // Observed data
  RooDataSet data_obs("data_obs","data_obs",variables,Cut(lowerSIG),Import(treeData));
  w->import(data_obs);

  w->writeToFile(Form("workSpaces/CMS_ZZ_%s_13TeV.root",key.c_str()));
 
}
