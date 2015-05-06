void backgroundFit()
{
  TFile *file = TFile::Open("treeDYJetsToLL_all.root");
  TTree *t0;
  file->GetObject("treeDumper/EDBRCandidates",t0);

  RooRealVar candMass("candMass","M_{ZZ}", 500.,3000., "GeV");
  RooRealVar lumiWeight("lumiWeight", "pure weight", 0., 10.);

  // Weighted dataset
  RooDataSet wds("wds","wds",RooArgSet(candMass,lumiWeight),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  wds.Print();
  
  // Build exponential p.d.f.

  RooRealVar p0("p0","parameter 0",500., 1. , 1.e3);
  RooRealVar p1("p1","parameter 1",  0.,-1. ,   1.);
  RooGenericPdf expo("expo","leveled exponential PDF","exp(-candMass/(p0+p1*candMass))",RooArgSet(candMass,p0,p1));

  expo.fitTo(wds);

  // Plot data and fit function in the same frame 

  RooPlot* frame1 = candMass.frame(RooFit::Title("CMS Preliminary     #sqrt{s} = 13 TeV     #int L dt = 3 fb^{-1}") );
  wds.plotOn(frame1); 
  expo.plotOn(frame1,RooFit::LineColor(kRed)); 
  expo.paramOn(frame1,RooFit::Layout(0.45,0.9,0.6));

  TCanvas *c1 = new TCanvas("c1","c1", 700, 700);
  c1->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  frame1->Draw();
  frame1->getAttText()->SetTextFont(42);
  frame1->getAttText()->SetTextSize(0.035);
  frame1->GetYaxis()->SetTitleOffset(1.1);

  TLegend *leg = new TLegend(0.45,0.6,0.9,0.9);
  leg->AddEntry("h_wds","MC background","ep");
  leg->AddEntry("expo_Norm[candMass]","Fit function","l");
  leg->AddEntry((TObject*)0,"exp#left[#minus x / (p_{0} #plus p_{1}x)#right]","");
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->Draw(); 

  c1->Print("backgroundFit.pdf");
}
