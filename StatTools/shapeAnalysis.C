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

  RooRealVar candMass("candMass","M_{VZ}",            600., 4800., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,             45.,  220., "GeV");
  RooRealVar tau21("tau21","tau21",                     0.,    1.       );
  RooRealVar lep("lep","lep",                           10,    15       );
  RooRealVar totalWeight("totalWeight", "total weight", 0.,    10.      );
  RooArgSet variables(candMass,massVhad,tau21,lep,totalWeight);

  massVhad.setRange("lowerSB",      45.,   65.);
  massVhad.setRange("lowerSIG",     65.,  105.);
  massVhad.setRange("upperSIG",    105.,  135.);
  massVhad.setRange("upperSB",     135.,  220.);

  std::map<std::string, std::string> selection;
  selection["ENP"] = "candMass>600 && lep<12";
  selection["MNP"] = "candMass>600 && lep>12";
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
      treeData.Add(     "../elTrees/nov13/treeEDBR_SingleElectron.root"              ); 
      treeMC2.Add(      "../elTrees/nov13/treeEDBR_WZ.root"                          );
      treeMC2.Add(      "../elTrees/nov13/treeEDBR_ZZ.root"                          );
      treeMC2.Add(      "../elTrees/nov13/treeEDBR_T_T.root"                         );
      treeMC1.Add(      "../elTrees/nov13/treeEDBR_DYJetsToLL_HT-100to200.root"      );
      treeMC1.Add(      "../elTrees/nov13/treeEDBR_DYJetsToLL_HT-200to400.root"      );
      treeMC1.Add(      "../elTrees/nov13/treeEDBR_DYJetsToLL_HT-400to600.root"      );
      treeMC1.Add(      "../elTrees/nov13/treeEDBR_DYJetsToLL_HT-600toInf.root"      );
      inputFile[800]  = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-800.root" ;
      inputFile[1000] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1000.root";
      inputFile[1200] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1200.root";
      inputFile[1400] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1400.root";
      inputFile[1600] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1600.root";
      inputFile[1800] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1800.root";
      inputFile[2000] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-2000.root";
      inputFile[2500] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-2500.root";
      inputFile[3000] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-3000.root";
      inputFile[3500] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-3500.root";
      inputFile[4000] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-4000.root";
      inputFile[4500] = "../elTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-4500.root";
      lepton_scale    = "1.005";
  }

  if( key[0]=='M' ){
      treeData.Add(     "../muTrees/nov13/treeEDBR_SingleMuon.root"                  ); 
      treeMC2.Add(      "../muTrees/nov13/treeEDBR_WZ.root"                          );
      treeMC2.Add(      "../muTrees/nov13/treeEDBR_ZZ.root"                          );
      treeMC2.Add(      "../muTrees/nov13/treeEDBR_T_T.root"                         );
      treeMC1.Add(      "../muTrees/nov13/treeEDBR_DYJetsToLL_HT-100to200.root"      );
      treeMC1.Add(      "../muTrees/nov13/treeEDBR_DYJetsToLL_HT-200to400.root"      );
      treeMC1.Add(      "../muTrees/nov13/treeEDBR_DYJetsToLL_HT-400to600.root"      );
      treeMC1.Add(      "../muTrees/nov13/treeEDBR_DYJetsToLL_HT-600toInf.root"      );
      inputFile[800]  = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-800.root" ;
      inputFile[1000] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1000.root";
      inputFile[1200] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1200.root";
      inputFile[1400] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1400.root";
      inputFile[1600] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1600.root";
      inputFile[1800] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-1800.root";
      inputFile[2000] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-2000.root";
      inputFile[2500] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-2500.root";
      inputFile[3000] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-3000.root";
      inputFile[3500] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-3500.root";
      inputFile[4000] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-4000.root";
      inputFile[4500] = "../muTrees/nov13/treeEDBR_BulkGravToZZToZlepZhad_M-4500.root";
      lepton_scale    = "1.03";
  }

  // dataset to host data in sideband
  RooDataSet sbObs("sbObs","sbObs", variables, Cut(allSB), Import(treeData));

  // MC datasets
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC1));
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC2));
  RooRealVar coef("coef", "coef", bkg2.sumEntries()/bkg1.sumEntries(),0.,1.);
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
  model1.fitTo(bkg1, Range("lowerSB,lowerSIG,upperSIG,upperSB"),PrintLevel(-1));
  model2.fitTo(bkg2, Range("lowerSB,lowerSIG,upperSIG,upperSB"),PrintLevel(-1));
  // Final background model
  RooAddPdf model("model","model",RooArgList(model2,model1),coef);
  c1.setConstant(true);
  c2.setConstant(true);
  offset1.setConstant(true);
  offset2.setConstant(true);
  width1.setConstant(true);
  width2.setConstant(true);
  // Extended model
  RooRealVar yieldLowerSB( "lower SB",  "Lower SB normalization",  10, 1., 1.e3);
  RooExtendPdf model_ext( "model_ext", "extended p.d.f",   model,  yieldLowerSB);
  model_ext.fitTo(sbObs,ConditionalObservables(RooArgSet(massVhad)),Extended(kTRUE),Range("lowerSB"),PrintLevel(-1));

  // Calculate integral of the model
  RooAbsReal* nSIG1 = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* nSB1  = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB"));
  Double_t scale1   = nSIG1->getVal()/nSB1->getVal(); // scale from lower sideband to lower signal reg
  Double_t bkgYield       = yieldLowerSB.getVal()   * scale1; 
  Double_t bkgYield_error = yieldLowerSB.getError() * scale1;

  RooRealVar ZZ_bkg_eig_norm("ZZ_bkg_eig_norm", "normalization in signal reg", 10., 1., 1.e4);
  ZZ_bkg_eig_norm.setVal(   bkgYield );
  ZZ_bkg_eig_norm.setError( bkgYield_error );
  ZZ_bkg_eig_norm.setConstant(true);

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
  RooDataSet bigSample("bigSample","bigSample", variables, WeightVar(totalWeight), Index(reg), Import("nsMC",nsBkg), Import("sbMC",sbBkg), Import("sbDA",sbObs));
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(nsBkg_pdf,sbBkg_pdf,sbObs_pdf), reg); 
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
  Double_t sig_xs_fb = 1.;            // signal cross section in fb
  Double_t target_lumi_fbInv = 2.093; // target luminosity in fb^-1
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
