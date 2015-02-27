//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  4 12:02:10 2015 by ROOT version 5.34/18
// from TTree EDBRCandidates/EDBR Candidates
// found on file: trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_3iii.root
//////////////////////////////////////////////////////////

#ifndef info_h
#define info_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TMath.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class info {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   TFile *filename;

   TH1D *h_lep1;
   TH1D *h_lep2;
   TH1D *h_eedeltaR;
   TH1D *h_lep1_pass;
   TH1D *h_lep2_pass;
   TH1D *h_eedeltaR_pass;
   TH1D *h_lep1_pass_match;
   TH1D *h_lep2_pass_match;
   TH1D *h_eedeltaR_pass_match;

   TH1D *h_lep1_G;
   TH1D *h_lep2_G;
   TH1D *h_eedeltaR_G;
   TH1D *h_lepZcand_G;
   TH1D *h_lep1_G_pass;
   TH1D *h_lep2_G_pass;
   TH1D *h_eedeltaR_G_pass;
   TH1D *h_lepZcand_G_pass;
   TH1D *h_lep1_G_pass_match;
   TH1D *h_lep2_G_pass_match;
   TH1D *h_eedeltaR_G_pass_match;
   TH1D *h_lepZcand_G_pass_match;

   TGraphAsymmErrors *HLTEff_vs_lep1;
   TGraphAsymmErrors *HLTEff_vs_lep2;
   TGraphAsymmErrors *HLTEff_vs_eedeltaR;
   TGraphAsymmErrors *HLTEff_vs_lep1_G;
   TGraphAsymmErrors *HLTEff_vs_lep2_G;
   TGraphAsymmErrors *HLTEff_vs_eedeltaR_G;
   TGraphAsymmErrors *HLTEff_vs_lepZcand_G;

   TGraphAsymmErrors *HLTEffm_vs_lep1;
   TGraphAsymmErrors *HLTEffm_vs_lep2;
   TGraphAsymmErrors *HLTEffm_vs_eedeltaR;
   TGraphAsymmErrors *HLTEffm_vs_lep1_G;
   TGraphAsymmErrors *HLTEffm_vs_lep2_G;
   TGraphAsymmErrors *HLTEffm_vs_eedeltaR_G;
   TGraphAsymmErrors *HLTEffm_vs_lepZcand_G;

   // Declaration of leaf types
   Int_t           event;
   Int_t           nVtx;
   Int_t           numCands;
   Double_t        ptVlep;
   Double_t        ptVhad;
   Double_t        yVlep;
   Double_t        yVhad;
   Double_t        phiVlep;
   Double_t        phiVhad;
   Double_t        massVlep;
   Double_t        mtVlep;
   Double_t        massVhad;
   Double_t        tau1;
   Double_t        tau2;
   Double_t        tau3;
   Double_t        tau21;
   Int_t           lep;
   Int_t           region;
   Int_t           channel;
   Double_t        candMass;
   Double_t        eeDeltaR;
   Double_t        ptel1;
   Double_t        ptel2;
   Double_t        etaSC1;
   Double_t        etaSC2;
   Double_t        dEtaIn1;
   Double_t        dEtaIn2;
   Double_t        dPhiIn1;
   Double_t        dPhiIn2;
   Double_t        hOverE1;
   Double_t        hOverE2;
   Double_t        full5x5_sigma1;
   Double_t        full5x5_sigma2;
   Double_t        ooEmooP1;
   Double_t        ooEmooP2;
   Double_t        d01;
   Double_t        d02;
   Double_t        dz1;
   Double_t        dz2;
   Double_t        relIso1;
   Double_t        relIso2;
   Int_t           missingHits1;
   Int_t           missingHits2;
   Int_t           passConVeto1;
   Int_t           passConVeto2;
   Int_t           el1passID;
   Int_t           el2passID;
   Double_t        ptlep1;
   Double_t        ptlep2;
   Double_t        ptjet1;
   Double_t        etalep1;
   Double_t        etalep2;
   Double_t        etajet1;
   Double_t        philep1;
   Double_t        philep2;
   Double_t        phijet1;
   Double_t        massjet1;
   Double_t        met;
   Double_t        metPhi;
   Double_t        triggerWeight;
   Double_t        lumiWeight;
   Double_t        pileupWeight;
   Double_t        deltaRleplep;
   Double_t        delPhilepmet;
   Double_t        deltaRlepjet;
   Double_t        delPhijetmet;
   Double_t        etSC1;
   Double_t        etSC2;
   Int_t           all;
   Int_t           off;
   Int_t           trg;
   Int_t           mtch;
   Int_t           mtcht;
   Int_t           countInTriggered;
   Int_t           triggerFired;
   Int_t           triggerFound;
   Int_t           trigObjmatched;
   Int_t           pathIndex;
   Double_t        eeDeltaR_OffSel;
   Double_t        eeDeltaR_OffSel_trig;
   Double_t        eeDeltaR_OffSel_mtrig;
   Double_t        ptAllRecoEl[8];   //[all]
   Double_t        ptOffSelRecoEl[3];   //[off]
   Double_t        ptOffSelRecoEl_trig[3];   //[trg]
   Double_t        ptMatchedEl[2]; //[mtch]
   Double_t        ptAllMatchedEl[2]; //[mtch]

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_numCands;   //!
   TBranch        *b_ptVlep;   //!
   TBranch        *b_ptVhad;   //!
   TBranch        *b_yVlep;   //!
   TBranch        *b_yVhad;   //!
   TBranch        *b_phiVlep;   //!
   TBranch        *b_phiVhad;   //!
   TBranch        *b_massVlep;   //!
   TBranch        *b_mtVlep;   //!
   TBranch        *b_massVhad;   //!
   TBranch        *b_tau1;   //!
   TBranch        *b_tau2;   //!
   TBranch        *b_tau3;   //!
   TBranch        *b_tau21;   //!
   TBranch        *b_lep;   //!
   TBranch        *b_region;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_candMass;   //!
   TBranch        *b_eeDeltaR;   //!
   TBranch        *b_ptel1;   //!
   TBranch        *b_ptel2;   //!
   TBranch        *b_etaSC1;   //!
   TBranch        *b_etaSC2;   //!
   TBranch        *b_dEtaIn1;   //!
   TBranch        *b_dEtaIn2;   //!
   TBranch        *b_dPhiIn1;   //!
   TBranch        *b_dPhiIn2;   //!
   TBranch        *b_hOverE1;   //!
   TBranch        *b_hOverE2;   //!
   TBranch        *b_full5x5_sigma1;   //!
   TBranch        *b_full5x5_sigma2;   //!
   TBranch        *b_ooEmooP1;   //!
   TBranch        *b_ooEmooP2;   //!
   TBranch        *b_d01;   //!
   TBranch        *b_d02;   //!
   TBranch        *b_dz1;   //!
   TBranch        *b_dz2;   //!
   TBranch        *b_relIso1;   //!
   TBranch        *b_relIso2;   //!
   TBranch        *b_missingHits1;   //!
   TBranch        *b_missingHits2;   //!
   TBranch        *b_passConVeto1;   //!
   TBranch        *b_passConVeto2;   //!
   TBranch        *b_el1passID;   //!
   TBranch        *b_el2passID;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_ptlep2;   //!
   TBranch        *b_ptjet1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_etalep2;   //!
   TBranch        *b_etajet1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_philep2;   //!
   TBranch        *b_phijet1;   //!
   TBranch        *b_massjet1;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metPhi;   //!
   TBranch        *b_triggerWeight;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_deltaRleplep;   //!
   TBranch        *b_delPhilepmet;   //!
   TBranch        *b_deltaRlepjet;   //!
   TBranch        *b_delPhijetmet;   //!
   TBranch        *b_etSC1;   //!
   TBranch        *b_etSC2;   //!
   TBranch        *b_all;   //!
   TBranch        *b_off;   //!
   TBranch        *b_trg;   //!
   TBranch        *b_mtch;   //!
   TBranch        *b_mtcht;   //!
   TBranch        *b_countInTriggered;   //!
   TBranch        *b_triggerFired;   //!
   TBranch        *b_triggerFound;   //!
   TBranch        *b_trigObjmatched;   //!
   TBranch        *b_pathIndex;   //!
   TBranch        *b_eeDeltaR_OffSel;   //!
   TBranch        *b_eeDeltaR_OffSel_trig;   //!
   TBranch        *b_eeDeltaR_OffSel_mtrig;   //!
   TBranch        *b_ptAllRecoEl;   //!
   TBranch        *b_ptOffSelRecoEl;   //!
   TBranch        *b_ptOffSelRecoEl_trig;   //!
   TBranch        *b_ptMatchedEl;   //!
   TBranch        *b_ptAllMatchedEl;   //!

   info(TTree *tree=0);
   virtual ~info();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef info_cxx
