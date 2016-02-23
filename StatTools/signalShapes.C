R__LOAD_LIBRARY(PDFs/HWWLVJRooPdfs_cxx.so)

void signalShapes(std::string key){

  using namespace RooFit;

  std::map<std::string, std::string> selection;
  selection["EHP"] = "lep<12 && tau21<0.45";
  selection["MHP"] = "lep>12 && tau21<0.45";
  selection["ELP"] = "lep<12 && tau21>0.45";
  selection["MLP"] = "lep>12 && tau21>0.45";

  TCut mycut = selection[key].c_str();

  std::vector<std::string> files;

  if( key[0]=='E' ){ 
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-4000_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3500_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3000_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2500_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2000_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1800_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1600_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1400_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1200_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1000_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-800_el.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-600_el.root");
  }

  if( key[0]=='M' ){ 
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-4000_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3500_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3000_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2500_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2000_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1800_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1600_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1400_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1200_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1000_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-800_mu.root");
    files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-600_mu.root");
  }

  RooRealVar candMass("candMass","VZ candidate mass", 550., 5000., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,             65.,  105., "GeV");
  RooRealVar tau21("tau21","tau21",                     0.,  0.75       );
  RooRealVar lep("lep","lep",                           10,    15       );
  RooRealVar pileupWeight("pileupWeight","pileup",      0.,    10.      );
  RooArgSet variables(candMass,massVhad,tau21,lep,pileupWeight);

  std::map<std::string, Double_t> low, Mass, upp;
  low["600"]  =  550.; Mass["600"]  =  600.; upp["600"]  =  700.;
  low["800"]  =  600.; Mass["800"]  =  800.; upp["800"]  = 1000.;
  low["1000"] =  800.; Mass["1000"] = 1000.; upp["1000"] = 1200.;
  low["1200"] = 1000.; Mass["1200"] = 1200.; upp["1200"] = 1400.;
  low["1400"] = 1100.; Mass["1400"] = 1400.; upp["1400"] = 1700.;
  low["1600"] = 1300.; Mass["1600"] = 1600.; upp["1600"] = 1900.;
  low["1800"] = 1400.; Mass["1800"] = 1800.; upp["1800"] = 2200.;
  low["2000"] = 1600.; Mass["2000"] = 2000.; upp["2000"] = 2500.;
  low["2500"] = 2000.; Mass["2500"] = 2500.; upp["2500"] = 3000.;
  low["3000"] = 2500.; Mass["3000"] = 3000.; upp["3000"] = 3500.;
  low["3500"] = 3000.; Mass["3500"] = 3500.; upp["3500"] = 4000.;
  low["4000"] = 3500.; Mass["4000"] = 4000.; upp["4000"] = 4500.;
  low["4500"] = 4000.; Mass["4500"] = 4500.; upp["4500"] = 5000.;

  // Total number of signal events in the sample 
  std::map<std::string, Int_t> nEvents;
  nEvents["600"]  = 50000;
  nEvents["800"]  = 50000;
  nEvents["1000"] = 50000;
  nEvents["1200"] = 50000;
  nEvents["1400"] = 49200;
  nEvents["1600"] = 50000;
  nEvents["1800"] = 50000;
  nEvents["2000"] = 48400;
  nEvents["2500"] = 50000;
  nEvents["3000"] = 50000;
  nEvents["3500"] = 50000;
  nEvents["4000"] = 50000;
  nEvents["4500"] = 50000;

  std::vector<double> MEAN, SIGMA, ALPHAL, ALPHAR, EFF;

   // Double Crystall ball
  RooRealVar mean("mean","mean of the Crystal Ball",600.,500.,5000.);
  RooRealVar sigma("sigma","Crystal Ball sigma",50.,10.,100.);
  RooRealVar alphaL("alphaL","alpha left",  1.5, 1., 3.);
  RooRealVar alphaR("alphaR","alpha right", 3.0, 1., 5.);
  RooRealVar nL("nL","n left", 2.,1., 2.); nL.setConstant(true); 
  RooRealVar nR("nR","n right",2.,1., 2.); nR.setConstant(true);

  while( !files.empty() ){
     std::string mass = files.back().substr(40,4);
     if(mass[3]=='_') mass.pop_back();
     mean.setVal(Mass[mass]);
     mean.setRange(low[mass],upp[mass]);
     RooDoubleCrystalBall ZZ_sig("ZZ_sig","Double Crystall Ball",candMass,mean,sigma,alphaL,nL,alphaR,nR);
 
     TChain t("treeDumper/EDBRCandidates");
     t.Add(files.back().c_str());

     RooDataSet ds("ds","ds",variables,WeightVar(pileupWeight),Cut(mycut),Import(t));
     // selection efficiency
     EFF.push_back( (double)ds.numEntries()/nEvents[mass] );
    
     ZZ_sig.fitTo(ds, Minimizer("Minuit"), Range(low[mass],upp[mass]), SumW2Error(kTRUE), PrintLevel(-1));
     MEAN.push_back(     mean.getVal() );
     SIGMA.push_back(   sigma.getVal() );
     ALPHAL.push_back( alphaL.getVal() );
     ALPHAR.push_back( alphaR.getVal() );

     files.pop_back();
  }

  Double_t x[12]={600.,800.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,3500.,4000.};
  TGraph *gmean   = new TGraph(12, x, &(MEAN[0])   );
  TGraph *gsigma  = new TGraph(12, x, &(SIGMA[0])  );
  TGraph *galphaL = new TGraph(12, x, &(ALPHAL[0]) );
  TGraph *galphaR = new TGraph(12, x, &(ALPHAR[0]) );
  TGraph *geff    = new TGraph(12, x, &(EFF[0])    );

  RooWorkspace *w = new RooWorkspace("BulkG","workspace");

  for(Double_t i=600.; i<4100.; i+=100.){
     RooRealVar _mean(  Form("mean_%.0f",  i), "mean of the Crystal Ball",600.,550.,5000.);
     RooRealVar _sigma( Form("sigma_%.0f", i), "Crystal Ball sigma",50.,10.,100.);
     RooRealVar _alphaL(Form("alphaL_%.0f",i), "alpha left",  1.5, 1., 3.);
     RooRealVar _alphaR(Form("alphaR_%.0f",i), "alpha right", 3.0, 1., 5.);
     _mean.setVal(   gmean->Eval(   i ) );
     _sigma.setVal(  gsigma->Eval(  i ) );
     _alphaL.setVal( galphaL->Eval( i ) );
     _alphaR.setVal( galphaR->Eval( i ) );
     RooDoubleCrystalBall ZZ_sig(Form("BulkG_%.0f",i),"Double Crystall Ball",candMass,_mean,_sigma,_alphaL,nL,_alphaR,nR);
     _mean.setConstant(   true );
     _sigma.setConstant(  true );
     _alphaL.setConstant( true );
     _alphaR.setConstant( true );
     w->import(ZZ_sig);

     RooRealVar eff(Form("eff_%.0f",i),"signal efficiency", 0.1, 0., 1.);
     eff.setVal( geff->Eval(i) );
     w->import(eff);
  }

  w->writeToFile(Form("workSpaces/BulkG_%s_13TeV.root", key.c_str()));

}
