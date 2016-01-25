//
//        Requires pre-compiled PDFs library  
//
//        Requires ROOT 6.04/02 (or above) to take advantage of R__LOAD_LIBRARY
//        https://root.cern.ch/root/html604/notes/release-notes.html#interpreter  
//
//        Examples of usage:
// 
//        root -b -q 'shapeAnalysisPlots.C("AHP")'
//        root -b -q 'shapeAnalysisPlots.C("ALP")'
//        root -b -q 'shapeAnalysisPlots.C("EHP")'
//        root -b -q 'shapeAnalysisPlots.C("ELP")'
//        root -b -q 'shapeAnalysisPlots.C("MHP")'
//        root -b -q 'shapeAnalysisPlots.C("MLP")'
//

R__LOAD_LIBRARY(74X/PDFs/HWWLVJRooPdfs_cxx.so)

void shapeAnalysisPlots(std::string key)
{
  using namespace RooFit;

  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);

  RooRealVar candMass("candMass","M_{VZ}",            500., 9800., "GeV");
  RooRealVar massVhad("massVhad","pruned m_{jet}",     20.,  220., "GeV");
  RooRealVar tau21("tau21","tau21",                     0.,  0.75       );
  RooRealVar lep("lep","lep",                           10,    15       );
  RooRealVar totalWeight("totalWeight", "total weight", 0.,    10.      );
  RooArgSet variables(candMass,massVhad,tau21,lep,totalWeight);

  massVhad.setRange("lowerSB",      20.,   65.);
  massVhad.setRange("lowerSIG",     65.,  105.);
  massVhad.setRange("upperSIG",    105.,  135.);
  massVhad.setRange("upperSB",     135.,  220.);

  std::map<std::string, std::string> selection;
  selection["AHP"] = "tau21<0.45";
  selection["ALP"] = "tau21>0.45";
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

  std::map<std::string, std::string> legTitle;
  legTitle["ENP"]="electron channel";
  legTitle["EHP"]="electron channel high purity";
  legTitle["ELP"]="electron channel low purity";
  legTitle["MNP"]="muon channel";
  legTitle["MHP"]="muon channel high purity";
  legTitle["MLP"]="muon channel low purity";
  legTitle["AHP"]="Both channels high purity";
  legTitle["ALP"]="Both channels low purity";

  //*******************************************************//
  //                                                       //     
  //                      Input files                      //
  //                                                       //     
  //*******************************************************//

  TChain treeData("treeDumper/EDBRCandidates");
  TChain treeMC1( "treeDumper/EDBRCandidates");
  TChain treeMC2( "treeDumper/EDBRCandidates");
  std::map<Int_t, std::string> inputFile;
  std::string lepton_scale;

  if( key[0]=='E' or key[0]=='A' ){ 
      treeData.Add(     "trees/treeEDBR_SingleElectron1.root"             ); 
      treeData.Add(     "trees/treeEDBR_SingleElectron2.root"             ); 
      treeMC2.Add(      "trees/treeEDBR_TT_el.root"                       );
      treeMC2.Add(      "trees/treeEDBR_WW_el.root"                       );
      treeMC2.Add(      "trees/treeEDBR_WZ_el.root"                       );
      treeMC2.Add(      "trees/treeEDBR_ZZ_el.root"                       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT100to200_el.root"    );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT200to400_el.root"    );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT400to600_el.root"    );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT600toInf_el.root"    );
  }
  if( key[0]=='M' or key[0]=='A' ){
      treeData.Add(     "trees/treeEDBR_SingleMuon1.root"                 ); 
      treeData.Add(     "trees/treeEDBR_SingleMuon2.root"                 ); 
      treeMC2.Add(      "trees/treeEDBR_TT_mu.root"                       );
      treeMC2.Add(      "trees/treeEDBR_WW_mu.root"                       );
      treeMC2.Add(      "trees/treeEDBR_WZ_mu.root"                       );
      treeMC2.Add(      "trees/treeEDBR_ZZ_mu.root"                       );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT100to200_mu.root"    );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT200to400_mu.root"    );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT400to600_mu.root"    );
      treeMC1.Add(      "trees/treeEDBR_DYJetsToLL_HT600toInf_mu.root"    );
  }

  // datasets to host data in sideband
  RooDataSet sbObs("sbObs","sbObs", variables, Cut(allSB),    Import(treeData));
  RooDataSet nsObs("sbObs","sbObs", variables, Cut(lowerSIG), Import(treeData));

  // MC datasets
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC1));
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC2));
  RooRealVar coef("coef", "coef", bkg2.sumEntries()/bkg1.sumEntries(),0.,1.);
  coef.setConstant(true);
  RooCategory MC("MC","MC");
  MC.defineType(   "dominant");
  MC.defineType("subdominant");
  RooDataSet allMC("allMC","allMC", variables, WeightVar(totalWeight), Index(MC), Import("dominant",bkg1), Import("subdominant",bkg2));


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
  RooRealVar offset2("offset2","offset of the erf",    10.0,   1.,  200.);
  RooRealVar width1("width1",  "width of the erf",     50.0,   1.,  200.);
  RooRealVar width2("width2",  "width of the erf",     50.0,   1.,  200.);
  RooErfExpPdf model1("model1","fiting mj spectrum1",massVhad,c1,offset1,width1);
  RooErfExpPdf model2("model2","fiting mj spectrum2",massVhad,c2,offset2,width2);
  RooFitResult *rf1 = model1.fitTo(bkg1, Save(1), PrintLevel(-1));
  RooFitResult *rf2 = model2.fitTo(bkg2, Save(1), PrintLevel(-1));
  // Final background model
  RooAddPdf model("model","model",RooArgList(model2,model1),coef);
  c1.setConstant(true);
  c2.setConstant(true);
  offset1.setConstant(true);
  offset2.setConstant(true);
  width1.setConstant(true);
  width2.setConstant(true);
  // Extended model
  RooRealVar yieldLowerSB( "lower SB",  "Lower SB normalization",  10, 0., 1.e3);
  RooExtendPdf model_ext( "model_ext", "extended p.d.f",   model,  yieldLowerSB);
  model_ext.fitTo(sbObs,ConditionalObservables(RooArgSet(massVhad)),Extended(kTRUE),Range("lowerSB"),PrintLevel(-1));

  // Calculate integral of the model
  RooAbsReal* nSIG = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* nSB  = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB"));
  // scale from lowerSB to lowerSIG
  RooFormulaVar lowerSIGyield("lowerSIGyield","extrapolation to lowerSIG","(@0/@1)*@2",RooArgList(*nSIG,*nSB,yieldLowerSB));
  Double_t bkgYield       =     lowerSIGyield.getVal(); 
  Double_t bkgYield_error = 1 + lowerSIGyield.getPropagatedError(*rf1)/bkgYield;
  RooRealVar ZZ_bkg_norm("#color[2]{bkg norm}","expected yield in lowerSIG",bkgYield,0.,1.e4);
  ZZ_bkg_norm.setError( lowerSIGyield.getPropagatedError(*rf1) );
 
  // Prepare beautiful plot
  RooBinning xbins(40,20,220);
  RooPlot *plot = massVhad.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  plot->SetAxisRange(20.,220.,"X");
  allMC.plotOn(    plot, Name("allmc"), Binning(xbins),DrawOption("B"),LineColor(0),FillColor(kAzure-9));
  //nsObs.plotOn(    plot, Name("sigDa"), Binning(xbins),MarkerColor(kRed));
  sbObs.plotOn(    plot, Name("sbDa"),  Binning(xbins));
  model_ext.plotOn(plot, Name("lowSBmc"), LineStyle(kSolid),LineColor(kBlue));
  model_ext.plotOn(plot, Name("lowSIGd"), LineStyle(kSolid),LineColor(kRed),Range("lowerSIG"));
  //model_ext.plotOn(plot, Name("uppSIGd"), LineStyle(kDashed),LineColor(kMagenta), Range("upperSIG"));
  //model_ext.plotOn(plot, Name("uppSBmc"), LineStyle(kDashed),LineColor(kBlue),    Range("upperSB"));

  TCanvas *canvas1 = new TCanvas("canvas","",1200,600);
  canvas1->Divide(2,1,0.001,0.001);
  canvas1->cd(1);
  gPad->SetGridx();
  plot->SetMinimum(0.5 );
  plot->SetMaximum(130.);
  plot->GetYaxis()->SetTitleSize(0.05); plot->GetYaxis()->SetTitleOffset(0.85);
  plot->GetXaxis()->SetTitleSize(0.05); plot->GetXaxis()->SetTitleOffset(0.85);
  plot->Draw();

  TLegend *leg1 = new TLegend(0.4,0.55,0.9,0.9);
  leg1->SetHeader(legTitle[key].c_str());
  //leg1->AddEntry("sigDa",  "Data in signal region",         "ep");
  leg1->AddEntry("sbDa",   "Data in sideband regions",      "ep");
  leg1->AddEntry("allmc",  "Background MC simulation",       "f");
  leg1->AddEntry("lowSBmc","Fit data in lower sideband",     "l");
  leg1->AddEntry("lowSIGd","Extrapolation to signal region", "l");
  leg1->Draw();
  TLegendEntry *header1 = (TLegendEntry*)leg1->GetListOfPrimitives()->First();
  header1->SetTextAlign(22);
  header1->SetTextColor(1);
  header1->SetTextSize(.04);

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
  RooRealVar s0("s0","slope of the exp0",500,1.,1.e3);
  RooRealVar s1("s1","slope of the exp1",500,1.,1.e3);
  RooRealVar s2("s2","slope of the exp2",500,1.,1.e3);
  RooRealVar a0("a0","parameter of exp0",0.1 ,0.,10.);
  RooRealVar a1("a1","parameter of exp1",0.1 ,0.,10.);
  RooRealVar a2("a2","parameter of exp2",0.1 ,0.,10.);
  RooExpTailPdf       nsBkg_pdf("nsBkg_pdf", "fit bkg  in nominal  region",   candMass,s0,a0);
  RooExpTailPdf       sbBkg_pdf("sbBkg_pdf", "fit bkg  in sideband region",   candMass,s1,a1);
  RooExpTailPdf       sbObs_pdf("sbObs_pdf", "fit data in sideband region",   candMass,s2,a2);
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
  RooDataSet bigSample("bigSample","bigSample", variables, WeightVar(totalWeight), Index(reg), Import("nsMC",nsBkg), Import("sbMC",sbBkg), Import("sbDA",sbObs));
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(nsBkg_pdf,sbBkg_pdf,sbObs_pdf), reg); 
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), SumW2Error(kTRUE), PrintLevel(-1));

  // Generate data for alpha
  RooDataSet *alpha = alpha_pdf.generate(candMass,1.e6); 
  alpha->SetName("alpha");

  RooBinning xbins2(20,500,2500);
  RooPlot *plot1 = candMass.frame(Title("#bf{MC SIG}"));
  RooPlot *plot2 = candMass.frame(Title("#bf{MC SB}"));
  RooPlot *plot3 = candMass.frame(Title("#bf{MC SIG / MC SB}"));
  RooPlot *plot4 = candMass.frame(Title("#bf{Data SB}"));
  plot1->SetAxisRange(500.,2500.,"X");
  plot2->SetAxisRange(500.,2500.,"X");
  plot3->SetAxisRange(500.,2500.,"X");
  plot4->SetAxisRange(500.,2500.,"X");

  nsBkg.plotOn(plot1,Binning(xbins2),RooFit::Invisible());
  nsBkg_pdf.plotOn( plot1,VisualizeError(*fitres,1),FillStyle(1001),FillColor(kYellow-7));
  nsBkg.plotOn(plot1,Binning(xbins2));
  nsBkg.statOn(plot1,Layout(0.50,0.99,0.75)) ;
  nsBkg_pdf.plotOn( plot1,Binning(xbins2),LineColor(kRed));
  nsBkg_pdf.paramOn(plot1,Layout(0.50,0.99,0.9),LineColor(kRed)) ;
  plot1->GetXaxis()->SetTitleSize(0.05);
  plot1->GetXaxis()->SetTitleOffset(0.85);
  plot1->GetYaxis()->SetTitleSize(0.05);
  plot1->GetYaxis()->SetTitleOffset(0.85);
  plot1->SetMinimum(0.5);   
  plot1->SetMaximum(550);

  sbBkg.plotOn(plot2,Binning(xbins2),RooFit::Invisible());
  sbBkg_pdf.plotOn( plot2,VisualizeError(*fitres,1),FillStyle(1001),FillColor(kYellow-7));
  sbBkg.plotOn(plot2,Binning(xbins2));
  sbBkg.statOn(plot2,Layout(0.50,0.99,0.75)) ;
  sbBkg_pdf.plotOn( plot2,Binning(xbins2),LineColor(kRed));
  sbBkg_pdf.paramOn(plot2,Layout(0.50,0.99,0.9)) ;
  plot2->GetYaxis()->SetTitleSize(0.05);
  plot2->GetYaxis()->SetTitleOffset(0.85);
  plot2->GetXaxis()->SetTitleSize(0.05);
  plot2->GetXaxis()->SetTitleOffset(0.85);
  plot2->SetMinimum(0.5);   
  plot2->SetMaximum(550);

  alpha->plotOn(plot3,Binning(xbins2),RooFit::Invisible());
  alpha_pdf.plotOn(plot3,VisualizeError(*fitres,1,kFALSE),FillStyle(1001),FillColor(kYellow-7));
  alpha_pdf.plotOn( plot3,Binning(xbins2),LineColor(kRed));
  alpha_pdf.paramOn(plot3,Layout(0.50,0.99,0.9)) ;
  plot3->GetYaxis()->SetTitle("Arbitrary units");
  plot3->GetYaxis()->SetNdivisions(2);
  plot3->GetYaxis()->SetTitleSize(0.05);
  plot3->GetYaxis()->SetTitleOffset(0.85);
  plot3->GetXaxis()->SetTitleSize(0.05);
  plot3->GetXaxis()->SetTitleOffset(0.85);
  plot3->SetMinimum(-50e3); 
  plot3->SetMaximum(150e3);

  sbObs.plotOn(plot4,Binning(xbins2),RooFit::Invisible());
  sbObs_pdf.plotOn( plot4,VisualizeError(*fitres,1),LineColor(kBlue),FillStyle(1001),FillColor(kYellow-7));
  sbObs.plotOn(plot4,Binning(xbins2));
  sbObs.statOn(plot4,Layout(0.50,0.99,0.75)) ;
  sbObs_pdf.plotOn( plot4,Binning(xbins2),LineColor(kRed));
  sbObs_pdf.paramOn(plot4,Layout(0.50,0.99,0.9)) ;
  plot4->GetYaxis()->SetTitleSize(0.05);
  plot4->GetYaxis()->SetTitleOffset(0.85);
  plot4->GetXaxis()->SetTitleSize(0.05);
  plot4->GetXaxis()->SetTitleOffset(0.85);
  plot4->SetMinimum(0.5);   
  plot4->SetMaximum(550);

  TCanvas *canvas2 = new TCanvas("canvas2","",700,700);
  canvas2->Divide(2,2);
  canvas2->cd(1); gPad->SetLogy(); gPad->SetGridx(); plot1->Draw();
  canvas2->cd(2); gPad->SetLogy(); gPad->SetGridx(); plot2->Draw();
  canvas2->cd(3);                  gPad->SetGridx(); plot3->Draw();
  canvas2->cd(4); gPad->SetLogy(); gPad->SetGridx(); plot4->Draw();
  canvas2->SaveAs(Form("otherPlots/alphaFits%s.eps",key.c_str()));

  RooExtendPdf ZZ_bkg_ext( "ZZ_bkg_ext", "extended p.d.f",  ZZ_bkg, ZZ_bkg_norm);
  RooDataSet allMCns("allMCns","allMCns", variables, Cut(lowerSIG), WeightVar(totalWeight), Index(MC), Import("dominant",bkg1), Import("subdominant",bkg2));

  RooBinning xbins3(30,500,3500);
  RooPlot *plot5 = candMass.frame(Title("#bf{CMS} Preliminary     #sqrt{s}=13 TeV       #int L = 2.6 fb^{-1}"));
  plot5->SetAxisRange(500.,3500.,"X");
  allMCns.plotOn(plot5, Name("MC"), Binning(xbins3),DrawOption("B"),LineColor(0),FillColor(kAzure-9));
  //nsObs.plotOn(plot5,Binning(xbins3),RooFit::Invisible());
  const RooCmdArg goodNorm = Normalization(1.0,RooAbsReal::RelativeExpected);
  ZZ_bkg_ext.plotOn( plot5, Name("1sigma"), goodNorm, LineColor(kBlack), VisualizeError(*fitres,1,kFALSE),FillStyle(1001),FillColor(kYellow-7));
  ZZ_bkg_ext.plotOn( plot5, Name("Bkg"),    goodNorm, LineColor(kRed));
  //nsObs.plotOn(plot5, Name("Data"), Binning(xbins3));
  canvas1->cd(2);
  plot5->SetMinimum(0.5);
  plot5->SetMaximum(550.);
  plot5->GetYaxis()->SetTitleSize(0.05); plot5->GetYaxis()->SetTitleOffset(0.85);
  plot5->GetXaxis()->SetTitleSize(0.05); plot5->GetXaxis()->SetTitleOffset(0.85);
  gPad->SetGridx();
  gPad->SetLogy();
  plot5->Draw();

  TLegend *leg2 = new TLegend(0.4,0.55,0.9,0.9);
  leg2->SetHeader(legTitle[key].c_str());
  leg2->AddEntry("Data",  "Data in signal region","lep");
  leg2->AddEntry("MC",  "Background MC simulation","f");
  leg2->AddEntry("Bkg",   "Estimated background","l");
  leg2->AddEntry("1sigma","Estimation #pm 1#sigma", "f");
  //leg2->AddEntry("2sigma","Estimation #pm 2#sigma", "f");
  leg2->Draw();
  TLegendEntry *header2 = (TLegendEntry*)leg2->GetListOfPrimitives()->First();
  header2->SetTextAlign(22);
  header2->SetTextColor(1);
  header2->SetTextSize(.04);
  
  canvas1->SaveAs(Form("otherPlots/bkgFinalPrediction%s.eps",key.c_str()));

  cout << "Estimated background = " << bkgYield << " +/- " << lowerSIGyield.getPropagatedError(*rf1) << endl;
  cout << "Simulated background = " << allMCns.sumEntries() << endl;
  cout << "True value = " << nsObs.numEntries() << endl;

}
