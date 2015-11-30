//
//        Requires pre-compiled PDFs library  
//
//        Requires ROOT 6.04/02 (or above) to take advantage of R__LOAD_LIBRARY
//        https://root.cern.ch/root/html604/notes/release-notes.html#interpreter  
//
//        Examples of usage:
// 
//        root -b -q 'shapeAnalysisSanityCheck.C("ALL")'
//        root -b -q 'shapeAnalysisSanityCheck.C("EHP")'
//        root -b -q 'shapeAnalysisSanityCheck.C("ELP")'
//        root -b -q 'shapeAnalysisSanityCheck.C("MHP")'
//        root -b -q 'shapeAnalysisSanityCheck.C("MLP")'
//

R__LOAD_LIBRARY(PDFs/HWWLVJRooPdfs_cxx.so)

void shapeAnalysisSanityCheck(std::string key)
{
  using namespace RooFit;

  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);

  RooRealVar candMass("candMass","M_{VZ}",            600., 4800., "GeV");
  RooRealVar massVhad("massVhad","pruned m_{j}",       40., 9999., "GeV");
  RooRealVar tau21("tau21","tau21",                     0.,    1.       );
  RooRealVar lep("lep","lep",                           10,    15       );
  RooRealVar region("region","region",                   0,     4       );
  RooRealVar totalWeight("totalWeight", "total weight", 0.,    10.      );
  RooArgSet variables(candMass,massVhad,tau21,lep,region,totalWeight);

  massVhad.setRange("lowerSB",      40.,   65.);
  massVhad.setRange("lowerSIG",     65.,  105.);
  massVhad.setRange("upperSIG",    105.,  135.);
  massVhad.setRange("upperSB",     135.,  220.);

  std::map<std::string, std::string> selection;
  selection["ALL"] = "candMass>600";
  selection["EHP"] = "candMass>600 && lep<12 && tau21<0.6";
  selection["MHP"] = "candMass>600 && lep>12 && tau21<0.6";
  selection["ELP"] = "candMass>600 && lep<12 && tau21>0.6 && tau21<0.75";
  selection["MLP"] = "candMass>600 && lep>12 && tau21>0.6 && tau21<0.75";
 
  TCut selectedCategory = selection[key].c_str();
  TCut lowerSIG = "massVhad>65.  && massVhad<105" + selectedCategory;
  TCut upperSIG = "massVhad>105. && massVhad<135" + selectedCategory;
  TCut lowerSB  = "massVhad<65."  + selectedCategory;
  TCut upperSB  = "massVhad>135." + selectedCategory;
  TCut allSB    = lowerSB or upperSB;

  TChain treeData("treeDumper/EDBRCandidates");
  treeData.Add("../muTrees/nov13/treeEDBR_SingleMuon.root"); 
  treeData.Add("../elTrees/nov13/treeEDBR_SingleElectron.root"); 
  // dataset to host data in sideband and runs<259626
  RooRealVar run("run","run", 256630, 260627);
  TCut blindData = "(region==0||region==3) && run<259626"; 
  RooDataSet sbObs("sbObs","sbObs", RooArgSet(massVhad,candMass,tau21,lep,run,region,totalWeight),Cut(blindData+allSB), Import(treeData));

  // dominant backgrounds
  TChain treeMC1("treeDumper/EDBRCandidates");
  treeMC1.Add("../elTrees/nov13/treeEDBR_DYJetsToLL_HT-100to200.root");
  treeMC1.Add("../elTrees/nov13/treeEDBR_DYJetsToLL_HT-200to400.root");
  treeMC1.Add("../elTrees/nov13/treeEDBR_DYJetsToLL_HT-400to600.root");
  treeMC1.Add("../elTrees/nov13/treeEDBR_DYJetsToLL_HT-600toInf.root");
  treeMC1.Add("../muTrees/nov13/treeEDBR_DYJetsToLL_HT-100to200.root");
  treeMC1.Add("../muTrees/nov13/treeEDBR_DYJetsToLL_HT-200to400.root");
  treeMC1.Add("../muTrees/nov13/treeEDBR_DYJetsToLL_HT-400to600.root");
  treeMC1.Add("../muTrees/nov13/treeEDBR_DYJetsToLL_HT-600toInf.root");
  // subdominant backgrounds
  TChain treeMC2("treeDumper/EDBRCandidates");
  treeMC2.Add("../elTrees/nov13/treeEDBR_WZ.root");
  treeMC2.Add("../elTrees/nov13/treeEDBR_ZZ.root");
  treeMC2.Add("../elTrees/nov13/treeEDBR_T_T.root");
  treeMC2.Add("../muTrees/nov13/treeEDBR_WZ.root");
  treeMC2.Add("../muTrees/nov13/treeEDBR_ZZ.root");
  treeMC2.Add("../muTrees/nov13/treeEDBR_T_T.root");
  // MC datasets
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), Import(treeMC1));
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), Import(treeMC2));
  RooCategory MC("MC","MC");
  MC.defineType(   "dominant");
  MC.defineType("subdominant");
  RooDataSet temp("allMC","allMC", variables, Index(MC), Import("dominant",bkg1), Import("subdominant",bkg2));
  // formula to weight MC
  const char *weightFormula = "(totalWeight<0.99)*totalWeight*1263.886/2093.917 + (totalWeight>0.99)";
  RooFormulaVar wFunc("wFunc","event weight", weightFormula, RooArgList(totalWeight));
  RooRealVar* w1 = (RooRealVar*) temp.addColumn(wFunc);
  RooDataSet allMC(temp.GetName(), temp.GetTitle(), &temp, *temp.get(),0,w1->GetName());
  RooDataSet* ds1 = (RooDataSet*) allMC.reduce(variables,"MC==0");
  RooDataSet* ds2 = (RooDataSet*) allMC.reduce(variables,"MC==1");
  RooRealVar yield1("yield1", "Zjets normalization", ds1->sumEntries(), 1., 1.e3);
  RooRealVar yield2("yield2", "Other backgrounds",   ds2->sumEntries(), 1., 1.e3);
  RooRealVar coef("coef","coef",yield2.getVal()/yield1.getVal(),0.,1.);
  coef.setConstant(true);

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
  RooRealVar offset1("offset1","offset of the erf",    10.0,   1.,  200.);
  RooRealVar offset2("offset2","offset of the erf",    10.0,   1.,  200.);
  RooRealVar width1("width1",  "width of the erf",     50.0,   1.,  200.);
  RooRealVar width2("width2",  "width of the erf",     50.0,   1.,  200.);
  RooErfExpPdf model1("model1","fiting mj spectrum",massVhad,c1,offset1,width1);
  RooErfExpPdf model2("model2","fiting mj spectrum",massVhad,c2,offset2,width2);
  RooFitResult* r1 = model1.fitTo(*ds1, Range("lowerSB,lowerSIG,upperSIG,upperSB"),Save(1),PrintLevel(-1));
  RooFitResult* r2 = model2.fitTo(*ds2, Range("lowerSB,lowerSIG,upperSIG,upperSB"),Save(1),PrintLevel(-1));
  // Final background model
  RooAddPdf model("model","model",RooArgList(model2,model1),coef);
  c1.setConstant(true);
  c2.setConstant(true);
  offset1.setConstant(true);
  offset2.setConstant(true);
  width1.setConstant(true);
  width2.setConstant(true);

  // Extended models
  RooRealVar yieldLowerSB( "#color[4]{lower SB}",  "Lower SB normalization",  10, 1., 1.e3);
  RooRealVar yieldLowerSIG("#color[2]{lower SIG}", "Lower SIG normalization", 10, 1., 1.e3);
  RooRealVar yieldUpperSIG("#color[6]{upper SIG}", "Upper SIG normalization", 10, 1., 1.e3);
  RooRealVar yieldUpperSB( "#color[4]{upper SB}",  "Upper SB normalization",  10, 1., 1.e3);
  RooExtendPdf model_ext( "model_ext", "extended p.d.f", model,      yieldLowerSB );
  RooExtendPdf model_ext2("model_ext2","extended p.d.f", model_ext,  yieldLowerSIG);
  RooExtendPdf model_ext3("model_ext3","extended p.d.f", model_ext2, yieldUpperSIG);
  RooExtendPdf model_ext4("model_ext4","extended p.d.f", model_ext3, yieldUpperSB );
  // Fit data in the lowerSB (not both sidebands), fixing all shape parameters, 
  // and letting only one parameter free, that is yieldLowerSB 
  RooFitResult* r = model_ext.fitTo(sbObs,ConditionalObservables(RooArgSet(massVhad)),Extended(kTRUE),Range("lowerSB"),Save(1),PrintLevel(-1));
  // Calculate integral of the model in every region 
  RooAbsReal* nSIG1 = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* nSIG2 = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("upperSIG"));
  RooAbsReal* nSB1  = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB"));
  RooAbsReal* nSB2  = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("upperSB"));
  Double_t scale1   = nSIG1->getVal()/nSB1->getVal(); // scale from lower sideband to lower signal region
  Double_t scale2   = nSIG2->getVal()/nSB1->getVal(); // scale from lower sideband to upper signal region
  Double_t scale3   =  nSB2->getVal()/nSB1->getVal(); // scale from lower sideband to upper sideband
  Double_t bkgYield       = yieldLowerSB.getVal()   * scale1; 
  Double_t bkgYield_error = yieldLowerSB.getError() * scale1;
  cout << "Yield in signal region:  " << bkgYield << " +/- " << bkgYield_error << endl;
  yieldLowerSIG.setVal(   bkgYield      );
  yieldLowerSIG.setError( bkgYield_error);
  yieldUpperSIG.setVal(   yieldLowerSB.getVal()   * scale2 );
  yieldUpperSIG.setError( yieldLowerSB.getError() * scale2 );
  yieldUpperSB.setVal(    yieldLowerSB.getVal()   * scale3 );
  yieldUpperSB.setError(  yieldLowerSB.getError() * scale3 );
 
  // Prepare beautiful plot
  RooBinning xbins(40,30,230);
  RooPlot *plot = massVhad.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  plot->SetAxisRange(45.,235.,"X");
  allMC.plotOn(plot,Binning(xbins),DrawOption("B"),FillColor(15),FillStyle(1001),LineColor(kWhite));
  sbObs.plotOn(plot,Binning(xbins));
  model_ext.plotOn(plot,LineStyle(kSolid),LineColor(kBlue));
  model_ext.plotOn(plot,LineStyle(kDashed),LineColor(kRed),     Range("lowerSIG"));
  model_ext.plotOn(plot,LineStyle(kDashed),LineColor(kMagenta), Range("upperSIG"));
  model_ext.plotOn(plot,LineStyle(kDashed),LineColor(kBlue),    Range("upperSB"));
  model_ext4.paramOn(plot,Layout(0.4,0.99,0.9));

  TCanvas *canvas1 = new TCanvas("canvas","",700,700);
  canvas1->cd();
  gPad->SetGridx();
  plot->Draw();
  canvas1->SaveAs(Form("fitPrunedMass%s.eps",key.c_str()));

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
  RooRealVar s0("s0","slope of the exp0",500.,1.,1.e3);
  RooRealVar s1("s1","slope of the exp1",500.,1.,1.e3);
  RooRealVar s2("s2","slope of the exp2",500.,1.,1.e3);
  RooRealVar a0("a0","parameter of exp0",0.1 ,0.,1.);
  RooRealVar a1("a1","parameter of exp1",0.1 ,0.,1.);
  RooRealVar a2("a2","parameter of exp2",0.1 ,0.,1.);
  RooExpTailPdf       nsBkg_pdf("nsBkg_pdf", "fit bkg  in nominal  region",   candMass,s0,a0);
  RooExpTailPdf       sbBkg_pdf("sbBkg_pdf", "fit bkg  in sideband region",   candMass,s1,a1);
  RooExpTailPdf       sbObs_pdf("sbObs_pdf", "fit data in sideband region",   candMass,s2,a2);
  RooAlpha4ExpTailPdf alpha_pdf("alpha_pdf", "alpha ratio",                   candMass,s0,a0,s1,a1);
  RooProdPdf             ZZ_bkg("ZZ_bkg", "Data-driven bakground estimation", alpha_pdf, sbObs_pdf);

  // Fit 1) Dominant backgrounds in lowerSIG
  // Fit 2) Dominant backgrounds in lowerSB and upperSB
  // Fit 3) Blinded data in lowerSB and upperSB
  RooDataSet* sbBkg = (RooDataSet*) allMC.reduce(variables,"MC==0 && (region==0||region==3)");
  RooDataSet* nsBkg = (RooDataSet*) allMC.reduce(variables,"MC==0 &&  region==1");
  RooCategory reg("reg","reg");
  reg.defineType("nsMC");
  reg.defineType("sbMC");
  reg.defineType("sbDA");
  RooDataSet bigSampleNoW("bigSample","bigSample", variables, Index(reg), Import("nsMC",*nsBkg), Import("sbMC",*sbBkg), Import("sbDA",sbObs));
  RooRealVar* w2 = (RooRealVar*) bigSampleNoW.addColumn(wFunc);
  RooDataSet bigSample(bigSampleNoW.GetName(), bigSampleNoW.GetTitle(), &bigSampleNoW, *bigSampleNoW.get(),0,w2->GetName());

  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(nsBkg_pdf,sbBkg_pdf,sbObs_pdf), reg); 
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Minimizer("Minuit"), PrintLevel(-1));

  // Generate data for alpha
  RooDataSet *alpha = alpha_pdf.generate(candMass,1.e6); 
  alpha->SetName("alpha");

  RooBinning xbins2(20,600,2600);
  RooPlot *plot1 = candMass.frame(Title("#bf{MC SIG}"));
  RooPlot *plot2 = candMass.frame(Title("#bf{MC SB}"));
  RooPlot *plot3 = candMass.frame(Title("#bf{MC SIG / MC SB}"));
  RooPlot *plot4 = candMass.frame(Title("#bf{Data SB}"));
  plot1->SetAxisRange(600.,2600.,"X");
  plot2->SetAxisRange(600.,2600.,"X");
  plot3->SetAxisRange(600.,2600.,"X");
  plot4->SetAxisRange(600.,2600.,"X");
  nsBkg->plotOn(plot1,Binning(xbins2));
  nsBkg->statOn(plot1,Layout(0.50,0.99,0.75)) ;
  nsBkg_pdf.plotOn( plot1,Binning(xbins2));
  nsBkg_pdf.plotOn( plot1,VisualizeError(*fitres,2),LineColor(kBlue),FillStyle(3002),FillColor(kBlack));
  nsBkg_pdf.paramOn(plot1,Layout(0.50,0.99,0.9)) ;
  sbBkg->plotOn(plot2,Binning(xbins2));
  sbBkg->statOn(plot2,Layout(0.50,0.99,0.75)) ;
  sbBkg_pdf.plotOn( plot2,Binning(xbins2));
  sbBkg_pdf.plotOn( plot2,VisualizeError(*fitres,2),LineColor(kBlue),FillStyle(3002),FillColor(kBlack));
  sbBkg_pdf.paramOn(plot2,Layout(0.50,0.99,0.9)) ;
  alpha->plotOn(plot3,Binning(xbins2));
  alpha_pdf.plotOn( plot3,Binning(xbins2));
  alpha_pdf.plotOn( plot3,VisualizeError(*fitres,1,kFALSE),LineColor(kBlue),FillStyle(3002),FillColor(kBlack));
  alpha_pdf.paramOn(plot3,Layout(0.50,0.99,0.9)) ;
  sbObs.plotOn(plot4,Binning(xbins2));
  sbObs.statOn(plot4,Layout(0.50,0.99,0.75)) ;
  sbObs_pdf.plotOn( plot4,Binning(xbins2));
  sbObs_pdf.plotOn( plot4,VisualizeError(*fitres,2),LineColor(kBlue),FillStyle(3002),FillColor(kBlack));
  sbObs_pdf.paramOn(plot4,Layout(0.50,0.99,0.9)) ;

  TCanvas *canvas2 = new TCanvas("canvas2","",700,700);
  canvas2->Divide(2,2);
  canvas2->cd(1); gPad->SetGridx(); plot1->Draw();
  canvas2->cd(2); gPad->SetGridx(); plot2->Draw();
  canvas2->cd(3); gPad->SetGridx(); plot3->Draw();
  canvas2->cd(4); gPad->SetGridx(); plot4->Draw();
  canvas2->SaveAs(Form("alphaFits%s.eps",key.c_str()));

