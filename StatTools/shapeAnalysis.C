//
//        Require pre-compiled PDFs library  
//
//        Usage:
// 
//        root -l 
//
//        gSystem->Load("PDFs/HWWLVJRooPdfs_cxx.so")
//        gSystem->Load("PDFs/PdfDiagonalizer_cc.so")
//
//        .x shapeAnalysis.C("EHP", 1000)
//        .x shapeAnalysis.C("ELP", 1000)
//        .x shapeAnalysis.C("MHP", 1000)
//        .x shapeAnalysis.C("MLP", 1000)

//        .x shapeAnalysis.C("EHP", 2000)
//        .x shapeAnalysis.C("ELP", 2000)
//        .x shapeAnalysis.C("MHP", 2000)
//        .x shapeAnalysis.C("MLP", 2000)

//        .x shapeAnalysis.C("EHP", 3000)
//        .x shapeAnalysis.C("ELP", 3000)
//        .x shapeAnalysis.C("MHP", 3000)
//        .x shapeAnalysis.C("MLP", 3000)

//        .x shapeAnalysis.C("EHP", 4000)
//        .x shapeAnalysis.C("ELP", 4000)
//        .x shapeAnalysis.C("MHP", 4000)
//        .x shapeAnalysis.C("MLP", 4000)

