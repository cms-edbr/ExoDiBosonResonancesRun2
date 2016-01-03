// Usage: 

// 1) Generate PU profile in data: 

//    pileupCalc.py -i MYJSON.txt --inputLumiJSON INPUTLUMIJSON.txt --calcMode true --minBiasXsec 69000 --maxPileupBin 50 --numPileupBins 50 MyDataPileupHistogram.root

// 2) root -b -q generatePUWeights.C

void generatePUWeights(){

    // Poisson density function taken from
    // https://github.com/cms-sw/cmssw/blob/CMSSW_7_6_X/SimGeneral/MixingModule/python/mix_2015_25ns_FallMC_matchData_PoissonOOTPU_cfi.py#L26
    double probValue[50] = {
                0.000108643,
                0.000388957,
                0.000332882,
                0.00038397,
                0.000549167,
                0.00105412,
                0.00459007,
                0.0210314,
                0.0573688,
                0.103986,
                0.142369,
                0.157729,
                0.147685,
                0.121027,
                0.08855,
                0.0582866,
                0.0348526,
                0.019457,
                0.0107907,
                0.00654313,
                0.00463195,
                0.00370927,
                0.0031137,
                0.00261141,
                0.00215499,
                0.00174491,
                0.00138268,
                0.00106731,
                0.000798828,
                0.00057785,
                0.00040336,
                0.00027161,
                0.000176535,
                0.00011092,
                6.75502e-05,
                4.00323e-05,
                2.32123e-05,
                1.32585e-05,
                7.51611e-06,
                4.25902e-06,
                2.42513e-06,
                1.39077e-06,
                8.02452e-07,
                4.64159e-07,
                2.67845e-07,
                1.5344e-07,
                8.68966e-08,
                4.84931e-08,
                2.6606e-08,
                1.433e-08
    };

    // Make histogram from the probValues
    TH1D *h1 = new TH1D("h1","",50,0,50);
    h1->Sumw2();
    for(int i=1; i<=50; i++) h1->SetBinContent(i,probValue[i-1]);

    // Read PU profile
    TFile *f = TFile::Open("MyDataPileupHistogram.root");
    TH1D *pileup = (TH1D*)f->Get("pileup");
    TH1D *h2 = (TH1D*)pileup->Clone("pileupWeights");

    // Normalized PU profile
    h2->Scale(1./h2->Integral());

    // Get weights by dividing the normalized PU profile by the probValues
    h2->Divide(h1);

    // Save weights in file
    TFile *outFile = new TFile("pileupWeights69mb.root", "RECREATE");
    outFile->cd();
    h2->Write();
}