info::info(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_newHEEPnoIso_2002.root");
     //     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_newHEEPwIso_1802.root");
     //     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("trigEDBR_RSGravToZZ_kMpl01_M-1000_Phys14_newHEEPwIso_1802.root");
     //     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("trigDYJetsToLL_HT-400to600_Phys14_newHEEPwIso_1802.root");
     //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("trigDYJetsToLL_HT-200to400_Phys14_newHEEPwIso_1802.root");
      if (!f || !f->IsOpen()) {
	f = new TFile("trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_newHEEPnoIso_2002.root");
	//	f = new TFile("trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_newHEEPwIso_1802.root");
	//f = new TFile("trigEDBR_RSGravToZZ_kMpl01_M-1000_Phys14_newHEEPwIso_1802.root");
	//	f = new TFile("trigDYJetsToLL_HT-400to600_Phys14_newHEEPwIso_1802.root");
	//f = new TFile("trigDYJetsToLL_HT-200to400_Phys14_newHEEPwIso_1802.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_newHEEPnoIso_2002.root:/treeDumper");
      // TDirectory * dir = (TDirectory*)f->Get("trigEDBR_RSGravToZZ_kMpl01_M-4500_Phys14_newHEEPwIso_1802.root:/treeDumper");
      //      TDirectory * dir = (TDirectory*)f->Get("trigEDBR_RSGravToZZ_kMpl01_M-1000_Phys14_newHEEPwIso_1802.root:/treeDumper");
      //      TDirectory * dir = (TDirectory*)f->Get("trigDYJetsToLL_HT-400to600_Phys14_newHEEPwIso_1802.root:/treeDumper");
      //TDirectory * dir = (TDirectory*)f->Get("trigDYJetsToLL_HT-200to400_Phys14_newHEEPwIso_1802.root:/treeDumper");
      dir->GetObject("EDBRCandidates",tree);

   }
   Init(tree);
}

