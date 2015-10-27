//
//        Requires pre-compiled PDFs library  
//
//        Requires ROOT 6.04/02 (or above) to take advantage of R__LOAD_LIBRARY
//        https://root.cern.ch/root/html604/notes/release-notes.html#interpreter  
//
//        Examples of usage:
// 
//        root -b -q 'shapeAnalysis.C("ENP", 1400)'   // Electron No Purity
//        root -b -q 'shapeAnalysis.C("EHP", 1400)'   // Electron High Purity
//        root -b -q 'shapeAnalysis.C("ELP", 1400)'   // Electron Low Purity
//        root -b -q 'shapeAnalysis.C("MNP", 1400)'   // Muon No Purity
//        root -b -q 'shapeAnalysis.C("MHP", 1400)'   // Muon High Purity
//        root -b -q 'shapeAnalysis.C("MLP", 1400)'   // Muon Low Purity

R__LOAD_LIBRARY(PDFs/HWWLVJRooPdfs_cxx.so)
R__LOAD_LIBRARY(PDFs/PdfDiagonalizer_cc.so)

void shapeAnalysis(std::string key, Int_t mass)
{
  using namespace RooFit;

  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);

  RooRealVar candMass("candMass","M_{VZ}", 600., 4800., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,  40., 9999., "GeV");
  RooRealVar tau21("tau21","tau21",          0.,    1.       );
  RooRealVar lep("lep","lep",                10,    15       );
  RooRealVar lumiWeight("lumiWeight", "lumi weight",       0., 1.e4 );
  RooRealVar pileupWeight("pileupWeight", "pileup weight", 0., 1.e4 );

  massVhad.setRange("lowerSB",      40.,   65.);
  massVhad.setRange("lowerSIG",     65.,  105.);
  massVhad.setRange("upperSIG",    105.,  145.);
  massVhad.setRange("upperSB",     145., 9999.);

  std::map<std::string, std::string> selection;
  selection["ENP"] = "candMass>600 && lep<12";
  selection["MNP"] = "candMass>600 && lep>12";
  selection["EHP"] = "candMass>600 && lep<12 && tau21<0.6";
  selection["MHP"] = "candMass>600 && lep>12 && tau21<0.6";
  selection["ELP"] = "candMass>600 && lep<12 && tau21>0.6 && tau21<0.75";
  selection["MLP"] = "candMass>600 && lep>12 && tau21>0.6 && tau21<0.75";

  TCut selectedCategory = selection[key].c_str();
  TCut lowerSIG = "massVhad>65.  && massVhad<105" + selectedCategory;
  TCut upperSIG = "massVhad>105. && massVhad<145" + selectedCategory;
  TCut lowerSB  = "massVhad<65."  + selectedCategory;
  TCut upperSB  = "massVhad>145." + selectedCategory;
  TCut allSB    = lowerSB or upperSB;

  //*******************************************************//
  //                                                       //     
  //                      Input files                      //
  //                                                       //     
  //*******************************************************//

  TChain treeData( "treeDumper/EDBRCandidates");
  TChain treeMCsub("treeDumper/EDBRCandidates");
  TChain treeMC(   "treeDumper/EDBRCandidates");
  std::map<Int_t, std::string> inputFile;

  if( key[0]=='E' ){ 
      treeData.Add(     "../trees/treeEDBR_SingleElectron.root"                ); 
      treeMCsub.Add(    "../elTrees/treeEDBR_WZ.root"                          );
      treeMCsub.Add(    "../elTrees/treeEDBR_ZZ.root"                          );
      treeMCsub.Add(    "../elTrees/treeEDBR_T_T.root"                         );
      treeMC.Add(       "../elTrees/treeEDBR_DYJetsToLL_HT-100to200.root"      );
      treeMC.Add(       "../elTrees/treeEDBR_DYJetsToLL_HT-200to400.root"      );
      treeMC.Add(       "../elTrees/treeEDBR_DYJetsToLL_HT-400to600.root"      );
      treeMC.Add(       "../elTrees/treeEDBR_DYJetsToLL_HT-600toInf.root"      );
      inputFile[600]  = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-600.root" ;
      inputFile[800]  = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-800.root" ;
      inputFile[1000] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1000.root";
      inputFile[1200] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1200.root";
      inputFile[1400] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1400.root";
      inputFile[1600] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1600.root";
      inputFile[1800] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1800.root";
      inputFile[2000] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-2000.root";
      inputFile[2500] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-2500.root";
      inputFile[3000] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-3000.root";
      inputFile[3500] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-3500.root";
      inputFile[4000] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-4000.root";
      inputFile[4500] = "../elTrees/treeEDBR_BulkGravToZZToZlepZhad_M-4500.root";
  }

  if( key[0]=='M' ){
      treeData.Add(     "../trees/treeEDBR_SingleMuon.root"                    ); 
      treeMCsub.Add(    "../muTrees/treeEDBR_WZ.root"                          );
      treeMCsub.Add(    "../muTrees/treeEDBR_ZZ.root"                          );
      treeMCsub.Add(    "../muTrees/treeEDBR_T_T.root"                         );
      treeMC.Add(       "../muTrees/treeEDBR_DYJetsToLL_HT-100to200.root"      );
      treeMC.Add(       "../muTrees/treeEDBR_DYJetsToLL_HT-200to400.root"      );
      treeMC.Add(       "../muTrees/treeEDBR_DYJetsToLL_HT-400to600.root"      );
      treeMC.Add(       "../muTrees/treeEDBR_DYJetsToLL_HT-600toInf.root"      );
      inputFile[600]  = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-600.root" ;
      inputFile[800]  = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-800.root" ;
      inputFile[1000] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1000.root";
      inputFile[1200] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1200.root";
      inputFile[1400] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1400.root";
      inputFile[1600] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1600.root";
      inputFile[1800] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-1800.root";
      inputFile[2000] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-2000.root";
      inputFile[2500] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-2500.root";
      inputFile[3000] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-3000.root";
      inputFile[3500] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-3500.root";
      inputFile[4000] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-4000.root";
      inputFile[4500] = "../muTrees/treeEDBR_BulkGravToZZToZlepZhad_M-4500.root";
  }

  //*******************************************************//
  //                                                       //     
  //                   Get Normalization                   //
  //                                                       //     
  //*******************************************************//

  RooDataSet sbObs("sbObs","sbObs", RooArgSet(massVhad,candMass,tau21,lep), Cut(allSB), Import(treeData));

  // Error Function * Exponential
  RooRealVar c("c","slope of the exp",              -0.1,  -1.0,  0.0);
  RooRealVar offset("offset","offset of the erf",    0.1,   0.0,  2.0);
  RooRealVar width("width",  "width of the erf",     0.1,   0.0,  1.0);
  RooRealVar yieldSideband("yieldSideband", "Zjets normalization in sideband region", 10., 1., 1.e4);
  yieldSideband.setVal(        sbObs.numEntries()  );
  yieldSideband.setError( sqrt(sbObs.numEntries()) );
  yieldSideband.setConstant(true);

  RooRealVar ZZ_bkg_eig_norm("ZZ_bkg_eig_norm", "Zjets normalization in signal region",     10., 1., 1.e4);
  RooErfExpPdf mj_pdf("mj_pdf","fiting mj spectrum",massVhad,c,offset,width);
  RooExtendPdf mj_pdf_ext("mj_pdf_ext","extended p.d.f", mj_pdf, yieldSideband);
  mj_pdf_ext.fitTo(sbObs, Extended(kTRUE), Minimizer("Minuit"), Range("lowerSB,upperSB"), PrintLevel(-1));

  // Extrapolate PDF to signal window 
  RooAbsReal* n_signalR1  = mj_pdf.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* n_sideband  = mj_pdf.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB,upperSB"));
  Double_t scale  = n_signalR1->getVal()/n_sideband->getVal(); //scale yield from both sidebands to lower SIG
  Double_t bkgYield       = yieldSideband.getVal()   * scale; 
  Double_t bkgYield_error = yieldSideband.getError() * scale;

  //*******************************************************//
  //                                                       //     
  //      Contribution of subddominant backgrounds         //
  //                                                       //     
  //*******************************************************//

  RooRealVar totalWeight("totalWeight", "total weight",  0., 1.);
  RooDataSet lowSigMCsub("lowSigMCsub","lowSigMCsub",RooArgSet(massVhad,candMass,tau21,lep,totalWeight),WeightVar(totalWeight),Cut(lowerSIG), Import(treeMCsub));
  double subMCyield = lowSigMCsub.sumEntries();
  double subMCyield_error = sqrt(subMCyield);

  // Add contribution of subdominant backgrounds
  ZZ_bkg_eig_norm.setVal( bkgYield + subMCyield );
  ZZ_bkg_eig_norm.setError( sqrt( bkgYield_error*bkgYield_error + subMCyield_error*subMCyield_error ) );
  ZZ_bkg_eig_norm.setConstant(true);
 
  //*******************************************************//
  //                                                       //     
  //      Simultaneous fit and alpha ratio                 //
  //                                                       //     
  //*******************************************************//

  RooArgSet variables(candMass,massVhad,tau21,lep,lumiWeight,pileupWeight);

  // Weight MC to current luminosity
  // For MC:   totWeight == lumiWeight*pileupWeight
  // For Data: totWeight == 1
  const char *weightFormula = "(lumiWeight<999)*lumiWeight*pileupWeight + (lumiWeight>999)";
  RooFormulaVar wFunc("wFunc","event weight", weightFormula, RooArgList(lumiWeight,pileupWeight));

  // Data in lower sideband
  RooDataSet sbDataNoW("sbData","sbData",variables,Cut(lowerSB),Import(treeData));
  RooRealVar* w0 = (RooRealVar*) sbDataNoW.addColumn(wFunc);
  RooDataSet sbData(sbDataNoW.GetName(), sbDataNoW.GetTitle(), &sbDataNoW, *sbDataNoW.get(),0,w0->GetName());

  // MC datasets in Signal and Sideband regions
  RooDataSet nsBkgNoW("nsBkgNoW",  "nsBkgNoW", variables, Cut(lowerSIG), Import(treeMC));
  RooDataSet sbBkgNoW("sbBkgNoW",  "sbBkgNoW", variables, Cut(lowerSB),  Import(treeMC));
  RooRealVar* w1 = (RooRealVar*) nsBkgNoW.addColumn(wFunc);
  RooRealVar* w2 = (RooRealVar*) sbBkgNoW.addColumn(wFunc);
  RooDataSet nsBkg(nsBkgNoW.GetName(), nsBkgNoW.GetTitle(), &nsBkgNoW, *nsBkgNoW.get(),0,w1->GetName());
  RooDataSet sbBkg(sbBkgNoW.GetName(), sbBkgNoW.GetTitle(), &sbBkgNoW, *sbBkgNoW.get(),0,w2->GetName());
  
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
  RooDataSet bigSampleNoW("bigSampleNoW","bigSampleNoW", variables, Index(region), Import("nsMC",nsBkg), Import("sbMC",sbBkg), Import("sbDA",sbData));
  RooRealVar* w3 = (RooRealVar*) bigSampleNoW.addColumn(wFunc);
  RooDataSet bigSample(bigSampleNoW.GetName(), bigSampleNoW.GetTitle(), &bigSampleNoW, *bigSampleNoW.get(),0,w3->GetName());
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(nsBkg_pdf,sbBkg_pdf,sbObs_pdf), region); 
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Minimizer("Minuit"), PrintLevel(-1));
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

  std::map<Int_t, Double_t> low;
  low[600]  =  400.;
  low[800]  =  600.;
  low[1000] =  800.;
  low[1200] = 1000.;
  low[1400] = 1200.;
  low[1600] = 1300.;
  low[1800] = 1500.;
  low[2000] = 1700.;
  low[2500] = 2100.;
  low[3000] = 2400.;
  low[3500] = 2900.;
  low[4000] = 3200.;
  low[4500] = 3700.;

  std::map<Int_t, Double_t> upp;
  upp[600]  =  800.;
  upp[800]  = 1000.;
  upp[1000] = 1200.;
  upp[1200] = 1400.;
  upp[1400] = 1600.;
  upp[1600] = 1900.;
  upp[1800] = 2100.;
  upp[2000] = 2300.;
  upp[2500] = 2900.;
  upp[3000] = 3500.;
  upp[3500] = 4000.;
  upp[4000] = 4800.;
  upp[4500] = 5300.;

  TChain bulkG("treeDumper/EDBRCandidates");
  bulkG.Add(inputFile[mass].c_str());
  RooDataSet dsSig("dsSig","dsSig",RooArgSet(candMass,massVhad,tau21,lep),Cut(lowerSIG),Import(bulkG));

  // Double Crystall ball
  RooRealVar mean("mean","mean of the Crystal Ball",mass,400.,4800.);
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

  // Number of signal events entering hltFilter
  std::map<Int_t, Int_t> nEvents;
  nEvents[600]  = 32338;
  nEvents[800]  = 32400;
  nEvents[1000] = 31320;
  nEvents[1200] = 31983;
  nEvents[1400] = 32361;
  nEvents[1600] = 32444;
  nEvents[1800] = 32525;
  nEvents[2000] = 32541;
  nEvents[2500] = 32344;
  nEvents[3000] = 31977;
  nEvents[3500] = 32409;
  nEvents[4000] = 32448;
  nEvents[4500] = 32292;

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

  // Observed data
  RooDataSet data_obs("data_obs","data_obs",RooArgSet(candMass,massVhad,tau21,lep),Cut(lowerSB),Import(treeData));
  w->import(data_obs);

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
