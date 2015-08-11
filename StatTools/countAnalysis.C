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
//        .x countAnalysis.C(   "EHP",    1000,     800,    1200  )
//        .x countAnalysis.C(   "ELP",    1000,     800,    1200  )
//        .x countAnalysis.C(   "MHP",    1000,     800,    1200  )
//        .x countAnalysis.C(   "MLP",    1000,     800,    1200  )

void countAnalysis(std::string key, Int_t mass, Double_t low, Double_t up)
{

  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

  std::map<Int_t, std::string> inputFile;
  inputFile[600]  = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-600.root";
  inputFile[800]  = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-800.root";
  inputFile[1000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1000.root";
  inputFile[1200] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1200.root";
  inputFile[1400] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1400.root";
  inputFile[1600] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1600.root";
  inputFile[1800] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1800.root";
  inputFile[2000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-2000.root";
  inputFile[2500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-2500.root";
  inputFile[3000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-3000.root";
  inputFile[3500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-3500.root";
  inputFile[4000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-4000.root";
  inputFile[4500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-4500.root";

  TFile *f0= TFile::Open("trees/treeEDBR_backgrounds.root");
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

  // Double Crystall ball
  RooRealVar mean("mean","mean of the Crystal Ball",mass,700.,4800.);
  RooRealVar sigma("sigma","Crystal Ball sigma",50.,10.,100.);
  RooRealVar alphaL("alphaL","alpha left",  1., 0.1, 5.);
  RooRealVar alphaR("alphaR","alpha right", 2., 0.1, 5.);
  RooRealVar nL("nL","n left", 30., 0.1, 50.);
  RooRealVar nR("nR","n right", 1., 0.1,  5.);
  RooDoubleCrystalBall sig_pdf("sig_pdf","Double Crystall Ball",candMass,mean,sigma,alphaL,nL,alphaR,nR);
  sig_pdf.fitTo(sigds, RooFit::PrintLevel(-1), RooFit::Range(low,up));

  // Integrate PDFs in signal window
  candMass.setRange("signal",low,up);
  RooAbsReal* bkg_pdf_r = bkg_pdf.createIntegral(candMass,RooFit::NormSet(candMass),RooFit::Range("signal"));
  RooAbsReal* sig_pdf_r = sig_pdf.createIntegral(candMass,RooFit::NormSet(candMass),RooFit::Range("signal"));

  // Number of generated signal events
  std::map<Int_t, Int_t> nEvents;
  nEvents[600]  = 50000;
  nEvents[800]  = 50000;
  nEvents[1000] = 48400;
  nEvents[1200] = 49800;
  nEvents[1400] = 50000;
  nEvents[1600] = 50000;
  nEvents[1800] = 50000;
  nEvents[2000] = 50000;
  nEvents[2500] = 50000;
  nEvents[3000] = 49200;
  nEvents[3500] = 50000;
  nEvents[4000] = 50000;
  nEvents[4500] = 50000;
  // selection efficiency
  Double_t sel_eff = (Double_t)sigds.numEntries()/nEvents[mass];
  Double_t sig_xs_pb = 1.;         // signal cross section in pb
  Double_t target_lumi_pbInv = 40.; // target luminosity in pb^-1
  // Signal yield inside signal window  
  float sigYield = sig_pdf_r->getVal() * target_lumi_pbInv * sel_eff * sig_xs_pb;

  float bkgYield = bkg_pdf_r->getVal() * bkgds.sumEntries();

  // create datacard
  const char *outFile = Form("dataCards/%s%d_card.txt",key.c_str(),mass);
  std::ofstream ofs;
  ofs.open(outFile, std::ofstream::out);
  ofs << Form("imax 1  number of channels\n"         );
  ofs << Form("jmax 1  number of processes minus 1\n");
  ofs << Form("kmax 2  number of systematics\n"      );
  ofs << Form("------------------------------------------------------------------------------\n");
  ofs << Form("bin            %-10s\n", key.c_str());
  ofs << Form("observation    %-10s\n",    "10"    );
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
