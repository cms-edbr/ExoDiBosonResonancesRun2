// https://root.cern.ch/root/html/TTreePlayer.html#TTreePlayer:Scan
//
// Usage: root -b -q 'scanTree.C(1600, 11)'

void scanTree(int mass, int channel){

   std::map<int, std::string> sufix;
   sufix[11] = "elChannel";
   sufix[13] = "muChannel";

   TFile *f0 = new TFile( Form("../treeEDBR_BulkGravToZZToZlepZhad_M-%d_%s.root", mass, sufix[channel].c_str()) );
   TTree *t0;
   f0->GetObject("trigReport/genTree", t0);
   t0->SetScanField(0); 
   ((TTreePlayer*)(t0->GetPlayer()))->SetScanRedirect(true); 
   ((TTreePlayer*)(t0->GetPlayer()))->SetScanFileName( Form("list_BulkGrav_M-%d_%s.txt", mass, sufix[channel].c_str()) ); 
   t0->Scan("run:lumisec:event", "index>19");
}