info::~info()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
   /*   filename->cd();

   h_lep1->Write();
   h_lep2->Write();
   h_eedeltaR->Write();
   h_lep1_pass->Write();
   h_lep2_pass->Write();
   h_eedeltaR_pass->Write();

   h_lep1_G->Write();
   h_lep2_G->Write();
   h_eedeltaR_G->Write();
   h_lepZcand_G->Write();
   h_lep1_G_pass->Write();
   h_lep2_G_pass->Write();
   h_eedeltaR_G_pass->Write();
   h_lepZcand_G_pass->Write();

   HLTEff_vs_lep1->Write();
   HLTEff_vs_lep2->Write();
   HLTEff_vs_eedeltaR->Write();
   HLTEff_vs_lep1_G->Write();
   HLTEff_vs_lep2_G->Write();
   HLTEff_vs_eedeltaR_G->Write();
   HLTEff_vs_lepZcand_G->Write();
   fileName->Close();*/
}

Int_t info::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t info::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void info::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("numCands", &numCands, &b_numCands);
   fChain->SetBranchAddress("ptVlep", &ptVlep, &b_ptVlep);
   fChain->SetBranchAddress("ptVhad", &ptVhad, &b_ptVhad);
   fChain->SetBranchAddress("yVlep", &yVlep, &b_yVlep);
   fChain->SetBranchAddress("yVhad", &yVhad, &b_yVhad);
   fChain->SetBranchAddress("phiVlep", &phiVlep, &b_phiVlep);
   fChain->SetBranchAddress("phiVhad", &phiVhad, &b_phiVhad);
   fChain->SetBranchAddress("massVlep", &massVlep, &b_massVlep);
   fChain->SetBranchAddress("mtVlep", &mtVlep, &b_mtVlep);
   fChain->SetBranchAddress("massVhad", &massVhad, &b_massVhad);
   fChain->SetBranchAddress("tau1", &tau1, &b_tau1);
   fChain->SetBranchAddress("tau2", &tau2, &b_tau2);
   fChain->SetBranchAddress("tau3", &tau3, &b_tau3);
   fChain->SetBranchAddress("tau21", &tau21, &b_tau21);
   fChain->SetBranchAddress("lep", &lep, &b_lep);
   fChain->SetBranchAddress("region", &region, &b_region);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("candMass", &candMass, &b_candMass);
   fChain->SetBranchAddress("eeDeltaR", &eeDeltaR, &b_eeDeltaR);
   fChain->SetBranchAddress("ptel1", &ptel1, &b_ptel1);
   fChain->SetBranchAddress("ptel2", &ptel2, &b_ptel2);
   fChain->SetBranchAddress("etaSC1", &etaSC1, &b_etaSC1);
   fChain->SetBranchAddress("etaSC2", &etaSC2, &b_etaSC2);
   fChain->SetBranchAddress("dEtaIn1", &dEtaIn1, &b_dEtaIn1);
   fChain->SetBranchAddress("dEtaIn2", &dEtaIn2, &b_dEtaIn2);
   fChain->SetBranchAddress("dPhiIn1", &dPhiIn1, &b_dPhiIn1);
   fChain->SetBranchAddress("dPhiIn2", &dPhiIn2, &b_dPhiIn2);
   fChain->SetBranchAddress("hOverE1", &hOverE1, &b_hOverE1);
   fChain->SetBranchAddress("hOverE2", &hOverE2, &b_hOverE2);
   fChain->SetBranchAddress("full5x5_sigma1", &full5x5_sigma1, &b_full5x5_sigma1);
   fChain->SetBranchAddress("full5x5_sigma2", &full5x5_sigma2, &b_full5x5_sigma2);
   fChain->SetBranchAddress("ooEmooP1", &ooEmooP1, &b_ooEmooP1);
   fChain->SetBranchAddress("ooEmooP2", &ooEmooP2, &b_ooEmooP2);
   fChain->SetBranchAddress("d01", &d01, &b_d01);
   fChain->SetBranchAddress("d02", &d02, &b_d02);
   fChain->SetBranchAddress("dz1", &dz1, &b_dz1);
   fChain->SetBranchAddress("dz2", &dz2, &b_dz2);
   fChain->SetBranchAddress("relIso1", &relIso1, &b_relIso1);
   fChain->SetBranchAddress("relIso2", &relIso2, &b_relIso2);
   fChain->SetBranchAddress("missingHits1", &missingHits1, &b_missingHits1);
   fChain->SetBranchAddress("missingHits2", &missingHits2, &b_missingHits2);
   fChain->SetBranchAddress("passConVeto1", &passConVeto1, &b_passConVeto1);
   fChain->SetBranchAddress("passConVeto2", &passConVeto2, &b_passConVeto2);
   fChain->SetBranchAddress("el1passID", &el1passID, &b_el1passID);
   fChain->SetBranchAddress("el2passID", &el2passID, &b_el2passID);
   fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
   fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
   fChain->SetBranchAddress("ptjet1", &ptjet1, &b_ptjet1);
   fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
   fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
   fChain->SetBranchAddress("etajet1", &etajet1, &b_etajet1);
   fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
   fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
   fChain->SetBranchAddress("phijet1", &phijet1, &b_phijet1);
   fChain->SetBranchAddress("massjet1", &massjet1, &b_massjet1);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("triggerWeight", &triggerWeight, &b_triggerWeight);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("deltaRleplep", &deltaRleplep, &b_deltaRleplep);
   fChain->SetBranchAddress("delPhilepmet", &delPhilepmet, &b_delPhilepmet);
   fChain->SetBranchAddress("deltaRlepjet", &deltaRlepjet, &b_deltaRlepjet);
   fChain->SetBranchAddress("delPhijetmet", &delPhijetmet, &b_delPhijetmet);
   fChain->SetBranchAddress("etSC1", &etSC1, &b_etSC1);
   fChain->SetBranchAddress("etSC2", &etSC2, &b_etSC2);
   fChain->SetBranchAddress("all", &all, &b_all);
   fChain->SetBranchAddress("off", &off, &b_off);
   fChain->SetBranchAddress("trg", &trg, &b_trg);
   fChain->SetBranchAddress("mtch", &mtch, &b_mtch);
   fChain->SetBranchAddress("mtcht", &mtcht, &b_mtcht);
   fChain->SetBranchAddress("countInTriggered", &countInTriggered, &b_countInTriggered);
   fChain->SetBranchAddress("triggerFired", &triggerFired, &b_triggerFired);
   fChain->SetBranchAddress("triggerFound", &triggerFound, &b_triggerFound);
   fChain->SetBranchAddress("trigObjmatched", &trigObjmatched, &b_trigObjmatched);
   fChain->SetBranchAddress("pathIndex", &pathIndex, &b_pathIndex);
   fChain->SetBranchAddress("eeDeltaR_OffSel", &eeDeltaR_OffSel, &b_eeDeltaR_OffSel);
   fChain->SetBranchAddress("eeDeltaR_OffSel_trig", &eeDeltaR_OffSel_trig, &b_eeDeltaR_OffSel_trig);
   fChain->SetBranchAddress("eeDeltaR_OffSel_mtrig", &eeDeltaR_OffSel_mtrig, &b_eeDeltaR_OffSel_mtrig);
   fChain->SetBranchAddress("ptAllRecoEl", ptAllRecoEl, &b_ptAllRecoEl);
   fChain->SetBranchAddress("ptOffSelRecoEl", ptOffSelRecoEl, &b_ptOffSelRecoEl);
   fChain->SetBranchAddress("ptOffSelRecoEl_trig", ptOffSelRecoEl_trig, &b_ptOffSelRecoEl_trig);
   fChain->SetBranchAddress("ptMatchedEl", ptMatchedEl, &b_ptMatchedEl);
   fChain->SetBranchAddress("ptAllMatchedEl", ptAllMatchedEl, &b_ptAllMatchedEl);
   Notify();
}

Bool_t info::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void info::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t info::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef info_cxx
