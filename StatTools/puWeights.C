// Create histogram with pileup weights

void puWeights(){
 
  TFile *temp = new TFile("pileupWeights.root", "RECREATE");
  using namespace RooFit;
  
  float weightData = 1000./209.8;
  float inix= 0.;
  float finx= 45.;
  int nbinx = 15.; 
   
  TChain treeData("treeDumper/EDBRCandidates");
  treeData.Add("treeEDBR_SingleMuon_Run2015D.root"); 
  treeData.Add("treeEDBR_SingleElectron_Run2015D.root");
  
  RooRealVar nVtx("nVtx","number of vertices", inix, finx);
  RooRealVar lumiWeight("lumiWeight", "pure weight", 0., 10.);
  RooRealVar massVhad("massVhad", "jet mass", 0., 110.);
  
  RooDataSet vtxData("vtxData","vtxData",RooArgSet(nVtx),Import(treeData));
  RooRealVar x("x","x",weightData,0.,10.);
  RooFormulaVar wFunc("w","event weight","x",x);
  RooRealVar* w = (RooRealVar*) vtxData.addColumn(wFunc) ;
  
  RooDataSet wdata(vtxData.GetName(), vtxData.GetTitle(), &vtxData, *vtxData.get(),0,w->GetName());
  wdata.Print();
  
  TChain treeMC("treeDumper/EDBRCandidates");
  treeMC.Add("treeEDBR_DYJets_ToLL.root");
  treeMC.Add("treeEDBR_Di_boson.root");
  treeMC.Add("treeEDBR_T_T.root");
  
  RooDataSet vtxMC("vtxMC","vtxMC",RooArgSet(nVtx,lumiWeight,massVhad),Cut("massVhad<65"),WeightVar(lumiWeight),Import(treeMC));
  vtxMC.Print();
  
  RooBinning xbins(nbinx, inix, finx);
  
  //RooPlot *plot = nVtx.frame();
  //vtxMC.plotOn(plot, Binning(xbins));
  //wdata.plotOn(plot, LineColor(kRed), Binning(xbins));
  //plot->Draw();
  
  TH1* pileupWeights = wdata.createHistogram("pileupWeights",nVtx,Binning(xbins));
  TH1* hMC = vtxMC.createHistogram("hMC",nVtx,Binning(xbins));
  pileupWeights->Divide(hMC);
  
  temp->cd();
  pileupWeights->Write();
  temp->Close();
  delete temp;
}
