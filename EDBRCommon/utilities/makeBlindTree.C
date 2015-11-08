// When running over Data, the output of the TreeMaker may be unblinded.
// This macro reduces the original n-tuple, 
// keeping only events in the sideband (region==0 or region==3) 

// Additional filters may be applied, for intance to select runs < 259626

// Usage: root -b -q makeBlindTree.C

void makeBlindTree() {
  TFile *oldfile = new TFile("muTrees/nov7/treeEDBR_SingleMuon.root");
  TTree *oldtree = (TTree*)oldfile->Get("treeDumper/EDBRCandidates");
  Long64_t nentries = oldtree->GetEntries();
  Int_t run, region;
  oldtree->SetBranchAddress("run",   &run   );
  oldtree->SetBranchAddress("region",&region);

  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile("treeEDBR_SingleMuon_Blind.root","recreate");
  newfile->mkdir("treeDumper");
  newfile->cd("treeDumper");
  TTree *newtree = oldtree->CloneTree(0);

  for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if ( run<259626 && (region==0 or region==3) ) newtree->Fill();
  } 
  newtree->Print();
  newtree->AutoSave();
  delete oldfile;
  delete newfile;
}
