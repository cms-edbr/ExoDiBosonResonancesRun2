//
//        Require pre-compiled PDFs library  
//
//        Usage:
// 
//        root -l 
//
//        gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
//
//        .x alphaMethod.C("EHP")
//        .x alphaMethod.C("ELP")
//        .x alphaMethod.C("MHP")
//        .x alphaMethod.C("MLP")

void alphaMethod(std::string key)
{
  std::map<std::string, std::string> selection;
  selection["EHP"] = "lep<12 && tau21<0.5";
  selection["MHP"] = "lep>12 && tau21<0.5";
  selection["ELP"] = "lep<12 && tau21>0.5 && tau21<0.75";
  selection["MLP"] = "lep>12 && tau21>0.5 && tau21<0.75";
  TCut selectedCategory = selection[key].c_str();

  RooRealVar candMass("candMass","M_{ZZ}", 500.,2500., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,  50., 110., "GeV");
  RooRealVar tau21("tau21","tau21",         0.,     1.);
  RooRealVar lep("lep","lep",               10,     15);
  RooRealVar lumiWeight("lumiWeight", "pure weight", 0., 10.);

  TCut sideband = "massVhad<70." + selectedCategory;
  TCut nomselec = "massVhad>70." + selectedCategory;

  massVhad.setRange("signalRegion",   70., 110.);
  massVhad.setRange("sidebandRegion", 50.,  70.);

  //*******************************************************//
  //                                                       //     
  //                   Get Alpha Ratio                     //
  //                                                       //     
  //*******************************************************//

  TFile *mcdata = TFile::Open("Ttrees/treeEDBR_DYJetsToLL_HT-100toInf_PHYS14.root");
  TTree *treeMC;
  mcdata->GetObject("treeDumper/EDBRCandidates",treeMC);

  // Nominal selection
  RooDataSet nsBkg("nsBkg","nsBkg",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(nomselec),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeMC));

   // Sideband selection
  RooDataSet sbBkg("sbBkg","sbBkg",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(sideband),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeMC));

  // Simultaneous Fit and alpha ratio 
  RooRealVar s0("s0","slope of the exp0",500.,1.,1.e3);
  RooRealVar s1("s1","slope of the exp1",400.,1.,1.e3);
  RooRealVar a0("a0","parameter of exp0",0.1,-1.,1.);
  RooRealVar a1("a1","parameter of exp1",0.1,-1.,1.);
  RooExpTailPdf nsBkg_pdf("nsBkg_pdf","fit bkg in nominal region", candMass,s0,a0);
  RooExpTailPdf sbBkg_pdf("sbBkg_pdf","fit bkg in sideband region",candMass,s1,a1);
  nsBkg_pdf.fitTo(nsBkg);
  sbBkg_pdf.fitTo(sbBkg);
  RooAlpha4ExpTailPdf alpha_pdf("alpha_pdf","fiting alpha ratio",candMass,s0,a0,s1,a1);

  //*******************************************************//
  //                                                       //     
  //                   Get Normalization                   //
  //                                                       //     
  //*******************************************************//

  TFile *data = TFile::Open("Ttrees/treeEDBR_PseudoData.root");
  TTree *treeData;
  data->GetObject("treeDumper/EDBRCandidates",treeData);

  RooDataSet data_sb("data_sb","data_sb",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(sideband),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeData));

  // FIXME to subtract subdominant backgrounds

  // Error Function * Exponential
  RooRealVar c("c","slope of the exp",-0.5,-10.,0.);
  RooRealVar offset("offset","offset of the erf",1.,0.,10.);
  RooRealVar width("width","width of the erf",1.,0.,10.);
  RooErfExpPdf mj_pdf("mj_pdf","fiting mj spectrum",massVhad,c,offset,width);
  RooRealVar normaliza("normaliza","number of events",1,0.1,1.e4);
  RooExtendPdf mj_pdf_ext("mj_pdf_ext","extended p.d.f", mj_pdf, normaliza);

  // Do the fit
  RooFitResult *rf = mj_pdf_ext.fitTo(data_sb, RooFit::Extended(kTRUE), RooFit::Range("sidebandRegion"), RooFit::Save(kTRUE));

  // Extrapolate PDF to signal window 
  RooProduct unNormPdf("fitted Function", "fitted Function", RooArgSet(mj_pdf_ext));
  TF1 * f1 = unNormPdf.asTF(RooArgList(massVhad), RooArgList(*mj_pdf_ext.getParameters(RooArgSet(massVhad))) );
  //f1->DrawClone();
  Double_t scale = f1->Integral(70.,110.)/f1->Integral(50.,70.);
  RooRealVar numberEvents("numberEvents","Zjets normalization in signal region",normaliza.getVal()*scale,0.1,1.e4);
  numberEvents.setError(normaliza.getError()*scale);

  //*******************************************************//
  //                                                       //     
  //           Get M_ZZ distribution in sideband           //
  //                                                       //     
  //*******************************************************//

  RooRealVar s2("s2","slope of the exp2",500.,1.,1.e3);
  RooRealVar a2("a2","parameter of exp2",0.1,-1.,1.);
  RooExpTailPdf data_sb_pdf("data_sb_pdf","fit data in sideband region", candMass,s2,a2);

  // Fit of M_ZZ distribution 
  data_sb_pdf.fitTo(data_sb);

  //*******************************************************//
  //                                                       //     
  //             Get M_ZZ pdf for signal region            //
  //                                                       //     
  //*******************************************************//

  RooProdPdf M_ZZ_pdf("M_ZZ_pdf","M_ZZ_pdf", alpha_pdf, data_sb_pdf);

  //*******************************************************//
  //                                                       //     
  //      Extended pdf with explicit normalization         //
  //                                                       //     
  //*******************************************************//

  RooExtendPdf M_ZZ_pdf_renormalized("M_ZZ_pdf_renormalized","Extended p.d.f", M_ZZ_pdf, numberEvents);

  //*******************************************************//
  //                                                       //     
  //                      Unblinding                       //
  //                                                       //     
  //*******************************************************//

  RooDataSet full_data("full_data","full_data",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(selectedCategory),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeData));

  RooPlot* frame1 = candMass.frame(RooFit::Title("CMS Preliminary #sqrt{s} = 13 TeV") );
  full_data.plotOn(frame1); 
  M_ZZ_pdf_renormalized.plotOn(frame1,RooFit::LineColor(kRed)); 
  frame1->Draw();

  Double_t expectedEvents       = ((RooRealVar*)(*M_ZZ_pdf_renormalized.getParameters(RooArgSet(candMass))).find("numberEvents"))->getVal();
  Double_t expectedEvents_error = ((RooRealVar*)(*M_ZZ_pdf_renormalized.getParameters(RooArgSet(candMass))).find("numberEvents"))->getError();

  cout << endl << "***************************************************************" << endl << endl;
  cout << "scale = " << scale  << endl;
  cout << endl << "***************************************************************" << endl << endl;

  cout << endl << "***************************************************************" << endl << endl;
  cout << "Expected number of events in signal region = " << expectedEvents  << " +- " << expectedEvents_error << endl;
  cout << endl << "***************************************************************" << endl << endl;

  cout << endl << "***************************************************************" << endl << endl;
  cout << "Real number of events in signal region = " << full_data.sumEntries() - data_sb.sumEntries() << endl;
  cout << endl << "***************************************************************" << endl << endl;

}