/////////////////////////////////////////////////////////////////////////////
//        _____             _ _                _               _           //
//       / ____|           (_) |              | |             | |          //
//      | (___   __ _ _ __  _| |_ _   _    ___| |__   ___  ___| | __       //
//       \___ \ / _` | '_ \| | __| | | |  / __| '_ \ / _ \/ __| |/ /       //
//       ____) | (_| | | | | | |_| |_| | | (__| | | |  __/ (__|   <        //
//      |_____/ \__,_|_| |_|_|\__|\__, |  \___|_| |_|\___|\___|_|\_\       //     
//                                 __/ |                                   //
//                                |___/                                    // 
/////////////////////////////////////////////////////////////////////////////

  // Unblind last runs, fit, and generate pseudodata from the obtained PDF
  TCut lastRuns = "run>=259626"; 
  RooDataSet nsObs("nsObs","nsObs", RooArgSet(massVhad,candMass,tau21,lep,run,region,totalWeight),Cut(lastRuns+lowerSIG), Import(treeData));

  RooRealVar s5("s5","slope of the exp5",500.,1.,1.e3);
  RooRealVar a5("a5","parameter of exp5",0.1 ,0.,1.);
  RooExpTailPdf nsObs_pdf("nsObs_pdf", "fit data  in signal region", candMass,s5,a5);
  nsObs_pdf.fitTo(nsObs, Range("lowerSIG"), PrintLevel(-1));
  RooDataSet *pseudoData = nsObs_pdf.generate(candMass, (int)bkgYield );
  pseudoData->SetName("pseudoData");

  RooPlot *plot5 = candMass.frame(Title("#bf{Pseudo-data and background prediction}"));
  plot5->SetAxisRange(600.,2600.,"X");
  pseudoData->plotOn(plot5,Binning(xbins2));
  pseudoData->statOn(plot5,Layout(0.55,0.99,0.5)) ;
  ZZ_bkg.plotOn( plot5,Binning(xbins2));
  ZZ_bkg.plotOn( plot5,VisualizeError(*fitres,2,kFALSE),LineColor(kBlue),FillStyle(3002),FillColor(kBlack));
  ZZ_bkg.paramOn(plot5,Layout(0.55,0.99,0.9)) ;
  TCanvas *canvas3 = new TCanvas("canvas3","",700,700);
  canvas3->cd();
  gPad->SetGridx();
  plot5->Draw();
  canvas3->SaveAs(Form("bkgFinalPrediction%s.eps",key.c_str()));

}
