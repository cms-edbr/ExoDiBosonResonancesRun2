// Ussage: 

// 1) Generate libray PUWeight_cxx.so (root -b; .L PUWeight.cxx+)

// 2) Generate PU profile in data: 

//    pileupCalc.py -i MYJSON.txt --inputLumiJSON INPUTLUMIJSON.txt --calcMode true --minBiasXsec 69000 --maxPileupBin 52 --numPileupBins 52 MyDataPileupHistogram.root

// 3) root -b -q generatePUWeights.C

R__LOAD_LIBRARY(PUWeight_cxx.so)

void generatePUWeights(){
   std::string PUProfileData_ = "MyDataPileupHistogram.root";
   PUWeight  PUWeight_;
   PUWeight::Scenario sc = PUWeight_.toScenario("PUS25ns");
   PUWeight_.initPUWeights(PUProfileData_,sc);

   TH1D* pileupWeights = new TH1D("pileupWeights","",52,0,52);

   for (int i=1; i<=52; i++ ){
       pileupWeights->SetBinContent(i, PUWeight_.getPUWeight(i-1));
   }

   TFile *outFile = new TFile("pileupWeights69mb.root", "RECREATE");
   outFile->cd();
   pileupWeights->Write();
   outFile->Close();
}
