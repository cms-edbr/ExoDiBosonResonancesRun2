// Usage: root -b -q 'scanTree.C(mass, channel, module position in TrigReport)'

// Find below a TrigReport for the muon channel (electron channel does not include the ZdaughterIso module)

// TrigReport ---------- Modules in Path: analysis ------------
// TrigReport  Trig Bit#    Visited     Passed     Failed      Error Name
// TrigReport     1    0      50000      16268      33732          0 leptonicDecay
// TrigReport     1    1      16268      15910        358          0 hltFilter
// TrigReport     1    2      15910      15910          0          0 hltMatchingElectrons
// TrigReport     1    3      15910      15910          0          0 hltMatchingMuons
// TrigReport     1    4      15910      15910          0          0 goodOfflinePrimaryVertex
// TrigReport     1    5      15910      15910          0          0 egmGsfElectronIDs
// TrigReport     1    6      15910      15910          0          0 electronsMiniIsolationValueMap
// TrigReport     1    7      15910      15910          0          0 muonsMiniIsolationValueMap
// TrigReport     1    8      15910      15910          0          0 goodLeptons
// TrigReport     1    9      15910      15910          0          0 kinElectrons
// TrigReport     1   10      15910      15910          0          0 idElectrons
// TrigReport     1   11      15910      15910          0          0 kinMuons
// TrigReport     1   12      15910      15899         11          0 idMuons
// TrigReport     1   13      15899      15899          0          0 Ztoee
// TrigReport     1   14      15899      15899          0          0 Ztomumu
// TrigReport     1   15      15899      15899          0          0 leptonicV
// TrigReport     1   16      15899      15176        723          0 leptonicVFilter
// TrigReport     1   17      15176      15156         20          0 ZdaughterCharge
// TrigReport     1   18      15156      14689        467          0 ZdaughterIso
// TrigReport     1   19      14689      14028        661          0 leptonicVSelector
// TrigReport     1   20      14028      14028          0          0 bestLeptonicV
// TrigReport     1   21      14028      13843        185          0 hadronicDecay
// TrigReport     1   22      13843      13843          0          0 patJetCorrFactorsReapplyJEC
// TrigReport     1   23      13843      13843          0          0 patJetsReapplyJEC
// TrigReport     1   24      13843      13836          7          0 goodJets
// TrigReport     1   25      13836      13836          0          0 bestLeptonicVdaughters
// TrigReport     1   26      13836      13836          0          0 cleanPatJets
// TrigReport     1   27      13836      13800         36          0 countCleanJets
// TrigReport     1   28      13800      13800          0          0 corrJetsProducer
// TrigReport     1   29      13800      13549        251          0 nsubjettiness
// TrigReport     1   30      13549      13040        509          0 hadronicV
// TrigReport     1   31      13040      13040          0          0 bestHadronicV
// TrigReport     1   32      13040      13040          0          0 graviton
// TrigReport     1   33      13040      13012         28          0 gravitonFilter
// TrigReport     1   34      13012      13012          0          0 treeDumper

void scanTree(int mass, int channel, int bit){

   std::map<int, std::string> sufix;
   sufix[11] = "el";
   sufix[13] = "mu";

   TFile *f0 = new TFile( Form("../treesSync/treeEDBR_BulkGravToZZToZlepZhad_M-%d_%s.root", mass, sufix[channel].c_str()) );
   TTree *t0;
   f0->GetObject("trigReport/genTree", t0);
   t0->SetScanField(0); 
   ((TTreePlayer*)(t0->GetPlayer()))->SetScanRedirect(true); 
   ((TTreePlayer*)(t0->GetPlayer()))->SetScanFileName( Form("ListsAfterLeptonicSelection/list_BulkGrav_M-%d_%s.txt", mass, sufix[channel].c_str()) ); 
   t0->Scan("run:lumisec:event", Form("index>%d",bit));
}
