// 
// Usage: root -b -q 'plotLimit.C("EHP")'
//        root -b -q 'plotLimit.C("ELP")'
//        root -b -q 'plotLimit.C("MHP")'
//        root -b -q 'plotLimit.C("MLP")'
//

void plotLimit(std::string key)
{
  std::map<std::string, std::string> inputFile;
  inputFile["EHP"]="combineEHP.root";
  inputFile["ELP"]="combineELP.root";
  inputFile["MHP"]="combineMHP.root";
  inputFile["MLP"]="combineMLP.root";

  std::map<std::string, std::string> outFile;
  outFile["EHP"]="limitEHP.pdf";
  outFile["ELP"]="limitELP.pdf";
  outFile["MHP"]="limitMHP.pdf";
  outFile["MLP"]="limitMLP.pdf";

  std::map<std::string, std::string> legTitle;
  legTitle["EHP"]="electron channel high purity";
  legTitle["ELP"]="electron channel low purity";
  legTitle["MHP"]="muon channel high purity";
  legTitle["MLP"]="muon channel low purity";

  std::map<std::string, std::string> axisTitle;
  axisTitle["EHP"]="ee";
  axisTitle["ELP"]="ee";
  axisTitle["MHP"]="#mu#mu";
  axisTitle["MLP"]="#mu#mu";
 
  TFile *f = TFile::Open(inputFile[key].c_str());
  TTreeReader myReader("limit", f);
  TTreeReaderValue<Double_t> limit(myReader, "limit");
  vector<Double_t> y0, y1, y2, y3, y4;
  Int_t i=0;
  while(myReader.Next()){
    switch ( i%6 ){
      case 0 : y0.push_back(*limit); break;
      case 1 : y1.push_back(*limit); break;
      case 2 : y2.push_back(*limit); break;
      case 3 : y3.push_back(*limit); break;
      case 4 : y4.push_back(*limit); break;
    }
    i++;
  }
  Double_t l1[4], l2[4], h1[4], h2[4];
  for(int j=0; j<y0.size(); j++){
     l1[j] = y2[j]-y1[j];
     l2[j] = y2[j]-y0[j];
     h1[j] = y3[j]-y2[j];
     h2[j] = y4[j]-y2[j];
  }

  Double_t x[4]={1000.,2000.,3000.,4000.};
  Double_t n[4]={   0.,   0.,   0.,   0.};
  TGraph *gr0 = new TGraph(y0.size(),x,&(y2[0]));
  gr0->SetLineStyle(2);
  gr0->SetLineWidth(2);
  gr0->SetMarkerStyle(21);
 
  TGraphAsymmErrors *gr1 = new TGraphAsymmErrors(y0.size(),x,&(y2[0]),n,n,l1,h1);
  TGraphAsymmErrors *gr2 = new TGraphAsymmErrors(y0.size(),x,&(y2[0]),n,n,l2,h2);
  gr1->SetFillStyle(1001);
  gr2->SetFillStyle(1001);
  gr1->SetFillColor(3);
  gr2->SetFillColor(5);
  gr2->GetYaxis()->SetTitleOffset(1.2);
  gr2->SetMinimum(4.);
  gr2->SetMaximum(2.e3);
  gr2->SetTitle(Form("#bf{CMS} Preliminary   #sqrt{s} = 13 TeV    #int L dt = 1 fb^{-1};M_{ZZ} [GeV];\
                     #sigma_{95%%} #times BR(G #rightarrow ZZ #rightarrow %sj ) [fb]",
                     axisTitle[key].c_str() ));

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  gr2->Draw("A3");
  gr1->Draw("same3");
  gr0->Draw("sameCP");

  TLegend *leg = new TLegend(0.45,0.68,0.9,0.9);
  leg->SetHeader(legTitle[key].c_str());
  leg->AddEntry(gr0,"expected 95% C.L. upper limit","lp");
  leg->AddEntry(gr1,"expected #pm 1#sigma","f");
  leg->AddEntry(gr2,"expected #pm 2#sigma","f");
  leg->Draw();
  TLegendEntry *header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
  header->SetTextAlign(22);
  header->SetTextColor(2);
  header->SetTextSize(.04);

  c1->Print(outFile[key].c_str());
}
