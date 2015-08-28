// Usage: root -l effvsdR.C

void effvsdR(){

   const char* title = ";gen #Delta R;Efficiency";

   TFile *f = new TFile("tree_BulkGravToZZToZlepZhad.root"); 

   TTree *t;
   f->GetObject("ana/t", t);
   TH1F *pass0 = new TH1F("pass0", title,20,0.,0.4);
   TH1F *pass1 = new TH1F("pass1", title,20,0.,0.4);
   TH1F *pass2 = new TH1F("pass2", title,20,0.,0.4);
   TH1F *total = new TH1F("total", title,20,0.,0.4);

   TCut A =  "medium1==1 && medium2==1";

   TCut B =  "highPt1==1 && highPt2==1";

   TCut C = "(highPt1==1 && tracker2==1) ||\
             (highPt2==1 && tracker1==1)";

   t->Project("pass0", "dRGenGen", A );
   t->Project("pass1", "dRGenGen", B );
   t->Project("pass2", "dRGenGen", C );
   t->Project("total", "dRGenGen"    );

   TEfficiency *eff0 = new TEfficiency(*pass0,*total);
   TEfficiency *eff1 = new TEfficiency(*pass1,*total);
   TEfficiency *eff2 = new TEfficiency(*pass2,*total);

   eff0->SetLineColor(2); eff0->SetMarkerSize(0.8); eff0->SetMarkerStyle(20); eff0->SetMarkerColor(2);
   eff1->SetLineColor(4); eff1->SetMarkerSize(0.8); eff1->SetMarkerStyle(20); eff1->SetMarkerColor(4);
   eff2->SetLineColor(6); eff2->SetMarkerSize(0.8); eff2->SetMarkerStyle(20); eff2->SetMarkerColor(6);

   TCanvas *c1 = new TCanvas("c1","c1",900,900);
   c1->cd();
   gPad->SetGridy();
   gPad->SetGridx();

   eff0->Draw("aZ"); 
   eff1->Draw("Zsame"); 
   eff2->Draw("Zsame"); 
   gPad->Update();
   eff0->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.,1.06);
   eff0->GetPaintedGraph()->GetXaxis()->SetRangeUser(0.063,0.36);
   eff0->GetPaintedGraph()->GetYaxis()->CenterTitle();
   eff0->GetPaintedGraph()->GetYaxis()->SetTitleSize(0.06);
   eff0->GetPaintedGraph()->GetXaxis()->SetTitleSize(0.06);
   eff0->GetPaintedGraph()->GetYaxis()->SetTitleOffset(0.72);
   eff0->GetPaintedGraph()->GetXaxis()->SetTitleOffset(0.72);

   TLegend *leg = new TLegend(0.35,0.32,0.8,0.58);
   leg->SetLineColor(1);
   leg->SetTextSize(0.035);
   leg->AddEntry(eff0,"Medium #plus Medium",  "p");
   leg->AddEntry(eff1,"High-pt #plus High-pt", "p");
   leg->AddEntry(eff2,"High-pt #plus custom tracker", "p");
   leg->Draw();

   TPaveText *pave = new TPaveText(0.05,0.93,0.5,0.98,"NDCNB");
   pave->SetFillColor(0); pave->SetTextFont(42);
   pave->AddText("#bf{CMS} Preliminary #sqrt{s} = 13 TeV");
   pave->Draw();
}
