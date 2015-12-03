// 
// Usage: root -b -q 'plotLimit.C("ENP")'
//        root -b -q 'plotLimit.C("EHP")'
//        root -b -q 'plotLimit.C("ELP")'
//        root -b -q 'plotLimit.C("MNP")'
//        root -b -q 'plotLimit.C("MHP")'
//        root -b -q 'plotLimit.C("MLP")'
//        root -b -q 'plotLimit.C("ALL")'

void plotLimit(std::string key)
{
  std::map<std::string, std::string> inputFile;
  inputFile["ENP"]="combineENP.root";
  inputFile["EHP"]="combineEHP.root";
  inputFile["ELP"]="combineELP.root";
  inputFile["MNP"]="combineMNP.root";
  inputFile["MHP"]="combineMHP.root";
  inputFile["MLP"]="combineMLP.root";
  inputFile["ALL"]="combineALL.root";

  std::map<std::string, std::string> outFile;
  outFile["ENP"]="limitENP.pdf";
  outFile["EHP"]="limitEHP.pdf";
  outFile["ELP"]="limitELP.pdf";
  outFile["MNP"]="limitMNP.pdf";
  outFile["MHP"]="limitMHP.pdf";
  outFile["MLP"]="limitMLP.pdf";
  outFile["ALL"]="limitALL.pdf";

  std::map<std::string, std::string> legTitle;
  legTitle["ENP"]="electron channel";
  legTitle["EHP"]="electron channel high purity";
  legTitle["ELP"]="electron channel low purity";
  legTitle["MNP"]="muon channel";
  legTitle["MHP"]="muon channel high purity";
  legTitle["MLP"]="muon channel low purity";
  legTitle["ALL"]="Combination of channels";

  std::map<std::string, std::string> axisTitle;
  axisTitle["ENP"]="ee";
  axisTitle["EHP"]="ee";
  axisTitle["ELP"]="ee";
  axisTitle["MNP"]="#mu#mu";
  axisTitle["MHP"]="#mu#mu";
  axisTitle["MLP"]="#mu#mu";
  axisTitle["ALL"]="ll";
 
  TFile *f = TFile::Open(inputFile[key].c_str());
  TTreeReader myReader("limit", f);
  TTreeReaderValue<Double_t> limit(myReader, "limit");
  vector<Double_t> y0, y1, y2, y3, y4, y5;
  Int_t i=0;
  while(myReader.Next()){
    switch ( i%6 ){
      case 0 : y0.push_back((*limit)/0.1412042); break;
      case 1 : y1.push_back((*limit)/0.1412042); break;
      case 2 : y2.push_back((*limit)/0.1412042); break;
      case 3 : y3.push_back((*limit)/0.1412042); break;
      case 4 : y4.push_back((*limit)/0.1412042); break;
      case 5 : y5.push_back((*limit)/0.1412042); break;
      //case 0 : y0.push_back((*limit)/0.09408488); break;
      //case 1 : y1.push_back((*limit)/0.09408488); break;
      //case 2 : y2.push_back((*limit)/0.09408488); break;
      //case 3 : y3.push_back((*limit)/0.09408488); break;
      //case 4 : y4.push_back((*limit)/0.09408488); break;
      //case 5 : y5.push_back((*limit)/0.09408488); break;
    }
    i++;
  }
  Double_t l1[11], l2[11], h1[11], h2[11];
  for(int j=0; j<y0.size(); j++){
     l1[j] = y2[j]-y1[j];
     l2[j] = y2[j]-y0[j];
     h1[j] = y3[j]-y2[j];
     h2[j] = y4[j]-y2[j];
  }

  Double_t x[11]={800.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,3500.,4000.};
  Double_t n[11]={  0.,   0.,   0.,   0.,   0.,   0.,   0.,   0.,   0.,   0.,   0.};

  TGraph *gr5 = new TGraph(y0.size(),x,&(y5[0]));
  gr5->SetLineStyle(1);
  gr5->SetLineWidth(2);
  gr5->SetMarkerStyle(20);
  gr5->SetMarkerColor(4);

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
  gr2->SetMinimum(5.e-1);
  gr2->SetMaximum(1.e3);
  gr2->SetTitle("#bf{CMS} Preliminary   #sqrt{s} = 13 TeV    #int L dt = 2.5 fb^{-1};M_{VZ} [GeV];\
                 #sigma_{95%} #times BR(G #rightarrow ZZ) [fb]");
//  gr2->SetTitle(Form("#bf{CMS} Preliminary   #sqrt{s} = 13 TeV    #int L dt = 1.26 fb^{-1};M_{VZ} [GeV];\
//                     #sigma_{95%%} #times BR(G #rightarrow ZZ #rightarrow %sj ) [fb]",
//                     axisTitle[key].c_str() ));

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  gr2->Draw("A3");
  gr1->Draw("same3");
  gr0->Draw("sameCP");
  gr5->Draw("sameCP");

   Double_t bulkToZZ_fx1[16] = {
   200,
   300,
   400,
   500,
   600,
   700,
   800,
   900,
   1000,
   1100,
   1200,
   1300,
   1400,
   1500,
   2000,
   3000};
   Double_t bulkToZZ_fy1[16] = {
   51600,
   10338,
   2520,
   674,
   226,
   90.8,
   41.7,
   20.9,
   11.2,
   6.35,
   3.74,
   2.29,
   1.44,
   0.934,
   0.135,
   0.00583};
   TGraph *graph = new TGraph(16,bulkToZZ_fx1,bulkToZZ_fy1);
   graph->SetName("bulkToZZ");
   //graph->SetTitle("G_{bulk} #rightarrow ZZ, k/M_{Pl} = 0.5");
   graph->SetFillColor(1);
   graph->SetLineColor(2);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0);
      
   graph->Draw("sameCP");


  TLegend *leg = new TLegend(0.32,0.12,0.9,0.45);
  leg->SetHeader(legTitle[key].c_str());
  leg->AddEntry(gr5,"Observed limit","lp");
  leg->AddEntry(gr0,"expected 95% C.L. upper limit","lp");
  leg->AddEntry(gr1,"expected #pm 1#sigma","f");
  leg->AddEntry(gr2,"expected #pm 2#sigma","f");
  leg->AddEntry(graph,"G_{bulk} #rightarrow ZZ, k/M_{Pl} = 0.5","l");
  leg->Draw();
  TLegendEntry *header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
  header->SetTextAlign(22);
  header->SetTextColor(2);
  header->SetTextSize(.04);

  c1->Print(outFile[key].c_str());
}
