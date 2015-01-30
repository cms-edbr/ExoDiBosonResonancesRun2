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
  RooRealVar tau21("tau21", "n-subjettiness", 0., 1.);
  RooRealVar lumiWeight("lumiWeight", "pure weight", 0., 10.);
  RooRealVar candMass("candMass","M_{ZZ}", 100.,7100., "GeV");
  const char* elLo = "numCands>0 && lep<12 && tau21<0.5";
  const char* muLo = "numCands>0 && lep>12 && tau21<0.5";
  const char* elHi = "numCands>0 && lep<12 && tau21>0.5 && tau21<0.75";
  const char* muHi = "numCands>0 && lep>12 && tau21>0.5 && tau21<0.75";
  // The muon and electron channels are considered separately  
  RooDataSet elLods("elLods","elLods",RooArgSet(candMass,numCands,lep,tau21,lumiWeight),RooFit::Cut(elLo),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  RooDataSet muLods("muLods","muLods",RooArgSet(candMass,numCands,lep,tau21,lumiWeight),RooFit::Cut(muLo),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  RooDataSet elHids("elHids","elHids",RooArgSet(candMass,numCands,lep,tau21,lumiWeight),RooFit::Cut(elHi),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  RooDataSet muHids("muHids","muHids",RooArgSet(candMass,numCands,lep,tau21,lumiWeight),RooFit::Cut(muHi),RooFit::WeightVar(lumiWeight),RooFit::Import(*t0));
  RooRealVar mean("mean","mean of the Crystal Ball",4000.,100.,7100.);
  RooRealVar sigma("sigma","Crystal Ball sigma",100.,10.,1000.);
  RooRealVar alphaL("alphaL","alpha left",  1.,  0.,10.);
  RooRealVar alphaR("alphaR","alpha right",-1.,-10., 0.);
  RooRealVar nL("nL","n left", 3.,0.,10.);
  RooRealVar nR("nR","n right",3.,0.,10.);
  // Build Crystal Ball for the left tail
  RooCBShape cbL("cbL","Left Crystal Ball PDF",candMass,mean,sigma,alphaL,nL);
  // Build Crystal Ball for the right tail
  RooCBShape cbR("cbR","Right Crystal Ball PDF",candMass,mean,sigma,alphaR,nR);
  // Add the previous PDFs to build the Double Crystall Ball
  RooRealVar frac("frac","fraction",0.5);
  RooAddPdf cbLR("cbLR","Double Crystall Ball",RooArgList(cbL,cbR),frac);

  TCanvas *c1 = new TCanvas("c1","c1", 1200, 900);
  c1->Divide(2,2,0.00001,0.01);
  c1->cd(1);
  RooPlot* frame1 = candMass.frame(RooFit::Title("CMS Preliminary     #sqrt{s} = 13 TeV     #int L dt = 3 fb^{-1}") );
  muLods.plotOn(frame1); 
  cbLR.fitTo(muLods,RooFit::Range(2500.,5500.));
  cbLR.plotOn(frame1,RooFit::LineColor(kRed)); 
  gPad->SetGridx();
  gPad->SetGridy();
  frame1->Draw();
  frame1->GetYaxis()->SetTitle();
  frame1->GetXaxis()->SetTitleSize(0.045);
  frame1->GetXaxis()->SetLabelSize(0.045);
  TLegend *leg1 = new TLegend(0.13,0.7,0.4,0.88);
  leg1->AddEntry("h_muLods","MC signal","ep");
  leg1->AddEntry("cbLR_Norm[candMass]_Range[fit_nll_cbLR_muLods]_NormRange[fit_nll_cbLR_muLods]","Fit model","l");
  leg1->Draw(); 
  TPaveText *pt1 = new TPaveText(0.63,0.61,0.88,0.88,"NDC");
  pt1->SetFillColor(0);
  pt1->SetBorderSize(1);
  pt1->SetTextFont(42);
  pt1->AddText("muon channel");
  pt1->AddText("#tau_{21} < 0.5");
  pt1->AddText(Form("#chi^{2} / ndf  :  %.2f",frame1->chiSquare(6)));
  pt1->Draw();

  c1->cd(2);
  RooPlot* frame2 = candMass.frame(RooFit::Title("CMS Preliminary     #sqrt{s} = 13 TeV     #int L dt = 3 fb^{-1}") );
  elLods.plotOn(frame2); 
  cbLR.fitTo(elLods,RooFit::Range(2500.,5500.));
  cbLR.plotOn(frame2,RooFit::LineColor(kRed)); 
  gPad->SetGridx();
  gPad->SetGridy();
  frame2->Draw();
  frame2->GetYaxis()->SetTitle();
  frame2->GetXaxis()->SetTitleSize(0.045);
  frame2->GetXaxis()->SetLabelSize(0.045);
  TLegend *leg2 = new TLegend(0.13,0.7,0.4,0.88);
  leg2->AddEntry("h_elLods","MC signal","ep");
  leg2->AddEntry("cbLR_Norm[candMass]_Range[fit_nll_cbLR_muLods,fit_nll_cbLR_elLods]_NormRange[fit_nll_cbLR_muLods,fit_nll_cbLR_elLods]","Fit model","l");
  leg2->Draw(); 
  TPaveText *pt2 = new TPaveText(0.6,0.61,0.88,0.88,"NDC");
  pt2->SetFillColor(0);
  pt2->SetBorderSize(1);
  pt2->SetTextFont(42);
  pt2->AddText("electron channel");
  pt2->AddText("#tau_{21} < 0.5");
  pt2->AddText(Form("#chi^{2} / ndf  :  %.2f",frame2->chiSquare(6)));
  pt2->Draw();

  c1->cd(3);
  RooPlot* frame3 = candMass.frame(RooFit::Title("CMS Preliminary     #sqrt{s} = 13 TeV     #int L dt = 3 fb^{-1}") );
  muHids.plotOn(frame3); 
  cbLR.fitTo(muHids,RooFit::Range(2500.,5500.));
  cbLR.plotOn(frame3,RooFit::LineColor(kRed)); 
  gPad->SetGridx();
  gPad->SetGridy();
  frame3->Draw();
  frame3->GetYaxis()->SetTitle();
  frame3->GetXaxis()->SetTitleSize(0.045);
  frame3->GetXaxis()->SetLabelSize(0.045);
  TLegend *leg3 = new TLegend(0.13,0.7,0.4,0.88);
  leg3->AddEntry("h_muHids","MC signal","ep");
  leg3->AddEntry("cbLR_Norm[candMass]_Range[fit_nll_cbLR_muLods,fit_nll_cbLR_elLods,fit_nll_cbLR_muHids]_NormRange[fit_nll_cbLR_muLods,fit_nll_cbLR_elLods,fit_nll_cbLR_muHids]","Fit model","l");
  leg3->Draw(); 
  TPaveText *pt3 = new TPaveText(0.63,0.61,0.88,0.88,"NDC");
  pt3->SetFillColor(0);
  pt3->SetBorderSize(1);
  pt3->SetTextFont(42);
  pt3->AddText("muon channel");
  pt3->AddText("0.5 < #tau_{21} < 0.75");
  pt3->AddText(Form("#chi^{2} / ndf  :  %.2f",frame3->chiSquare(6)));
  pt3->Draw();

  c1->cd(4);
  RooPlot* frame4 = candMass.frame(RooFit::Title("CMS Preliminary     #sqrt{s} = 13 TeV     #int L dt = 3 fb^{-1}") );
  elHids.plotOn(frame4); 
  cbLR.fitTo(elHids,RooFit::Range(2500.,5500.));
  cbLR.plotOn(frame4,RooFit::LineColor(kRed)); 
  gPad->SetGridx();
  gPad->SetGridy();
  frame4->Draw();
  frame4->GetYaxis()->SetTitle();
  frame4->GetXaxis()->SetTitleSize(0.045);
  frame4->GetXaxis()->SetLabelSize(0.045);
  TLegend *leg4 = new TLegend(0.13,0.7,0.4,0.88);
  leg4->AddEntry("h_elHids","MC signal","ep");
  leg4->AddEntry("cbLR_Norm[candMass]_Range[fit_nll_cbLR_muLods,fit_nll_cbLR_elLods,fit_nll_cbLR_muHids,fit_nll_cbLR_elHids]_NormRange[fit_nll_cbLR_muLods,fit_nll_cbLR_elLods,fit_nll_cbLR_muHids,fit_nll_cbLR_elHids]","Fit model","l");
  leg4->Draw(); 
  TPaveText *pt4 = new TPaveText(0.6,0.61,0.88,0.88,"NDC");
  pt4->SetFillColor(0);
  pt4->SetBorderSize(1);
  pt4->SetTextFont(42);
  pt4->AddText("electron channel");
  pt4->AddText("0.5 < #tau_{21} < 0.75");
  pt4->AddText(Form("#chi^{2} / ndf  :  %.2f",frame4->chiSquare(6)));
  pt4->Draw();

}
