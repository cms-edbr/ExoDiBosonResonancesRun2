// ROOFIT macro to build a double Crystal-Ball model
//
// Usage: root signalFit.C
//
// Jan 16 2015


void signalFit()
{
  TFile *file = TFile::Open("treeEDBR_RSGravToZZ_kMpl01_M-4000.root");
  TTree *t0;
  file->GetObject("treeDumper/EDBRCandidates",t0);

  RooRealVar numCands("numCands", "number of candidates", 0., 100.);
  RooRealVar lep("lep", "leptonic number", 0., 100.);
  RooRealVar lumiWeight("lumiWeight", "pure weight", 0., 10.);
  RooRealVar candMass("candMass","M_{ZZ}", 100.,7100., "GeV");
  const char* elCh = "numCands>0 && lep<12";
  const char* muCh = "numCands>0 && lep>12";
  // The muon and electron channels are considered separately  
  RooDataSet elds("elds","elds",RooArgSet(candMass,numCands,lep,lumiWeight),RooFit::Cut(elCh),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  RooDataSet muds("muds","muds",RooArgSet(candMass,numCands,lep,lumiWeight),RooFit::Cut(muCh),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  RooRealVar mean("mean","mean of the Crystal Ball",4000.,100.,7100.);
  RooRealVar sigma("sigma","Crystal Ball sigma",100.,10.,1000.);
  RooRealVar alphaL("alphaL","alpha left",  1.,  0.,10.);
  RooRealVar alphaR("alphaR","alpha right",-1.,-10., 0.);
  RooRealVar nL("nL","n left", 3.,0.,10.);
  RooRealVar nR("nR","n right",3.,0.,10.);
  // Build Crystal Ball for the left tail
  RooCBShape cbL("cbL","Left Crystal Ball PDF",candMass,mean,sigma,alphaL,nL);
  // Build Crystal Ball for the right tail
  RooCBShape cbR("cb","Right Crystal Ball PDF",candMass,mean,sigma,alphaR,nR);
  // Add the previous PDFs to build the Double Crystall Ball
  RooRealVar frac("frac","fraction",0.5);
  RooAddPdf cbLR("cbLR","Double Crystall Ball",RooArgList(cbL,cbR),frac);

  TCanvas *c1 = new TCanvas("c1","c1", 1400, 700);
  c1->Divide(2,1);
  c1->cd(1);
  RooPlot* frame1 = candMass.frame(RooFit::Title("CMS Preliminary     #sqrt{s} = 13 TeV     #int L dt = 3 fb^{-1}") );
  muds.plotOn(frame1); 
  cbLR.fitTo(muds,RooFit::Range(2500.,6000.));
  cbLR.plotOn(frame1,RooFit::LineColor(kRed)); 
  gPad->SetGridx();
  gPad->SetGridy();
  frame1->Draw();
  frame1->GetYaxis()->SetTitle();
  TLegend *leg1 = new TLegend(0.13,0.7,0.4,0.88);
  leg1->AddEntry("h_muds","MC signal","ep");
  leg1->AddEntry("cbLR_Norm[candMass]_Range[fit_nll_cbLR_muds]_NormRange[fit_nll_cbLR_muds]","Fit model","l");
  leg1->Draw(); 
  TPaveText *pt1 = new TPaveText(0.6,0.7,0.88,0.88,"NDC");
  pt1->SetFillColor(0);
  pt1->SetBorderSize(1);
  pt1->SetTextFont(42);
  pt1->AddText("muon channel");
  pt1->AddText(Form("#chi^{2} / ndf  :  %.1f / 6",6.*frame1->chiSquare(6)));
  pt1->Draw();

  c1->cd(2);
  RooPlot* frame2 = candMass.frame(RooFit::Title("CMS Preliminary     #sqrt{s} = 13 TeV     #int L dt = 3 fb^{-1}") );
  elds.plotOn(frame2); 
  cbLR.fitTo(elds,RooFit::Range(2500.,6000.));
  cbLR.plotOn(frame2,RooFit::LineColor(kRed)); 
  gPad->SetGridx();
  gPad->SetGridy();
  frame2->Draw();
  frame2->GetYaxis()->SetTitle();
  TLegend *leg2 = new TLegend(0.13,0.7,0.4,0.88);
  leg2->AddEntry("h_elds","MC signal","ep");
  leg2->AddEntry("cbLR_Norm[candMass]_Range[fit_nll_cbLR_muds,fit_nll_cbLR_elds]_NormRange[fit_nll_cbLR_muds,fit_nll_cbLR_elds]","Fit model","l");
  leg2->Draw(); 
  TPaveText *pt2 = new TPaveText(0.6,0.7,0.88,0.88,"NDC");
  pt2->SetFillColor(0);
  pt2->SetBorderSize(1);
  pt2->SetTextFont(42);
  pt2->AddText("electron channel");
  pt2->AddText(Form("#chi^{2} / ndf  :  %.1f / 6",6.*frame2->chiSquare(6)));
  pt2->Draw();

}
