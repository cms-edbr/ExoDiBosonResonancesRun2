R__LOAD_LIBRARY(PDFs/HWWLVJRooPdfs_cxx.so)

void makeDataCards(std::string key, Int_t mass){

  using namespace RooFit;
  TFile *f = TFile::Open( Form("workSpaces/CMS_ZZ_%s_13TeV.root", key.c_str()));
  RooWorkspace* ZZ_13TeV = (RooWorkspace*) f->Get("ZZ_13TeV");

  TFile *sig  = TFile::Open(Form("workSpaces/BulkG_%s_13TeV.root",  key.c_str()));
  RooWorkspace* BulkG = (RooWorkspace*) sig->Get("BulkG");
  RooAbsPdf  *ZZ_sig = BulkG->pdf(Form("BulkG_%d",mass));

  // selection efficiency
  Double_t sel_eff = BulkG->var(Form("eff_%d",mass))->getVal();
  Double_t sig_xs_fb = 1.;           // signal cross section in fb
  Double_t target_lumi_fbInv = 2.63; // target luminosity in fb^-1
  // Signal yield  
  Double_t sigYield = target_lumi_fbInv * sel_eff * sig_xs_fb;

  ZZ_13TeV->import(*ZZ_sig);
  ZZ_13TeV->writeToFile(Form("workSpaces/CMS_ZZ_%d_%s_13TeV.root",mass,key.c_str()));

  // create datacard
  const char *outFile = Form("dataCards/CMS_ZZ_%d_%s_13TeV.txt",mass,key.c_str());
  std::ofstream ofs;
  ofs.open(outFile, std::ofstream::out);

  std::string lepton_scale;
  if( key[0]=='E' ) lepton_scale = "1.005";
  if( key[0]=='M' ) lepton_scale = "1.03";

  ofs << Form("imax 1\n");
  ofs << Form("jmax *\n");
  ofs << Form("kmax *\n");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("shapes            %-10s         %-5s    workSpaces/CMS_ZZ_%d_%s_13TeV.root    %s\n", "*",        key.c_str(), mass, key.c_str(), "ZZ_13TeV:$PROCESS");
  ofs << Form("shapes            %-10s         %-5s    workSpaces/CMS_ZZ_%d_%s_13TeV.root    %s\n", "data_obs", key.c_str(), mass, key.c_str(), "ZZ_13TeV:data_obs");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("bin               %s\n", key.c_str());
  ofs << Form("observation       %s\n",      "-1.0");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("bin               %-10s         %-10s         %s\n",       key.c_str(),     key.c_str(),      key.c_str() );
  ofs << Form("process           %-10s         %-10s         %s\n", ZZ_sig->GetName(),        "DY_pdf",        "Sub_pdf" );
  ofs << Form("process           %-10s         %-10s         %s\n",               "0",             "1",              "2" );
  ofs << Form("rate              %-10f         %-10s         %s\n",          sigYield,             "1",              "1" );
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("DY_pdf_norm                    lnU         %-10s    %.2f       %-5s\n", "1.",        ZZ_13TeV->var( "DY_error")->getVal(), "1." );
  ofs << Form("lumi_13TeV                     lnN         %-10s    %-5s      %s\n", "1.027",  "1.", "1." );
  ofs << Form("CMS_eff_vtag_tau21_sf_13TeV    lnN         %-10s    %-5s      %s\n", "1.1"  ,  "1.", "1." );
  ofs << Form("CMS_scale_j_13TeV              lnN         %-10s    %-5s      %s\n", "1.01" ,  "1.", "1." );
  ofs << Form("CMS_scale_%c_13TeV              lnN         %-10s    %-5s      %s\n", key[0], lepton_scale.c_str(),  "1.", "1." );
  ofs << Form("pdf_eig0                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig1                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig2                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig3                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig4                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig5                       param       %-10s    %s\n",    "0.",    "1." );

  ofs.close();
  
}