void shapeAnalysis(std::string key, Int_t mass)
{
  using namespace RooFit;

  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);

  RooRealVar candMass("candMass","M_{ZZ}", 700.,4800., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,  50., 110., "GeV");
  RooRealVar tau21("tau21","tau21",          0.,   1.       );
  RooRealVar lep("lep","lep",                10,   15       );
  RooRealVar lumiWeight("lumiWeight", "pure weight", 0., 10.);

  massVhad.setRange("signalRegion",   70., 110.);
  massVhad.setRange("sidebandRegion", 50.,  70.);

  std::map<std::string, std::string> selection;
  selection["EHP"] = "lep<12 && tau21<0.5";
  selection["MHP"] = "lep>12 && tau21<0.5";
  selection["ELP"] = "lep<12 && tau21>0.5 && tau21<0.75";
  selection["MLP"] = "lep>12 && tau21>0.5 && tau21<0.75";

  TCut selectedCategory = selection[key].c_str();
  TCut sideband = "massVhad<70." + selectedCategory;
  TCut nomselec = "massVhad>70." + selectedCategory;

  //*******************************************************//
  //                                                       //     
  //                   Get Normalization                   //
  //                                                       //     
  //*******************************************************//

  TFile *data = TFile::Open("treeEDBR_PseudoData.root");
  TTree *treeData;
  data->GetObject("treeDumper/EDBRCandidates",treeData);

  RooDataSet sbObs("sbObs","sbObs",RooArgSet(massVhad,tau21,lep,lumiWeight),Cut(sideband),WeightVar(lumiWeight),Import(*treeData));

  // FIXME to subtract subdominant backgrounds

  // Error Function * Exponential
  RooRealVar c("c","slope of the exp",-0.5,-10.,0.);
  RooRealVar offset("offset","offset of the erf",1.,0.,10.);
  RooRealVar width("width","width of the erf",1.,0.,10.);
  RooRealVar yieldSideband("yieldSideband","Zjets normalization in sideband region", 1, 0.1, 1.e4);
  RooRealVar ZZ_bkg_eig_norm("ZZ_bkg_eig_norm",    "Zjets normalization in signal region",   1, 0.1, 1.e4);
  RooErfExpPdf mj_pdf("mj_pdf","fiting mj spectrum",massVhad,c,offset,width);
  RooExtendPdf mj_pdf_ext("mj_pdf_ext","extended p.d.f", mj_pdf, yieldSideband);
  mj_pdf_ext.fitTo(sbObs, Extended(kTRUE), Minimizer("Minuit"), Range("sidebandRegion"), PrintLevel(-1));

  // Extrapolate PDF to signal window 
  RooAbsReal* n_signalRegion = mj_pdf.createIntegral(massVhad,NormSet(massVhad),Range("signalRegion"));
  RooAbsReal* n_contrlRegion = mj_pdf.createIntegral(massVhad,NormSet(massVhad),Range("sidebandRegion"));
  Double_t scale = n_signalRegion->getVal()/n_contrlRegion->getVal();
  Double_t bkgYield       = yieldSideband.getVal()   * scale; // scale yield in sideband to get yield in signal region
  Double_t bkgYield_error = yieldSideband.getError() * scale;
  ZZ_bkg_eig_norm.setVal(   bkgYield );
  ZZ_bkg_eig_norm.setError( bkgYield_error );
  ZZ_bkg_eig_norm.setConstant(true);

  //*******************************************************//
  //                                                       //     
  //      Simultaneous fit and alpha ratio                 //
  //                                                       //     
  //*******************************************************//

  TFile *mcdata = TFile::Open("treeEDBR_DYJetsToLL_HT-100toInf_PHYS14.root");
  TTree *treeMC;
  mcdata->GetObject("treeDumper/EDBRCandidates",treeMC);

  // PseudoData in Sideband region
  RooDataSet sbData("sbData","sbData",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),Cut(sideband),WeightVar(lumiWeight),Import(*treeData));

  // MC datasets in Signal and Sideband regions
  RooDataSet nsBkg("nsBkg",  "nsBkg", RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),Cut(nomselec),WeightVar(lumiWeight),Import(*treeMC));
  RooDataSet sbBkg("sbBkg",  "sbBkg", RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),Cut(sideband),WeightVar(lumiWeight),Import(*treeMC));

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

  // Perform a simultaneous fit  
  RooCategory region("region","region");
  region.defineType("nsMC");
  region.defineType("sbMC");
  region.defineType("sbDA");
  RooDataSet bigSample("bigSample","bigSample",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),WeightVar(lumiWeight),Index(region),Import("nsMC",nsBkg),Import("sbMC",sbBkg),Import("sbDA",sbData));
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(nsBkg_pdf,sbBkg_pdf,sbObs_pdf), region); 
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Minimizer("Minuit2"), PrintLevel(-1));
  s0.setConstant(true);
  s1.setConstant(true);
  s2.setConstant(true);
  a0.setConstant(true);
  a1.setConstant(true);
  a2.setConstant(true);

  //*******************************************************//
  //                                                       //     
  //                    Signal shape                       //
  //                                                       //     
  //*******************************************************//

  std::map<Int_t, std::string> inputFile;
  inputFile[1000] = "treeEDBR_RSGravToZZ_kMpl01_M-1000_PHYS14.root";
  inputFile[2000] = "treeEDBR_RSGravToZZ_kMpl01_M-2000_PHYS14.root";
  inputFile[3000] = "treeEDBR_RSGravToZZ_kMpl01_M-3000_PHYS14.root";
  inputFile[4000] = "treeEDBR_RSGravToZZ_kMpl01_M-4000_PHYS14.root";

  std::map<Int_t, Double_t> low;
  low[1000] =  800.;
  low[2000] = 1700.;
  low[3000] = 2400.;
  low[4000] = 3200.;

  std::map<Int_t, Double_t> upp;
  upp[1000] = 1200.;
  upp[2000] = 2300.;
  upp[3000] = 3500.;
  upp[4000] = 4800.;

  TFile *f1= TFile::Open(inputFile[mass].c_str());
  TTree *t1;
  f1->GetObject("treeDumper/EDBRCandidates",t1);
  RooDataSet dsSig("dsSig","dsSig",RooArgSet(candMass,massVhad,tau21,lep,lumiWeight),Cut(nomselec),WeightVar(lumiWeight),Import(*t1));

  // Double Crystall ball
  RooRealVar mean("mean","mean of the Crystal Ball",mass,700.,4800.);
  RooRealVar sigma("sigma","Crystal Ball sigma",50.,10.,100.);
  RooRealVar alphaL("alphaL","alpha left",  1., 0.1, 5.);
  RooRealVar alphaR("alphaR","alpha right", 2., 0.1, 5.);
  RooRealVar nL("nL","n left", 30., 0.1, 50.);
  RooRealVar nR("nR","n right", 1., 0.1,  5.);
  RooDoubleCrystalBall ZZ_sig("ZZ_sig","Double Crystall Ball",candMass,mean,sigma,alphaL,nL,alphaR,nR);
  ZZ_sig.fitTo(dsSig, Minimizer("Minuit2"), Range(low[mass],upp[mass]), PrintLevel(-1));
  mean.setConstant(true);
  sigma.setConstant(true);
  alphaL.setConstant(true);
  alphaR.setConstant(true);
  nL.setConstant(true);
  nR.setConstant(true);

  // Number of generated signal events
  std::map<Int_t, Int_t> nEvents;
  nEvents[1000] = 2823;
  nEvents[2000] = 2733;
  nEvents[3000] = 2726;
  nEvents[4000] = 2860;
  nEvents[4500] = 199385;
  // selection efficiency
  Double_t sel_eff = (Double_t)dsSig.numEntries()/nEvents[mass];
  Double_t sig_xs_fb = 1.;         // signal cross section in fb
  Double_t target_lumi_fbInv = 1.; // target luminosity in fb^-1
  // Signal yield  
  Double_t sigYield = target_lumi_fbInv * sel_eff * sig_xs_fb;

  //*******************************************************//
  //                                                       //     
  //       Generate workspaces and datacards               //
  //                                                       //     
  //*******************************************************//

  // create workspace
  RooWorkspace *w = new RooWorkspace("ZZ_13TeV","workspace") ;
  w->import(ZZ_sig);
  w->import(ZZ_bkg);
  w->import(ZZ_bkg_eig_norm);
  
  // diagonalization
  PdfDiagonalizer diago("eig", w, *fitres);
  RooAbsPdf *ZZ_bkg_eig = diago.diagonalize(*w->pdf("ZZ_bkg"));
  w->import(*ZZ_bkg_eig, RecycleConflictNodes());

  // Generate 30 events of pseudo-data
  RooDataSet *data_obs = ZZ_bkg.generate(candMass,30);
  data_obs->SetName("data_obs");
  w->import(*data_obs);
  w->writeToFile(Form("workSpaces/CMS_ZZ_%d_%s_13TeV.root",mass,key.c_str()));
 
  // create datacard
  const char *outFile = Form("dataCards/CMS_ZZ_%d_%s_13TeV.txt",mass,key.c_str());
  std::ofstream ofs;
  ofs.open(outFile, std::ofstream::out);

  ofs << Form("imax 1\n");
  ofs << Form("jmax *\n");
  ofs << Form("kmax *\n");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("shapes            %-10s         %-5s    workSpaces/CMS_ZZ_%d_%s_13TeV.root    %s\n", "*",        key.c_str(), mass, key.c_str(), "ZZ_13TeV:$PROCESS");
  ofs << Form("shapes            %-10s         %-5s    workSpaces/CMS_ZZ_%d_%s_13TeV.root    %s\n", "data_obs", key.c_str(), mass, key.c_str(), "ZZ_13TeV:data_obs");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("bin               %s\n", key.c_str());
  ofs << Form("observation       %s\n",      "-1.0");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("bin               %-10s         %s\n",     key.c_str(),      key.c_str());
  ofs << Form("process           %-10s         %s\n",        "ZZ_sig",     "ZZ_bkg_eig");
  ofs << Form("process           %-10s         %s\n",             "0",              "1");
  ofs << Form("rate              %-10f         %s\n",        sigYield,              "1");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("lumi_13TeV                     lnN       %-10s    %s\n", "1.026", "1.026");
  ofs << Form("CMS_eff_vtag_tau21_sf_13TeV    lnN       %-10s    %s\n", "1.15",  "1.15" );
  ofs << Form("CMS_scale_j_13TeV              lnN       %-10s    %s\n", "1.12",  "1.12" );
  ofs << Form("CMS_res_j_13TeV                lnN       %-10s    %s\n", "1.04",  "1.04" );
  ofs << Form("CMS_pu_13TeV                   lnN       %-10s    %s\n", "1.03",  "1.03" );
  ofs << Form("eig_eig0                     param       %-10s    %s\n", "0",     "1"    );
  ofs << Form("eig_eig1                     param       %-10s    %s\n", "0",     "1"    );
  ofs << Form("eig_eig2                     param       %-10s    %s\n", "0",     "1"    );
  ofs << Form("eig_eig3                     param       %-10s    %s\n", "0",     "1"    );
  ofs << Form("eig_eig4                     param       %-10s    %s\n", "0",     "1"    );
  ofs << Form("eig_eig5                     param       %-10s    %s\n", "0",     "1"    );

  ofs.close();
}
