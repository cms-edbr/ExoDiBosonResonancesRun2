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
  std::map<std::string, std::string> outFile;
  outFile["EHP"]="dataDrivenEHP.pdf";
  outFile["ELP"]="dataDrivenELP.pdf";
  outFile["MHP"]="dataDrivenMHP.pdf";
  outFile["MLP"]="dataDrivenMLP.pdf";

  std::map<std::string, std::string> legTitle;
  legTitle["EHP"]="electron channel high purity";
  legTitle["ELP"]="electron channel low purity";
  legTitle["MHP"]="muon channel high purity";
  legTitle["MLP"]="muon channel low purity";

  std::map<std::string, std::string> selection;
  selection["EHP"] = "lep<12 && tau21<0.5";
  selection["MHP"] = "lep>12 && tau21<0.5";
  selection["ELP"] = "lep<12 && tau21>0.5 && tau21<0.75";
  selection["MLP"] = "lep>12 && tau21>0.5 && tau21<0.75";
  TCut selectedCategory = selection[key].c_str();

  RooRealVar candMass("candMass","M_{ZZ}", 600.,2600., "GeV");
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
  //                   Get Normalization                   //
  //                                                       //     
  //*******************************************************//

  TFile *data = TFile::Open("Ttrees/treeEDBR_PseudoData.root");
  TTree *treeData;
  data->GetObject("treeDumper/EDBRCandidates",treeData);

  RooDataSet sbDat("sbDat","sbDat",RooArgSet(massVhad,tau21,lep,lumiWeight),RooFit::Cut(sideband),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeData));

  // FIXME to subtract subdominant backgrounds

  // Error Function * Exponential
  RooRealVar c("c","slope of the exp",-0.5,-10.,0.);
  RooRealVar offset("offset","offset of the erf",1.,0.,10.);
  RooRealVar width("width","width of the erf",1.,0.,10.);
  RooErfExpPdf mj_pdf("mj_pdf","fiting mj spectrum",massVhad,c,offset,width);
  RooRealVar integral("integral","number of events",1,0.1,1.e4);
  RooExtendPdf mj_pdf_ext("mj_pdf_ext","extended p.d.f", mj_pdf, integral);
  mj_pdf_ext.fitTo(sbDat, RooFit::Extended(kTRUE), RooFit::Range("sidebandRegion"));

  // Extrapolate PDF to signal window 
  RooAbsReal* n_signalRegion = mj_pdf.createIntegral(massVhad,RooFit::NormSet(massVhad),RooFit::Range("signalRegion"));
  RooAbsReal* n_contrlRegion = mj_pdf.createIntegral(massVhad,RooFit::NormSet(massVhad),RooFit::Range("sidebandRegion"));
  Double_t scale = n_signalRegion->getVal()/n_contrlRegion->getVal();
  RooRealVar numberEvents("numberEvents","Zjets normalization in signal region",integral.getVal()*scale,0.1,1.e4);
  numberEvents.setError(integral.getError()*scale);

  //*******************************************************//
  //                                                       //     
  //      Simultaneous fit and alpha ratio                 //
  //                                                       //     
  //*******************************************************//

  TFile *mcdata = TFile::Open("Ttrees/treeEDBR_DYJetsToLL_HT-100toInf_PHYS14.root");
  TTree *treeMC;
  mcdata->GetObject("treeDumper/EDBRCandidates",treeMC);

  // PseudoData in Sideband region
  RooDataSet sbData("sbData","sbData",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(sideband),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeData));

  // MC datasets in Signal and Sideband regions
  RooDataSet nsBkg("nsBkg",  "nsBkg", RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(nomselec),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeMC));
  RooDataSet sbBkg("sbBkg",  "sbBkg", RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(sideband),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeMC));

  // Combine Nominal + Sideband MC  
  RooCategory region("region","region");
  region.defineType("nsMC");            //signal region monte carlo
  region.defineType("sbMC");            //sideband region monte carlo
  RooDataSet combBkg("combBkg","combBkg",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::WeightVar(lumiWeight),RooFit::Index(region),RooFit::Import("nsMC",nsBkg),RooFit::Import("sbMC",sbBkg));

  // Declare PDFs (3 levelled-exponentials) 
  RooRealVar s0("s0","slope of the exp0",500.,1.,1.e3);
  RooRealVar s1("s1","slope of the exp1",500.,1.,1.e3);
  RooRealVar s2("s2","slope of the exp2",500.,1.,1.e3);
  RooRealVar a0("a0","parameter of exp0",0.1,-1.,1.);
  RooRealVar a1("a1","parameter of exp1",0.1,-1.,1.);
  RooRealVar a2("a2","parameter of exp2",0.1,-1.,1.);
  RooExpTailPdf       nsBkg_pdf("  nsBkg_pdf", "fit bkg  in nominal  region", candMass,s0,a0);
  RooExpTailPdf       sbBkg_pdf("  sbBkg_pdf", "fit bkg  in sideband region", candMass,s1,a1);
  RooExpTailPdf       sbDat_pdf("  sbDat_pdf", "fit data in sideband region", candMass,s2,a2);
  RooAlpha4ExpTailPdf alpha_pdf("  alpha_pdf", "alpha ratio",                 candMass,s0,a0,s1,a1);
  RooProdPdf           M_ZZ_pdf("   M_ZZ_pdf", "M_ZZ_pdf",                    alpha_pdf, sbDat_pdf);

  // Simultaneous Fit of MC sample in signal and sideband region 
  RooSimultaneous combBkg_pdf("combBkg_pdf", "simultaneous pdf", RooArgList(nsBkg_pdf,sbBkg_pdf),region); 
  combBkg_pdf.fitTo(combBkg);
  
  // Fit PseudoData in sideband region 
  sbDat_pdf.fitTo(sbData);

  // Add normalization to M_ZZ_pdf
  RooExtendPdf M_ZZ_pdf_renormalized("M_ZZ_pdf_renormalized","Extended p.d.f", M_ZZ_pdf, numberEvents);
  Double_t expectedEvents       = ((RooRealVar*)(*M_ZZ_pdf_renormalized.getParameters(RooArgSet(candMass))).find("numberEvents"))->getVal();
  Double_t expectedEvents_error = ((RooRealVar*)(*M_ZZ_pdf_renormalized.getParameters(RooArgSet(candMass))).find("numberEvents"))->getError();

  //*******************************************************//
  //                                                       //     
  //                      Unblinding                       //
  //                                                       //     
  //*******************************************************//

  RooDataSet full_data("full_data","full_data",RooArgSet(massVhad,tau21,lep,lumiWeight),RooFit::Cut(selectedCategory),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeData));
  RooDataSet data_ns("data_ns","data_ns",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),RooFit::Cut(nomselec),RooFit::WeightVar(lumiWeight),RooFit::Import(*treeData));
  RooRealVar p0("p0","parameter 0",500., 1. , 1.e3);
  RooRealVar p1("p1","parameter 1",  0.,-1. ,   1.);
  RooExpTailPdf expo("expo","fit bkg in signal region", candMass,p0,p1);
  expo.fitTo(data_ns, RooFit::Range(600.,2600.));
  RooDataSet* pseudoData = expo.generate(RooArgSet(candMass),data_ns,expectedEvents,false,true,true);

  RooPlot* frame1 = massVhad.frame(RooFit::Title("#bf{CMS} Preliminary   #sqrt{s} = 13 TeV   #int L dt = 1 fb^{-1}") );
  RooBinning binsMj(50,110);
  binsMj.addUniform(24,50,110);
  full_data.plotOn(frame1,RooFit::Binning(binsMj));
  mj_pdf_ext.plotOn(frame1,RooFit::LineColor(kRed));
  mj_pdf_ext.paramOn(frame1,RooFit::Layout(0.4,0.88,0.88));

  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  c1->Divide(2,1);
  c1->cd(1);
  gPad->SetGridx();
  frame1->SetMaximum(50);
  frame1->Draw();

  RooPlot* frame2 = candMass.frame(RooFit::Title("#bf{CMS} Preliminary   #sqrt{s} = 13 TeV   #int L dt = 1 fb^{-1}") );
  const Double_t boundaries[12]={600,640,680,740,800,900,1000,1200,1400,1600,2000,2600};
  RooBinning bins(11,boundaries);
  pseudoData->plotOn(frame2,RooFit::Binning(bins));
  M_ZZ_pdf_renormalized.plotOn(frame2,RooFit::LineColor(kRed)); 
  c1->cd(2);
  gPad->SetLogy();
  gPad->SetGridx();
  frame2->SetMinimum(3e-2);
  frame2->SetMaximum(70);
  frame2->Draw();
  frame2->GetYaxis()->SetTitle("Events");
  TPaveText *pt2 = new TPaveText(0.42,0.68,0.88,0.88,"NDC");
  pt2->SetFillColor(0);
  pt2->SetBorderSize(1);
  pt2->SetTextFont(42);
  pt2->AddText(Form("#color[2]{#bf{%s}}",legTitle[key].c_str()));
  pt2->AddText(Form("#bf{Normalization = %.2f #pm %.2f}",expectedEvents,expectedEvents_error));
  pt2->Draw();
  c1->Print(outFile[key].c_str());

  cout << endl << "***************************************************************" << endl << endl;
  cout << "Extrapolation factor = " << scale  << endl;
  cout << endl << "***************************************************************" << endl << endl;

  cout << endl << "***************************************************************" << endl << endl;
  cout << "Expected number of events in signal region = " << expectedEvents  << " +- " << expectedEvents_error << endl;
  cout << endl << "***************************************************************" << endl << endl;

  cout << endl << "***************************************************************" << endl << endl;
  cout << "Real number of events in signal region = " << full_data.sumEntries() - sbDat.sumEntries() << endl;
  cout << endl << "***************************************************************" << endl << endl;

}
