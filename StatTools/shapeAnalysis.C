//
//        Require pre-compiled PDFs library  
//
//        Usage:
// 
//        root -l 
//
//        gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
//
//                             category  central   lower    upper
//
//        .x shapeAnalysis.C(   "EHP",    1000,     800,    1200  )
//        .x shapeAnalysis.C(   "ELP",    1000,     800,    1200  )
//        .x shapeAnalysis.C(   "MHP",    1000,     800,    1200  )
//        .x shapeAnalysis.C(   "MLP",    1000,     800,    1200  )
//
//        .x shapeAnalysis.C(   "EHP",    2000,    1700,    2300  )
//        .x shapeAnalysis.C(   "ELP",    2000,    1700,    2300  )
//        .x shapeAnalysis.C(   "MHP",    2000,    1700,    2300  )
//        .x shapeAnalysis.C(   "MLP",    2000,    1700,    2300  )
//
//        .x shapeAnalysis.C(   "EHP",    3000,    2400,    3500  )
//        .x shapeAnalysis.C(   "ELP",    3000,    2400,    3500  )
//        .x shapeAnalysis.C(   "MHP",    3000,    2400,    3500  )
//        .x shapeAnalysis.C(   "MLP",    3000,    2400,    3500  )
//
//        .x shapeAnalysis.C(   "EHP",    4000,    3200,    4800  )
//        .x shapeAnalysis.C(   "ELP",    4000,    3200,    4800  )
//        .x shapeAnalysis.C(   "MHP",    4000,    3200,    4800  )
//        .x shapeAnalysis.C(   "MLP",    4000,    3200,    4800  )
//

