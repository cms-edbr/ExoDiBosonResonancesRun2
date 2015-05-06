#define info_cxx
#include "info.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
void info::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L info.C
//      Root > info t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   //   filename = new TFile("HLTefficiency_DY400-600_newHEEPwIso.root", "RECREATE");
   filename = new TFile("HLTefficiency_RS4500_newHEEPnoIso_2002.root", "RECREATE");

   // h_lep1 = new TH1D("h_lep1", "P_{T} of leading lepton", 50, 0, 500);
   //h_lep2 = new TH1D("h_lep2", "P_{T} of sub-leading lepton", 50, 0, 500);
   //h_eedeltaR = new TH1D("h_eedeltaR", "deltaR between the two electrons", 25,0,5.0);
   h_lep1 = new TH1D("h_lep1", "P_{T} of leading lepton", 50, 0, 2500);
   h_lep2 = new TH1D("h_lep2", "P_{T} of sub-leading lepton", 50, 0, 2500);
   h_eedeltaR = new TH1D("h_eedeltaR", "deltaR between the two electrons", 25,0,0.5);
   //h_lep1_pass = new TH1D("h_lep1_pass", "P_{T} of leading lepton", 50, 0, 500);
   //h_lep2_pass = new TH1D("h_lep2_pass", "P_{T} of sub-leading lepton", 50, 0, 500);
   //h_eedeltaR_pass = new TH1D("h_eedeltaR_pass", "deltaR between the two electrons", 25,0,5.0);
   h_lep1_pass = new TH1D("h_lep1_pass", "P_{T} of leading lepton", 50, 0, 2500);
   h_lep2_pass = new TH1D("h_lep2_pass", "P_{T} of sub-leading lepton", 50, 0, 2500);
   h_eedeltaR_pass = new TH1D("h_eedeltaR_pass", "deltaR between the two electrons", 25,0,0.5);
   //h_lep1_pass_match = new TH1D("h_lep1_pass_match", "P_{T} of leading lepton", 50, 0, 500);
   //h_lep2_pass_match = new TH1D("h_lep2_pass_match", "P_{T} of sub-leading lepton", 50, 0, 500);
   //h_eedeltaR_pass_match = new TH1D("h_eedeltaR_pass_match", "deltaR between the two electrons",25,0,5.0);
   h_lep1_pass_match = new TH1D("h_lep1_pass_match", "P_{T} of leading lepton", 50, 0, 2500);
   h_lep2_pass_match = new TH1D("h_lep2_pass_match", "P_{T} of sub-leading lepton", 50, 0, 2500);
   h_eedeltaR_pass_match = new TH1D("h_eedeltaR_pass_match", "deltaR between the two electrons", 25,0,0.5);


   h_lep1_G = new TH1D("h_lep1_G", "P_{T} of leading lepton", 50, 0, 2500);
   h_lep2_G = new TH1D("h_lep2_G", "P_{T} of sub-leading lepton", 50, 0, 2500);
   h_eedeltaR_G = new TH1D("h_eedeltaR_G", "deltaR between the two electrons", 25,0,0.5);
   h_lepZcand_G = new TH1D("h_lepZcand_G", "P_{T} of leptonic Z boson", 50, 0, 2500);
   h_lep1_G_pass = new TH1D("h_lep1_G_pass", "P_{T} of leading lepton", 50, 0, 2500);
   h_lep2_G_pass = new TH1D("h_lep2_G_pass", "P_{T} of sub-leading lepton", 50, 0, 2500);
   h_eedeltaR_G_pass = new TH1D("h_eedeltaR_G_pass", "deltaR between the two electrons", 25,0,0.5);
   h_lepZcand_G_pass = new TH1D("h_lepZcand_G_pass", "P_{T} of leptonic Z boson", 50, 0, 2500);
   h_lep1_G_pass_match = new TH1D("h_lep1_G_pass_match", "P_{T} of leading lepton", 50, 0, 2500);
   h_lep2_G_pass_match = new TH1D("h_lep2_G_pass_match", "P_{T} of sub-leading lepton", 50, 0, 2500);
   h_eedeltaR_G_pass_match = new TH1D("h_eedeltaR_G_pass_match", "deltaR between the two electrons", 25,0,0.5);
   h_lepZcand_G_pass_match = new TH1D("h_lepZcand_G_pass_match", "P_{T} of leptonic Z boson", 50, 0, 2500);

   HLTEff_vs_lep1 = new TGraphAsymmErrors();
   HLTEff_vs_lep2 = new TGraphAsymmErrors();
   HLTEff_vs_eedeltaR = new TGraphAsymmErrors();
   HLTEff_vs_lep1_G = new TGraphAsymmErrors();
   HLTEff_vs_lep2_G = new TGraphAsymmErrors();
   HLTEff_vs_eedeltaR_G = new TGraphAsymmErrors();
   HLTEff_vs_lepZcand_G = new TGraphAsymmErrors();

   HLTEffm_vs_lep1 = new TGraphAsymmErrors();
   HLTEffm_vs_lep2 = new TGraphAsymmErrors();
   HLTEffm_vs_eedeltaR = new TGraphAsymmErrors();
   HLTEffm_vs_lep1_G = new TGraphAsymmErrors();
   HLTEffm_vs_lep2_G = new TGraphAsymmErrors();
   HLTEffm_vs_eedeltaR_G = new TGraphAsymmErrors();
   HLTEffm_vs_lepZcand_G = new TGraphAsymmErrors();

   TLegend *leg;
   Long64_t nentries = fChain->GetEntriesFast();

   std::cout<<"n = "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) { //   std::cout<<"j = "<<jentry<<std::endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(off > 1) h_lep1->Fill(ptOffSelRecoEl[0]);    
      if(off > 1) h_lep2->Fill(ptOffSelRecoEl[1]);
      if(off > 1) h_eedeltaR->Fill(eeDeltaR_OffSel); 
      if(off > 1 && trg > 1) h_lep1_pass->Fill(ptOffSelRecoEl[0]);
      if(off > 1 && trg > 1) h_lep2_pass->Fill(ptOffSelRecoEl[1]);
      if(off > 1 && trg > 1) h_eedeltaR_pass->Fill(eeDeltaR_OffSel);  
      if(off > 1 && trg > 1 && mtcht == 2) h_lep1_pass_match->Fill(ptOffSelRecoEl[0]);  
      if(off > 1 && trg > 1 && mtcht == 2) h_lep2_pass_match->Fill(ptOffSelRecoEl[1]);  
      if(off > 1 && trg > 1 && mtcht == 2) h_eedeltaR_pass_match->Fill(eeDeltaR_OffSel);

      if(numCands > 0) {
	h_lep1_G->Fill(ptel1);
	h_lep2_G->Fill(ptel2);
	h_eedeltaR_G->Fill(eeDeltaR);
	h_lepZcand_G->Fill(ptVlep);
	
	if(triggerFired){
	  h_lep1_G_pass->Fill(ptel1);
	  h_lep2_G_pass->Fill(ptel2);
	  h_eedeltaR_G_pass->Fill(eeDeltaR);
	  h_lepZcand_G_pass->Fill(ptVlep);

	  if(trigObjmatched){
	    h_lep1_G_pass_match->Fill(ptel1);
	    h_lep2_G_pass_match->Fill(ptel2);
	    h_eedeltaR_G_pass_match->Fill(eeDeltaR);
	    h_lepZcand_G_pass_match->Fill(ptVlep);
	  }
	}
      }

   }

   HLTEff_vs_lep1->Divide(h_lep1_pass,h_lep1);
   HLTEff_vs_lep2->Divide(h_lep2_pass,h_lep2);
   HLTEff_vs_eedeltaR->Divide(h_eedeltaR_pass,h_eedeltaR);	   
   //G candidate       
   HLTEff_vs_lep1_G->Divide(h_lep1_G_pass,h_lep1_G); // ALSO FIX all the eff plots taking into account graviton... all are flat at 1.... :P
   HLTEff_vs_lep2_G->Divide(h_lep2_G_pass,h_lep2_G);
   HLTEff_vs_eedeltaR_G->Divide(h_eedeltaR_G_pass,h_eedeltaR_G);
   HLTEff_vs_lepZcand_G->Divide(h_lepZcand_G_pass,h_lepZcand_G);

   HLTEffm_vs_lep1->Divide(h_lep1_pass_match,h_lep1);
   HLTEffm_vs_lep2->Divide(h_lep2_pass_match,h_lep2);
   HLTEffm_vs_eedeltaR->Divide(h_eedeltaR_pass_match,h_eedeltaR); // FIX THIS	   
   //G candidate       
   HLTEffm_vs_lep1_G->Divide(h_lep1_G_pass_match,h_lep1_G);
   HLTEffm_vs_lep2_G->Divide(h_lep2_G_pass_match,h_lep2_G);
   HLTEffm_vs_eedeltaR_G->Divide(h_eedeltaR_G_pass_match,h_eedeltaR_G);
   HLTEffm_vs_lepZcand_G->Divide(h_lepZcand_G_pass_match,h_lepZcand_G);

   //LABELLING 
   HLTEff_vs_lep1->Draw("AP");
   HLTEff_vs_lep1->SetLineWidth(2);
   HLTEff_vs_lep1->GetXaxis()->SetTitle("P_{T}^{e1}");
   HLTEff_vs_lep1->GetXaxis()->CenterTitle();
   HLTEff_vs_lep1->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_lep1->GetYaxis()->CenterTitle();
   c1->SaveAs("TEff_vs_lep1.pdf");
   HLTEff_vs_lep2->Draw("AP");
   HLTEff_vs_lep2->GetXaxis()->SetTitle("P_{T}^{e2}");
   HLTEff_vs_lep2->GetXaxis()->CenterTitle();
   HLTEff_vs_lep2->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_lep2->GetYaxis()->CenterTitle();
   c1->SaveAs("TEff_vs_lep2.pdf");
   HLTEff_vs_eedeltaR->Draw("AP");
   HLTEff_vs_eedeltaR->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   HLTEff_vs_eedeltaR->GetXaxis()->CenterTitle();
   HLTEff_vs_eedeltaR->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_eedeltaR->GetYaxis()->CenterTitle();
   c1->SaveAs("TEff_vs_eedeltaR.pdf");
   /*   HLTEff_vs_lep1_G->Draw("AP");
   HLTEff_vs_lep1_G->GetXaxis()->SetTitle("P_{T}^{e1}");
   HLTEff_vs_lep1_G->GetXaxis()->CenterTitle();
   HLTEff_vs_lep1_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_lep1_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEff_vs_lep1_G.pdf");
   HLTEff_vs_lep2_G->Draw("AP");
   HLTEff_vs_lep2_G->GetXaxis()->SetTitle("P_{T}^{e2}");
   HLTEff_vs_lep2_G->GetXaxis()->CenterTitle();
   HLTEff_vs_lep2_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_lep2_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEff_vs_lep2_G.pdf");
   HLTEff_vs_eedeltaR_G->Draw("AP");
   HLTEff_vs_eedeltaR_G->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   HLTEff_vs_eedeltaR_G->GetXaxis()->CenterTitle();
   HLTEff_vs_eedeltaR_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_eedeltaR_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEff_vs_eedeltaR_G.pdf");
   HLTEff_vs_lepZcand_G->Draw("AP");
   HLTEff_vs_lepZcand_G->GetXaxis()->SetTitle("P_{T}^{Z leptonic}");
   HLTEff_vs_lepZcand_G->GetXaxis()->CenterTitle();
   HLTEff_vs_lepZcand_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_lepZcand_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEff_vs_lepZcand_G.pdf");*/
   //matched
   HLTEffm_vs_lep1->Draw("AP");
   HLTEffm_vs_lep1->GetXaxis()->SetTitle("P_{T}^{e1}");
   HLTEffm_vs_lep1->GetXaxis()->CenterTitle();
   HLTEffm_vs_lep1->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEffm_vs_lep1->GetYaxis()->CenterTitle();
   c1->SaveAs("TEffm_vs_lep1.pdf");
   HLTEffm_vs_lep2->Draw("AP");
   HLTEffm_vs_lep2->GetXaxis()->SetTitle("P_{T}^{e2}");
   HLTEffm_vs_lep2->GetXaxis()->CenterTitle();
   HLTEffm_vs_lep2->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEffm_vs_lep2->GetYaxis()->CenterTitle();
   c1->SaveAs("TEffm_vs_lep2.pdf");
   HLTEffm_vs_eedeltaR->Draw("AP");
   HLTEffm_vs_eedeltaR->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   HLTEffm_vs_eedeltaR->GetXaxis()->CenterTitle();
   HLTEffm_vs_eedeltaR->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEffm_vs_eedeltaR->GetYaxis()->CenterTitle();
   c1->SaveAs("TEffm_vs_eedeltaR.pdf");
   /*   HLTEffm_vs_lep1_G->Draw("AP");
   HLTEffm_vs_lep1_G->GetXaxis()->SetTitle("P_{T}^{e1}");
   HLTEffm_vs_lep1_G->GetXaxis()->CenterTitle();
   HLTEffm_vs_lep1_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEffm_vs_lep1_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEffm_vs_lep1_G.pdf");
   HLTEffm_vs_lep2_G->Draw("AP");
   HLTEffm_vs_lep2_G->GetXaxis()->SetTitle("P_{T}^{e2}");
   HLTEffm_vs_lep2_G->GetXaxis()->CenterTitle();
   HLTEffm_vs_lep2_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEffm_vs_lep2_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEffm_vs_lep2_G.pdf");
   HLTEffm_vs_eedeltaR_G->Draw("AP");
   HLTEffm_vs_eedeltaR_G->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   HLTEffm_vs_eedeltaR_G->GetXaxis()->CenterTitle();
   HLTEffm_vs_eedeltaR_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEffm_vs_eedeltaR_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEffm_vs_eedeltaR_G.pdf");
   HLTEffm_vs_lepZcand_G->Draw("AP");
   HLTEffm_vs_lepZcand_G->GetXaxis()->SetTitle("P_{T}^{Z leptonic}");
   HLTEffm_vs_lepZcand_G->GetXaxis()->CenterTitle();
   HLTEffm_vs_lepZcand_G->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEffm_vs_lepZcand_G->GetYaxis()->CenterTitle();
   c1->SaveAs("TEffm_vs_lepZcand_G.pdf");*/

   HLTEff_vs_lep1->Draw("AP");
   HLTEff_vs_lep1->SetLineWidth(2);
   HLTEff_vs_lep1->SetLineColor(1);
   HLTEff_vs_lep1->SetMarkerSize(1);
   HLTEff_vs_lep1->SetMarkerStyle(8);
   HLTEff_vs_lep1->SetMarkerColor(1);
   HLTEff_vs_lep1->GetXaxis()->SetTitle("P_{T}^{e1}");
   HLTEff_vs_lep1->GetXaxis()->CenterTitle();
   HLTEff_vs_lep1->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_lep1->GetYaxis()->CenterTitle();
   HLTEffm_vs_lep1->Draw("sameP");
   HLTEffm_vs_lep1->SetLineWidth(2);
   HLTEffm_vs_lep1->SetLineColor(2);
   HLTEffm_vs_lep1->SetMarkerStyle(8);
   HLTEffm_vs_lep1->SetMarkerSize(1);
   HLTEffm_vs_lep1->SetMarkerColor(2);
   leg = new TLegend(0.2,0.2,0.4,0.4);
   leg->AddEntry(HLTEff_vs_lep1,"without matched objects","p");
   leg->AddEntry(HLTEffm_vs_lep1,"with matched objects","p");
   leg->Draw();
   c1->SaveAs("TEff_TEffm_vs_lep1.pdf");

   HLTEff_vs_lep2->Draw("AP");
   HLTEff_vs_lep2->SetLineWidth(2);
   HLTEff_vs_lep2->SetLineColor(1);
   HLTEff_vs_lep2->SetMarkerStyle(8);
   HLTEff_vs_lep2->SetMarkerSize(1);
   HLTEff_vs_lep2->SetMarkerColor(1);
   HLTEff_vs_lep2->GetXaxis()->SetTitle("P_{T}^{e2}");
   HLTEff_vs_lep2->GetXaxis()->CenterTitle();
   HLTEff_vs_lep2->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_lep2->GetYaxis()->CenterTitle();
   HLTEffm_vs_lep2->Draw("sameP");
   HLTEffm_vs_lep2->SetLineWidth(2);
   HLTEffm_vs_lep2->SetLineColor(2);
   HLTEffm_vs_lep2->SetMarkerStyle(8);
   HLTEffm_vs_lep2->SetMarkerSize(1);
   HLTEffm_vs_lep2->SetMarkerColor(2);
   leg = new TLegend(0.2,0.2,0.4,0.4);
   leg->AddEntry(HLTEff_vs_lep2,"without matched objects","p");
   leg->AddEntry(HLTEffm_vs_lep2,"with matched objects","p");
   leg->Draw();
   c1->SaveAs("TEff_TEffm_vs_lep2.pdf");

   HLTEff_vs_eedeltaR->Draw("AP");
   HLTEff_vs_eedeltaR->SetLineWidth(2);
   HLTEff_vs_eedeltaR->SetLineColor(1);
   HLTEff_vs_eedeltaR->SetMarkerStyle(8);
   HLTEff_vs_eedeltaR->SetMarkerSize(1);
   HLTEff_vs_eedeltaR->SetMarkerColor(1);
   HLTEff_vs_eedeltaR->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   HLTEff_vs_eedeltaR->GetXaxis()->CenterTitle();
   HLTEff_vs_eedeltaR->GetYaxis()->SetTitle("Trigger Efficiency");
   HLTEff_vs_eedeltaR->GetYaxis()->CenterTitle();
   HLTEffm_vs_eedeltaR->Draw("sameP");
   HLTEffm_vs_eedeltaR->SetLineWidth(2);
   HLTEffm_vs_eedeltaR->SetLineColor(2);
   HLTEffm_vs_eedeltaR->SetMarkerStyle(8);
   HLTEffm_vs_eedeltaR->SetMarkerSize(1);
   HLTEffm_vs_eedeltaR->SetMarkerColor(2);
   leg = new TLegend(0.59,0.2,0.79,0.4);
   leg->AddEntry(HLTEff_vs_eedeltaR,"without matched objects","p");
   leg->AddEntry(HLTEffm_vs_eedeltaR,"with matched objects","p");
   leg->Draw();
   c1->SaveAs("TEff_TEffm_vs_eedeltaR.pdf");

   h_lep1->Draw();
   h_lep1->GetXaxis()->SetTitle("P_{T}^{e1}");
   h_lep1->GetXaxis()->CenterTitle();
   //h_lep1->SetStats(0);
   c1->SaveAs("h_lep1.pdf");
   h_lep2->Draw();
   h_lep2->GetXaxis()->SetTitle("P_{T}^{e2}");
   h_lep2->GetXaxis()->CenterTitle();
   //h_lep2->SetStats(0);
   c1->SaveAs("h_lep2.pdf");
   h_lep1_pass->Draw();
   h_lep1_pass->GetXaxis()->SetTitle("P_{T}^{e1}");
   h_lep1_pass->GetXaxis()->CenterTitle();
   //h_lep1_pass->SetStats(0);
   c1->SaveAs("h_lep1_pass.pdf");
   h_lep2_pass->Draw();
   h_lep2_pass->GetXaxis()->SetTitle("P_{T}^{e2}");
   h_lep2_pass->GetXaxis()->CenterTitle();
   //h_lep2_pass->SetStats(0);
   c1->SaveAs("h_lep2_pass.pdf");
   h_lep1_pass_match->Draw();
   h_lep1_pass_match->GetXaxis()->SetTitle("P_{T}^{e1}");
   h_lep1_pass_match->GetXaxis()->CenterTitle();
   //h_lep1_pass_match->SetStats(0);
   c1->SaveAs("h_lep1_pass_match.pdf");
   h_lep2_pass_match->Draw();
   h_lep2_pass_match->GetXaxis()->SetTitle("P_{T}^{e2}");
   h_lep2_pass_match->GetXaxis()->CenterTitle();
   //h_lep2_pass_match->SetStats(0);
   c1->SaveAs("h_lep2_pass_match.pdf");
   h_eedeltaR->Draw();
   h_eedeltaR->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   h_eedeltaR->GetXaxis()->CenterTitle();
   //h_eedeltaR->SetStats(0);
   c1->SaveAs("h_eedeltaR.pdf");
   h_eedeltaR_pass->Draw();
   h_eedeltaR_pass->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   h_eedeltaR_pass->GetXaxis()->CenterTitle();
   //h_eedeltaR_pass->SetStats(0);
   c1->SaveAs("h_eedeltaR_pass.pdf");
   h_eedeltaR_pass_match->Draw();
   h_eedeltaR_pass_match->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   h_eedeltaR_pass_match->GetXaxis()->CenterTitle();
   //h_eedeltaR_pass_match->SetStats(0);
   c1->SaveAs("h_eedeltaR_pass_match.pdf");

   h_lep1->Draw();
   gPad->Update();
   TPaveStats *p1 = (TPaveStats*)h_lep1->FindObject("stats");
   p1->SetTextColor(kBlue);
   h_lep1->GetXaxis()->SetTitle("P_{T}^{e1}");
   h_lep1->GetXaxis()->CenterTitle();
   h_lep1_pass->Draw("same");
   h_lep1_pass->SetLineColor(kRed);
   //gPad->Update();
   c1->Update(); //to force the generation of the stats box
   TPaveStats *p2 = (TPaveStats*)h_lep1_pass->FindObject("stats");
   p2->SetY1NDC(0.76);
   p2->SetY2NDC(0.61);
   p2->SetTextColor(kRed);
   c1->Modified();
   h_lep1_pass_match->Draw("same");
   h_lep1_pass_match->SetLineColor(kGreen);
   //gPad->Update();
   c1->Update(); //to force the generation of the stats box
   TPaveStats *p3 = (TPaveStats*)h_lep1_pass_match->FindObject("stats");
   p3->SetY1NDC(0.59);
   p3->SetY2NDC(0.44);
   p3->SetTextColor(kGreen);
   c1->Modified();
   c1->SaveAs("h_lep1_all.pdf");

   h_lep2->Draw();
   gPad->Update();   
   TPaveStats *p1 = (TPaveStats*)h_lep2->FindObject("stats");
   p1->SetTextColor(kBlue);
   h_lep2->GetXaxis()->SetTitle("P_{T}^{e2}");
   h_lep2->GetXaxis()->CenterTitle();
   h_lep2_pass->Draw("same");
   h_lep2_pass->SetLineColor(kRed);
   //gPad->Update();
   c1->Update(); //to force the generation of the stats box
   TPaveStats *p2 = (TPaveStats*)h_lep2_pass->FindObject("stats");
   p2->SetY1NDC(0.76);
   p2->SetY2NDC(0.61);
   p2->SetTextColor(kRed);
   c1->Modified();
   h_lep2_pass_match->Draw("same");
   h_lep2_pass_match->SetLineColor(kGreen);
   //gPad->Update();
   c1->Update(); //to force the generation of the stats box
   TPaveStats *p3 = (TPaveStats*)h_lep2_pass_match->FindObject("stats");
   p3->SetY1NDC(0.59);
   p3->SetY2NDC(0.44);
   p3->SetTextColor(kGreen);
   c1->Modified();
   c1->SaveAs("h_lep2_all.pdf");

   h_eedeltaR->Draw();
   gPad->Update();
   TPaveStats *p1 = (TPaveStats*)h_eedeltaR->FindObject("stats");
   // p1->SetX1NDC(0.10);
   //p1->SetX2NDC(0.35);
   p1->SetTextColor(kBlue);
   h_eedeltaR->GetXaxis()->SetTitle("#DeltaR(e1,e2)");
   h_eedeltaR->GetXaxis()->CenterTitle();
   h_eedeltaR_pass->Draw("same");
   h_eedeltaR_pass->SetLineColor(kRed);
   //gPad->Update();
   c1->Update(); //to force the generation of the stats box
   TPaveStats *p2 = (TPaveStats*)h_eedeltaR_pass->FindObject("stats");
   //p2->SetX1NDC(0.10);
   //p2->SetX2NDC(0.35);
   p2->SetY1NDC(0.76);
   p2->SetY2NDC(0.61);
   p2->SetTextColor(kRed);
   c1->Modified();
   h_eedeltaR_pass_match->Draw("same");
   h_eedeltaR_pass_match->SetLineColor(kGreen);
   //gPad->Update();
   c1->Update(); //to force the generation of the stats box
   TPaveStats *p3 = (TPaveStats*)h_eedeltaR_pass_match->FindObject("stats");
   //p3->SetX1NDC(0.10);
   //p3->SetX2NDC(0.35);
   p3->SetY1NDC(0.59);
   p3->SetY2NDC(0.44);
   p3->SetTextColor(kGreen);
   c1->Modified();
   c1->SaveAs("h_eedeltaR_all.pdf");
   
   filename->cd();
   h_lep1->Write();
   h_lep2->Write();
   h_eedeltaR->Write();
   h_lep1_pass->Write();
   h_lep2_pass->Write();
   h_eedeltaR_pass->Write();
   h_lep1_pass_match->Write();
   h_lep2_pass_match->Write();
   h_eedeltaR_pass_match->Write();

   h_lep1_G->Write();
   h_lep2_G->Write();
   h_eedeltaR_G->Write();
   h_lepZcand_G->Write();
   h_lep1_G_pass->Write();
   h_lep2_G_pass->Write();
   h_eedeltaR_G_pass->Write();
   h_lepZcand_G_pass->Write();
   h_lep1_G_pass_match->Write();
   h_lep2_G_pass_match->Write();
   h_eedeltaR_G_pass_match->Write();
   h_lepZcand_G_pass_match->Write();

   HLTEff_vs_lep1->Write("HLTEff_vs_lep1");
   HLTEff_vs_lep2->Write("HLTEff_vs_lep2");
   HLTEff_vs_eedeltaR->Write("HLTEff_vs_eedeltaR");
   HLTEff_vs_lep1_G->Write("HLTEff_vs_lep1_G");
   HLTEff_vs_lep2_G->Write("HLTEff_vs_lep2_G");
   HLTEff_vs_eedeltaR_G->Write("HLTEff_vs_eedeltaR_G");
   HLTEff_vs_lepZcand_G->Write("HLTEff_vs_lepZcand_G");

   HLTEffm_vs_lep1->Write("HLTEffm_vs_lep1");
   HLTEffm_vs_lep2->Write("HLTEffm_vs_lep2");
   HLTEffm_vs_eedeltaR->Write("HLTEffm_vs_eedeltaR");
   HLTEffm_vs_lep1_G->Write("HLTEffm_vs_lep1_G");
   HLTEffm_vs_lep2_G->Write("HLTEffm_vs_lep2_G");
   HLTEffm_vs_eedeltaR_G->Write("HLTEffm_vs_eedeltaR_G");
   HLTEffm_vs_lepZcand_G->Write("HLTEffm_vs_lepZcand_G");
   //   fileName->Close();                             
}
