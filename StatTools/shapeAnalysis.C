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

  RooRealVar candMass("candMass","M_{VZ}",                     500., 5300., "GeV");
  RooRealVar massVhad("massVhad","pruned m_{jet}",              20.,  220., "GeV");
  RooRealVar tau21("tau21","tau21",                              0.,  0.75       );
  RooRealVar lep("lep","lep",                                    10,    15       );
  RooRealVar totalWeight("totalWeight", "total weight",          0.,    10.      );
  RooArgSet variables(candMass,massVhad,tau21,lep,totalWeight);

  massVhad.setRange("lowerSB",      20.,   65.);
  massVhad.setRange("lowerSIG",     65.,  105.);
  massVhad.setRange("upperSIG",    105.,  135.);
  massVhad.setRange("upperSB",     135.,  220.);

  std::map<std::string, std::string> selection;
  selection["ENP"] = "lep<12 && tau21<0.6";
  selection["MNP"] = "lep>12 && tau21<0.6";
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
  std::map<Int_t, std::string> inputFile;
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
      inputFile[600]  = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-600_el.root";
      inputFile[800]  = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-800_el.root";
      inputFile[1000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1000_el.root";
      inputFile[1200] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1200_el.root";
      inputFile[1400] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1400_el.root";
      inputFile[1600] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1600_el.root";
      inputFile[1800] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1800_el.root";
      inputFile[2000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-2000_el.root";
      inputFile[2500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-2500_el.root";
      inputFile[3000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-3000_el.root";
      inputFile[3500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-3500_el.root";
      inputFile[4000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-4000_el.root";
      inputFile[4500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-4500_el.root";
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
      inputFile[600]  = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-600_mu.root";
      inputFile[800]  = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-800_mu.root";
      inputFile[1000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1000_mu.root";
      inputFile[1200] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1200_mu.root";
      inputFile[1400] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1400_mu.root";
      inputFile[1600] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1600_mu.root";
      inputFile[1800] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-1800_mu.root";
      inputFile[2000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-2000_mu.root";
      inputFile[2500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-2500_mu.root";
      inputFile[3000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-3000_mu.root";
      inputFile[3500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-3500_mu.root";
      inputFile[4000] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-4000_mu.root";
      inputFile[4500] = "trees/treeEDBR_BulkGravToZZToZlepZhad_M-4500_mu.root";
      lepton_scale    = "1.03";
  }

  // dataset to host data in sideband
  RooDataSet sbObs("sbObs","sbObs", variables, Cut(allSB), Import(treeData));

  // MC datasets
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC1));
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC2));
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
  RooFitResult* erf = model_ext.fitTo(sbObs,Extended(kTRUE),Range("lowerSB,upperSB"),PrintLevel(-1),Save());

  // Calculate integral of the model
  RooAbsReal* domBkgIntegralSR = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* subBkgIntegralSR = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooFormulaVar domBkgSRyield("domBkgSRyield","@0*@1",RooArgList(*domBkgIntegralSR,nbkg1));
  RooFormulaVar subBkgSRyield("subBkgSRyield","@0*@1",RooArgList(*subBkgIntegralSR,nbkg2));
  RooFormulaVar lowerSIGyield("lowerSIGyield","extrapolation to lowerSIG","@0+@1", RooArgList(domBkgSRyield,subBkgSRyield));
  Double_t bkgYield       =     lowerSIGyield.getVal(); 
  Double_t bkgYield_error = 1 + lowerSIGyield.getPropagatedError(*erf)/bkgYield;
  RooRealVar ZZ_bkg_eig_norm("ZZ_bkg_eig_norm","expected yield in lowerSIG",bkgYield,0.,1.e4);

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

  candMass.setRange("range", 500., 5300);
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE), PrintLevel(-1));

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
  low[600]  =  500.;
  low[800]  =  600.;
  low[1000] =  800.;
  low[1200] = 1000.;
  low[1400] = 1100.;
  low[1600] = 1300.;
  low[1800] = 1400.;
  low[2000] = 1600.;
  low[2500] = 2000.;
  low[3000] = 2400.;
  low[3500] = 2900.;
  low[4000] = 3200.;
  low[4500] = 3700.;

  std::map<Int_t, Double_t> upp;
  upp[600]  =  700.;
  upp[800]  = 1000.;
  upp[1000] = 1200.;
  upp[1200] = 1400.;
  upp[1400] = 1700.;
  upp[1600] = 1900.;
  upp[1800] = 2200.;
  upp[2000] = 2500.;
  upp[2500] = 3000.;
  upp[3000] = 3600.;
  upp[3500] = 4000.;
  upp[4000] = 4800.;
  upp[4500] = 5300.;

  TChain bulkG("treeDumper/EDBRCandidates");
  bulkG.Add(inputFile[mass].c_str());
  RooDataSet dsSig("dsSig","dsSig",RooArgSet(candMass,massVhad,tau21,lep),Cut(lowerSIG),Import(bulkG));

  // Double Crystall ball
  RooRealVar mean("mean","mean of the Crystal Ball",mass,low[mass],upp[mass]);
  RooRealVar sigma("sigma","Crystal Ball sigma",50.,10.,100.);
  RooRealVar alphaL("alphaL","alpha left",  1., 0.1, 5.);
  RooRealVar alphaR("alphaR","alpha right", 2., 0.1, 5.);
  RooRealVar nL("nL","n left", 30., 0.1, 50.);
  RooRealVar nR("nR","n right", 1., 0.1,  5.);
  RooDoubleCrystalBall ZZ_sig("ZZ_sig","Double Crystall Ball",candMass,mean,sigma,alphaL,nL,alphaR,nR);
  ZZ_sig.fitTo(dsSig, Minimizer("Minuit"), Range(low[mass],upp[mass]), SumW2Error(kTRUE), PrintLevel(-1));
  mean.setConstant(true);
  sigma.setConstant(true);
  alphaL.setConstant(true);
  alphaR.setConstant(true);
  nL.setConstant(true);
  nR.setConstant(true);

  // Total number of signal events in the sample 
  std::map<Int_t, Int_t> nEvents;
  nEvents[600]  = 50000;
  nEvents[800]  = 50000;
  nEvents[1000] = 50000;
  nEvents[1200] = 50000;
  nEvents[1400] = 49200;
  nEvents[1600] = 50000;
  nEvents[1800] = 48400;
  nEvents[2000] = 50000;
  nEvents[2500] = 50000;
  nEvents[3000] = 50000;
  nEvents[3500] = 50000;
  nEvents[4000] = 50000;
  nEvents[4500] = 50000;

  // selection efficiency
  Double_t sel_eff = (Double_t)dsSig.numEntries()/nEvents[mass];
  Double_t sig_xs_fb = 1.;           // signal cross section in fb
  Double_t target_lumi_fbInv = 2.63; // target luminosity in fb^-1
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
  RooDataSet data_obs("data_obs","data_obs",variables,Cut(lowerSIG),Import(treeData));
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
  ofs << Form("ZZ_bkg_eig_norm                lnU       %-10s    %.2f\n", "1.",  bkgYield_error );
  ofs << Form("lumi_13TeV                     lnN       %-10s    %s\n", "1.05",  "1." );
  ofs << Form("CMS_eff_vtag_tau21_sf_13TeV    lnN       %-10s    %s\n", "1.1" ,  "1." );
  ofs << Form("CMS_scale_j_13TeV              lnN       %-10s    %s\n", "1.01",  "1." );
  ofs << Form("CMS_scale_%c_13TeV              lnN       %-10s    %s\n", key[0], lepton_scale.c_str(),  "1." );
  ofs << Form("eig_eig0                     param       %-10s    %s\n", "0.",    "1." );
  ofs << Form("eig_eig1                     param       %-10s    %s\n", "0.",    "1." );
  ofs << Form("eig_eig2                     param       %-10s    %s\n", "0.",    "1." );
  ofs << Form("eig_eig3                     param       %-10s    %s\n", "0.",    "1." );
  ofs << Form("eig_eig4                     param       %-10s    %s\n", "0.",    "1." );
  ofs << Form("eig_eig5                     param       %-10s    %s\n", "0.",    "1." );

  ofs.close();
}
