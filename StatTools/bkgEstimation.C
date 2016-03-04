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

  RooRealVar candMass("candMass","M_{VZ}",                     600., 5000., "GeV");
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
  RooDataSet Data_SB("Data_SB","Data_SB", variables, Cut(allSB), Import(treeData));

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
  RooFitResult *rf1 = emodel1.fitTo(bkg1, Save(1), PrintLevel(-1));
  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(-1));

  // Fix the shapes and the subdominant background yields,
  // let only the yield of the dominant background to fluctuate
  c1.setConstant(true);
  c2.setConstant(true);
  offset1.setConstant(true);
  offset2.setConstant(true);
  width1.setConstant(true);
  width2.setConstant(true);
  nbkg1.setConstant(false);
  nbkg2.setConstant(true);

  // Final background model
  RooAddPdf model_ext("model_ext","sum of extended models",RooArgList(emodel1,emodel2));

  massVhad.setRange("lowerSB",   20.,   65.);
  massVhad.setRange("lowerSIG",  65.,  105.);
  massVhad.setRange("upperSIG", 105.,  135.);
  massVhad.setRange("upperSB",  135.,  220.);

  model_ext.fitTo(Data_SB,Extended(kTRUE),Range("lowerSB,upperSB"),PrintLevel(-1));
  nbkg1.setConstant(true);

  // Calculate integrals of the model
  RooAbsReal*     DY_integral = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal*    Sub_integral = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal*  DY_SB_integral = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB,upperSB"));
  RooAbsReal* Sub_SB_integral = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB,upperSB"));
  RooFormulaVar     DY_yield(    "DY_yield","@0*@1",RooArgList(    *DY_integral,nbkg1));
  RooFormulaVar    Sub_yield(   "Sub_yield","@0*@1",RooArgList(   *Sub_integral,nbkg2));
  RooFormulaVar  DY_SB_yield( "DY_SB_yield","@0*@1",RooArgList( *DY_SB_integral,nbkg1));
  RooFormulaVar Sub_SB_yield("Sub_SB_yield","@0*@1",RooArgList(*Sub_SB_integral,nbkg2));
  // Subdominant over Dominant ratio
  RooFormulaVar coef( "coef","@0/@1", RooArgList(Sub_SB_yield,DY_SB_yield));

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

  // Declare PDFs (levelled-exponentials) 
  RooRealVar      s0("s0","slope of the exp0", 100.,    0., 1000.);
  RooRealVar      s1("s1","slope of the exp1", 100.,    0., 1000.);
  RooRealVar      s2("s2","slope of the exp2", 100.,    0., 1000.);
  RooRealVar      s3("s3","slope of the exp3", 100.,    0., 1000.);
  RooRealVar      s4("s4","slope of the exp4", 100.,    0., 1000.);
  RooRealVar      a0("a0","parameter of exp0", 0.1 , 0.001,   10.);
  RooRealVar      a1("a1","parameter of exp1", 0.1 , 0.001,   10.);
  RooRealVar      a2("a2","parameter of exp2", 0.1 , 0.001,   10.);
  RooRealVar      a3("a3","parameter of exp3", 0.1 , 0.001,   10.);
  RooRealVar      a4("a4","parameter of exp4", 0.1 , 0.001,   10.);
  RooExpTailPdf     Sub_pdf(   "Sub_pdf", "Sub in nominal  region", candMass,s0,a0);
  RooExpTailPdf  Sub_SB_pdf("Sub_SB_pdf", "Sub in sideband region", candMass,s1,a1);
  RooExpTailPdf  Dat_SB    ("Dat_SB"    , "Data sideband",          candMass,s2,a2);
  RooExpTailPdf   DY_SR_pdf( "DY_SR_pdf", "DY in nominal   region", candMass,s3,a3);
  RooExpTailPdf   DY_SB_pdf( "DY_SB_pdf", "DY in sideband  region", candMass,s4,a4);

  // Model sideband Data as the contribution of subdominant and dominant 
  RooAddPdf Data_SB_pdf("Data_SB_pdf", "Model data in sideband", Sub_SB_pdf, Dat_SB, coef);
  // Alpha function
  RooAlpha4ExpTailPdf alpha("alpha", "alpha function for DY",  candMass,s3,a3,s4,a4);
  // Model DY in signal region
  RooProdPdf DY("DY", "DY in SIG", alpha, Dat_SB);

  // Range for fits
  candMass.setRange("range", 600., 3000);

  // Fit Subdominant backgrounds
  RooDataSet Sub(   "Sub",    "Sub",    variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC2));
  RooDataSet Sub_SB("Sub_SB", "Sub_SB", variables, Cut(allSB),    WeightVar(totalWeight), Import(treeMC2));
  Sub_pdf.fitTo(   Sub,    Range("range"), SumW2Error(true), PrintLevel(-1));
  Sub_SB_pdf.fitTo(Sub_SB, Range("range"), SumW2Error(true), PrintLevel(-1));
  s0.setConstant(true); a0.setConstant(true);
  s1.setConstant(true); a1.setConstant(true);

  // Fit Dominant backgrounds in lowerSIG
  // Fit Dominant backgrounds in lowerSB and upperSB
  // Fit Blinded data in lowerSB and upperSB
  RooDataSet  DY_SR("DY_SR", "DY_SR", variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC1));
  RooDataSet  DY_SB("DY_SB", "DY_SB", variables, Cut(allSB),    WeightVar(totalWeight), Import(treeMC1));
  RooCategory reg("reg","reg");
  reg.defineType("1");
  reg.defineType("2");
  reg.defineType("3");
  RooDataSet bigSample("bigSample","bigSample",variables,WeightVar(totalWeight),Index(reg),Import("1",DY_SR),Import("2",DY_SB),Import("3",Data_SB));
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(DY_SR_pdf,DY_SB_pdf,Data_SB_pdf), reg); 

  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE), PrintLevel(-1));
  s2.setConstant(true); a2.setConstant(true);
  s3.setConstant(true); a3.setConstant(true);
  s4.setConstant(true); a4.setConstant(true);

  // create workspace
  RooWorkspace *w = new RooWorkspace("ZZ_13TeV","workspace") ;

  RooRealVar  DY_pdf_norm( "DY_pdf_norm",  "DY yield in lowerSIG",  DY_yield.getVal(), 0.,1.e4);
  RooRealVar Sub_pdf_norm("Sub_pdf_norm", "Sub yield in lowerSIG", Sub_yield.getVal(), 0.,1.e4); 
  RooRealVar  DY_error( "DY_error", "DY yield error",1+ DY_yield.getPropagatedError(*rf1)/ DY_yield.getVal(),1.,2.);

  Sub_pdf_norm.setConstant(true); // we do not want to let that normalization float

  w->import(Sub_pdf);
  w->import(Sub_pdf_norm);
  w->import( DY_pdf_norm);
  w->import( DY_error);
  // diagonalization
  PdfDiagonalizer diag("pdf", w, *fitres);
  RooAbsPdf *DY_pdf = diag.diagonalize( DY );
  w->import(*DY_pdf , RecycleConflictNodes() );

  // Observed data
  RooDataSet data_obs("data_obs","data_obs",variables,Cut(lowerSIG),Import(treeData));
  w->import(data_obs);

  w->writeToFile(Form("workSpaces/CMS_ZZ_%s_13TeV.root",key.c_str()));
}