void shapeAnalysis(std::string key, Int_t mass, Double_t low, Double_t up)
{

  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

  std::map<Int_t, std::string> inputFile;
  inputFile[1000] = "../treeEDBR_RSGravToZZ_kMpl01_M-1000.root";
  inputFile[2000] = "../treeEDBR_RSGravToZZ_kMpl01_M-2000.root";
  inputFile[3000] = "../treeEDBR_RSGravToZZ_kMpl01_M-3000.root";
  inputFile[4000] = "../treeEDBR_RSGravToZZ_kMpl01_M-4000.root";

  TFile *f0= TFile::Open("../treeEDBR_DYJetsToLL_HT-100toInf_PHYS14.root");
  TFile *f1= TFile::Open(inputFile[mass].c_str());
  TTree *t0, *t1;
  f0->GetObject("treeDumper/EDBRCandidates",t0);
  f1->GetObject("treeDumper/EDBRCandidates",t1);

  RooRealVar candMass("candMass","M_{ZZ}",700.,  4800., "GeV");
  RooRealVar massVhad("massVhad","M_{J}",  70.,   110., "GeV");
  RooRealVar ptVhad("ptVhad","p_{T}",     200., 10000., "GeV");
  RooRealVar ptVlep("ptVlep","p_{T}",     200., 10000., "GeV");
  RooRealVar tau21("tau21","tau21",         0.,     1.);
  RooRealVar lep("lep","lep",               10,     15);
  RooRealVar lumiWeight("lumiWeight", "pure weight", 0., 10.);

  std::map<std::string, std::string> selection;
  selection["EHP"] = "lep<12 && tau21<0.5";
  selection["MHP"] = "lep>12 && tau21<0.5";
  selection["ELP"] = "lep<12 && tau21>0.5 && tau21<0.75";
  selection["MLP"] = "lep>12 && tau21>0.5 && tau21<0.75";
  TCut myCut = selection[key].c_str();

  // datasets
  RooDataSet bkgds("bkgds","bkgds",RooArgSet(candMass,massVhad,ptVhad,ptVlep,tau21,lep,lumiWeight),RooFit::Cut(myCut),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  RooDataSet sigds("sigds","sigds",RooArgSet(candMass,massVhad,ptVhad,ptVlep,tau21,lep,lumiWeight),RooFit::Cut(myCut),RooFit::WeightVar(lumiWeight),RooFit::Import(*t1));

  // Build exponential p.d.f.
  RooRealVar p0("p0","parameter 0",150., 10., 400.);
  RooRealVar p1("p1","parameter 1",  0., -1.,   1.);
  RooGenericPdf bkg_pdf("bkg_pdf","leveled exponential PDF","exp(-candMass/(p0+p1*candMass))",RooArgSet(candMass,p0,p1));
  bkg_pdf.fitTo(bkgds, RooFit::PrintLevel(-1));
  p0.setConstant(true);
  p1.setConstant(true);
//  RooPlot *plot = candMass.frame();
//  bkgds.plotOn(plot);
//  bkg_pdf.plotOn(plot);
//  bkg_pdf.paramOn(plot);
//  plot->Draw();
//  cout << "chi2: " << plot->chiSquare(2) << endl; 

  // Double Crystall ball
  RooRealVar mean("mean","mean of the Crystal Ball",mass,700.,4800.);
  RooRealVar sigma("sigma","Crystal Ball sigma",50.,10.,100.);
  RooRealVar alphaL("alphaL","alpha left",  1., 0.1, 5.);
  RooRealVar alphaR("alphaR","alpha right", 2., 0.1, 5.);
  RooRealVar nL("nL","n left", 30., 0.1, 50.);
  RooRealVar nR("nR","n right", 1., 0.1,  5.);
  RooDoubleCrystalBall sig_pdf("sig_pdf","Double Crystall Ball",candMass,mean,sigma,alphaL,nL,alphaR,nR);
  sig_pdf.fitTo(sigds, RooFit::PrintLevel(-1), RooFit::Range(low,up));
  mean.setConstant(true);
  sigma.setConstant(true);
  alphaL.setConstant(true);
  alphaR.setConstant(true);
  nL.setConstant(true);
  nR.setConstant(true);
//  RooPlot *plot = candMass.frame(low,up);
//  sigds.plotOn(plot);
//  sig_pdf.plotOn(plot);
//  sig_pdf.paramOn(plot);
//  plot->Draw();
//  cout << "chi2: " << plot->chiSquare(6) << endl; 

  // Integrate PDFs in signal window
  candMass.setRange("signal",low,up);
  RooAbsReal* bkg_pdf_r = bkg_pdf.createIntegral(candMass,RooFit::NormSet(candMass),RooFit::Range("signal"));
  RooAbsReal* sig_pdf_r = sig_pdf.createIntegral(candMass,RooFit::NormSet(candMass),RooFit::Range("signal"));

  // Number of generated signal events
  std::map<Int_t, Int_t> nEvents;
  nEvents[1000] = 2823;
  nEvents[2000] = 2733;
  nEvents[3000] = 2726;
  nEvents[4000] = 2860;

  // target luminosity
  Double_t target_lumi_fbInv = 3.;

  // Get yields inside signal window 
  float bkgYield = bkg_pdf_r->getVal() * bkgds.sumEntries();
  float sigYield = sig_pdf_r->getVal() * sigds.numEntries() * target_lumi_fbInv / nEvents[mass];

  // Generate 10 events of pseudo-data
  RooDataSet *data = bkg_pdf.generate(candMass,10);
  data->SetName("data");

  // create workspace
  RooWorkspace *w = new RooWorkspace("myws","workspace") ;
  w->import(*data);
  w->import(bkg_pdf);
  w->import(sig_pdf);
  w->writeToFile(Form("workSpaces/wspace_%s%d.root",key.c_str(),mass));

  // create datacard
  const char *outFile = Form("dataCards/%s%d_shape_card.txt",key.c_str(),mass);
  std::ofstream ofs;
  ofs.open(outFile, std::ofstream::out);

  ofs << Form("imax 1  number of channels\n"       );
  ofs << Form("jmax 1  number of processes minus 1\n");
  ofs << Form("kmax *\n");

  ofs << Form("------------------------------------------------------------------------------\n");

  ofs << Form("shapes         %-10s    %-5s    workSpaces/wspace_%s%d.root    %-10s\n", "mc_signal", key.c_str(), key.c_str(),mass, "myws:sig_pdf");
  ofs << Form("shapes         %-10s    %-5s    workSpaces/wspace_%s%d.root    %-10s\n", "bkg_mass",  key.c_str(), key.c_str(),mass, "myws:bkg_pdf");
  ofs << Form("shapes         %-10s    %-5s    workSpaces/wspace_%s%d.root    %-10s\n", "data_obs",  key.c_str(), key.c_str(),mass, "myws:data"   );

  ofs << Form("------------------------------------------------------------------------------\n");

  ofs << Form("bin            %-10s\n", key.c_str());
  ofs << Form("observation    %-10s\n",      "-1.0");

  ofs << Form("------------------------------------------------------------------------------\n");

  ofs << Form("bin            %-10s    %-10s\n", key.c_str(), key.c_str());
  ofs << Form("process        %-10s    %-10s\n", "mc_signal",  "bkg_mass");
  ofs << Form("process        %-10s    %-10s\n",         "0",         "1");
  ofs << Form("rate           %-10f    %-10f\n",    sigYield,    bkgYield);

  ofs << Form("------------------------------------------------------------------------------\n");

  ofs << Form("lumi    lnN    %-10s    %-10s\n", "1.03", "1.03");
  ofs << Form("eff_sig lnN    %-10s    %-10s\n", "1.01",  "-"  );

  ofs.close();
  
}
