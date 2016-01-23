#include <Riostream.h>
#include <map>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TError.h"
#include "TChain.h"
#include "TFile.h"
#include "TCollection.h"
#include "TKey.h"
#include "EDBRHistoMaker.h"
#include "EDBRHistoPlotter.h"

#include "CMSTDRStyle.h"

void loopPlot(){

  gErrorIgnoreLevel=kFatal;//suppresses all info messages
  setTDRStyle();//TDR style
  
  //#####################EDIT THE OPTIONS##############################
  /// Boolean flags to steer the histogram making
  bool wantElectrons = false; // Will make histograms for electrons
  bool wantMuons     = true; // Will make histograms for muons
  bool wantSideband  = true; // Will make histograms for sideband region
  bool wantSignal    = false; // Will make histograms for signal region
  bool wantFullRange = false; // Will not check signal or sideband, ie, pick all jet mass range
  int  wantNXJets    = 1; // Will make histograms for 1 or 2 jet topology
  int  isZZchannel   = 1; //plot label for zz (1) or ww (0)
  int  flavour = 0; 
  std::string outputDir;
  if(wantElectrons) {flavour=11;   outputDir = "../controlPlots/plots_ELP_SidebandRegion";}
  if(wantMuons)     {flavour=13;   outputDir = "../controlPlots/plots_MLP_SidebandRegion";}
  if(wantElectrons and wantMuons)  outputDir = "../controlPlots/plots_ALP_SidebandRegion";
  
  /// Luminosity value in fb^-1
  /// Scale histograms (line 403 EDBRHistoPloter.h) 
  /// Use lumiValue = 1. if actualWeights (lines 562-585 EDBRHistoMaker.h) were consistently defined in the EDBRTreeMaker 
  double lumiValue = 1.; 
  /// Should we scale the histograms to data?
  bool scaleToData = false;
  // Should we scale only wjets to make total MC = DATA?
  bool scaleOnlyWJets = false;
  /// Should we plot the Data/Bkg and Data-Bkg/Error ratios?
  bool makeRatio = true; 
  /// Should we REDO histograms?
  bool redoHistograms = true;
  /// Should we put the signal MC stacked on top of the background (or just plot the signal alone)?
  bool isSignalStackOnBkg = false;
  /// Should we do pileup reweighting?
  bool pileupReweight = true;

  /// Path to wherever the files with the trees are. 
  std::string pathToTrees="../trees/";

  /// Setup names of data files for trees.

  const int nDATA=4;//set to zero if you don't want to plot
  //std::string dataLabels[nDATA]={ };
  std::string dataLabels[nDATA]={"SingleMuon1",      // SingleMuon/Run2015C_25ns-05Oct2015
                                 "SingleMuon2",      // SingleMuon/Run2015D-05Oct2015
                                 "SingleElectron1",  // SingleElectron/Run2015C_25ns-05Oct2015
                                 "SingleElectron2"   // SingleElectron/Run2015D-04Dec2015
                                };

  std::vector<std::string> fData;
  
  for(int ii=0;ii<nDATA;ii++){
    fData.push_back(pathToTrees+"treeEDBR_"+dataLabels[ii]+".root");
  }

  /// Setup names of MC files for trees.
  const int nMC=2;//set to zero if you don't want to plot
  std::string mcLabels[nMC]={ 
                             "Diboson",
                             "DYJets",
			    };

  std::vector<std::string> DBsamples; 
  std::vector<std::string> DYsamples; 

  if(wantElectrons){
     DBsamples.push_back(pathToTrees+"treeEDBR_WZ_el.root");
     DBsamples.push_back(pathToTrees+"treeEDBR_WW_el.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT100to200_el.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT200to400_el.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT400to600_el.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT600toInf_el.root");
  }
  if(wantMuons){
     DBsamples.push_back(pathToTrees+"treeEDBR_WZ_mu.root");
     DBsamples.push_back(pathToTrees+"treeEDBR_WW_mu.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT100to200_mu.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT200to400_mu.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT400to600_mu.root");
     DYsamples.push_back(pathToTrees+"treeEDBR_DYJetsToLL_HT600toInf_mu.root");
  }
  
  std::map<int, std::vector<std::string> > fMC; 
  fMC[0] = DBsamples;
  fMC[1] = DYsamples;

  double kFactorsMC_array[nMC] = {1, 1};
  std::vector<double> kFactorsMC;
  //std::cout << "The contents of kFactorsMC are:" << std::endl;
  for (int index=0; index<nMC; index++)
    {
      //std::cout << kFactorsMC_array[index] << std::endl;
      kFactorsMC.push_back( kFactorsMC_array[index] );	
    }

  /// Setup names of MC signal files for trees.
  const int nMCSig=0;//set to zero if you don't want to plot
  //std::string mcLabelsSig[nMCSig]={"BulkGrav_-M_2000"};
  std::string mcLabelsSig[nMCSig]={};
  //double kFactorsSig_array[nMCSig] = {0.5e7};
  double kFactorsSig_array[nMCSig] = {};

  std::vector<double> kFactorsMCSig;
  for (int index=0; index<nMCSig; index++)
    {
      kFactorsMCSig.push_back( kFactorsSig_array[index] );	
    }
  
  std::vector<std::string> fMCSig;
  for(int ii=0;ii<nMCSig;ii++){
    fMCSig.push_back(pathToTrees+"treeEDBR_"+mcLabelsSig[ii]+".root");
  }

  /// Setup names of files for histograms (data and MC)
  std::vector<std::string> fHistosData;
  std::vector<std::string> fHistosMC;
  std::vector<std::string> fHistosMCSig;
 
  char buffer[256];
  printf("All strings set\n");


  /// ----------------------------------------------------------------
  /// This first part is the loop over trees to create histogram files 
  /// ----------------------------------------------------------------

  /// The EDBRHistoMaker, for reference
  ///
  ///EDBRHistoMaker::EDBRHistoMaker(TTree* tree, 
  ///		       bool wantElectrons,
  ///		       bool wantMuons,
  ///		       bool wantSideband,
  ///		       bool wantSignal,
  ///		       int  wantNXJets,
  ///                  bool isZZchannel,
  ///                  bool pileupReweight )

  printf("\nStart making histograms\n\n");

  //loop over data files and make histograms individually for each of them
  for(int i=0;i<nDATA;i++){

    std::cout<<"\n-------\nRunning over "<<dataLabels[i].c_str()<<std::endl;
    std::cout<<"The file is " <<fData.at(i)<<std::endl;
    sprintf(buffer,"histos_%s.root",dataLabels[i].c_str());
    fHistosData.push_back(buffer);
    
    if(redoHistograms) {
      TFile *fileData = TFile::Open(fData.at(i).c_str());
      TTree *treeData = (TTree*)fileData->Get("treeDumper/EDBRCandidates");
      EDBRHistoMaker* maker = new EDBRHistoMaker(treeData, 
						 wantElectrons,
						 wantMuons,
						 wantSideband,
						 wantSignal,
						 wantFullRange,
						 wantNXJets,
						 isZZchannel,
                                                 pileupReweight);
      maker->setUnitaryWeights(true);
      maker->Loop(buffer);
      //delete maker; // This class is badly written and deleting it isn't safe!
      fileData->Close();
    }
    
  }//end loop on data files

  printf("Loop over data done\n");
 
  //loop over MC files and make histograms individually for each of them
  for(int i=0;i<nMC;i++){
    std::cout<<"\n-------\nRunning over "<<mcLabels[i].c_str()<<std::endl;
    sprintf(buffer,"histos_%s.root",mcLabels[i].c_str());
    fHistosMC.push_back(buffer);
    if(redoHistograms){
      TChain treeMC("treeDumper/EDBRCandidates");
      while( !fMC[i].empty() ){
         treeMC.Add(fMC[i].back().c_str());
         fMC[i].pop_back();
      }
      EDBRHistoMaker* maker = new EDBRHistoMaker(&treeMC, 
						 wantElectrons, 
						 wantMuons, 
						 wantSideband, 
						 wantSignal, 
						 wantFullRange,
						 wantNXJets,
						 isZZchannel,
                                                 pileupReweight);
      maker->setUnitaryWeights(false);
      maker->Loop(buffer);
      //maker->saveAllHistos(buffer);
      //delete maker; // This class is badly written and deleting it isn't safe!
    }
    
  }//end loop on MC files

  printf("Loop over MC done\n");

  //loop over MC signal files and make histograms individually for each of them
  for(int i=0;i<nMCSig;i++){
    std::cout<<"\n-------\nRunning over "<<mcLabelsSig[i].c_str()<<std::endl;
    std::cout<<"The file is " <<fMCSig.at(i)<<std::endl;    
    sprintf(buffer,"histos_%s.root",mcLabelsSig[i].c_str());
    fHistosMCSig.push_back(buffer);

    if(redoHistograms){
      TFile *fileMCSig = TFile::Open(fMCSig.at(i).c_str());
      TTree *treeMCSig = (TTree*)fileMCSig->Get("treeDumper/EDBRCandidates");
      EDBRHistoMaker* maker = new EDBRHistoMaker(treeMCSig, 
						 wantElectrons, 
						 wantMuons, 
						 wantSideband, 
						 wantSignal, 
						 wantFullRange,
						 wantNXJets,
						 isZZchannel);
      maker->setUnitaryWeights(false);
      maker->Loop(buffer);
      //delete maker; // This class is badly written and deleting it isn't safe!
      fileMCSig->Close();
    }
    
  }//end loop on MC files

  printf("Loop over MC signal done\n");
  
  /// ------------------------------------------------------------------
  /// This second part is the loop over histograms to create stack plots
  /// ------------------------------------------------------------------  

  //  EDBRHistoMaker::EDBRHistoMaker(TTree* tree,
  //			 bool wantElectrons,
  //			 bool wantMuons,
  //			 bool wantSideband,
  //			 bool wantSignal,
  //			 int  wantNXJets,
  //			 bool isZZchannel){
    
  printf("\nStart looping over histograms\n\n");
  //make nice plots
  std::vector<std::string> listOfHistos;
  if(nMC>0){
    // Open one of the histogram files just to get the list of histograms
    // produced, then loop over all the histograms inheriting 
    // from TH1 contained in the file.
    sprintf(buffer,"histos_%s.root",mcLabels[0].c_str());
    std::cout<<"Opening "<<buffer<<std::endl;
    TFile* oneFile = TFile::Open(buffer);
    TIter next(oneFile->GetListOfKeys());
    TKey *key;
    
    while ((key = (TKey*)next())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TH1")) continue;
      TH1 *hTMP = (TH1*)key->ReadObj();
      std::string hName=hTMP->GetName();
      printf("Histogram found: %s\n",hName.c_str());
      //bool isMJJhisto=(hName.find("mJJ")!=std::string::npos);
      //bool isMZZhisto=(hName.find("mZZ")!=std::string::npos);
      //if( !isMJJhisto && !isMZZhisto)continue;//skip all histos except MJJ and MZZ
      listOfHistos.push_back(hName);
    }//end while loop
    oneFile->Close();
  }//end if fmc size >0

  std::cout << "Creating plotter" << std::endl;
  EDBRHistoPlotter *plotter=new EDBRHistoPlotter("./",
						 fHistosData,
						 fHistosMC,
						 fHistosMCSig,
						 lumiValue,
						 wantNXJets,
						 flavour,
						 isZZchannel,
						 scaleToData,
						 scaleOnlyWJets,
						 makeRatio,
						 isSignalStackOnBkg,
						 kFactorsMC,kFactorsMCSig);
  std::cout<<"Set output dir"<<std::endl;
  plotter->setOutDir(outputDir);
  plotter->setDebug(true);

  //colors are assigned in the same order of mcLabels
    // For ZZ
  ////// {DYJetsToLL_HT-100to200,DYJetsToLL_HT-200to400,DYJetsToLL_HT-200to400,DYJetsToLL_HT-600toInf}
  std::vector<int> fColorsMC;
  //fColorsMC.push_back(kRed+3);
  //fColorsMC.push_back(kRed);
  //fColorsMC.push_back(kAzure+1);
  //fColorsMC.push_back(kAzure+2);
  fColorsMC.push_back(kGreen-7);
  fColorsMC.push_back(kRed-7);
  fColorsMC.push_back(kAzure-7);
  
  ////// {"BulkG_WW_lvjj_c1p0_M600_xww","BulkG_WW_lvjj_c1p0_M1000_xww","BulkG_WW_lvjj_c1p0_M1500_xww"};
  std::vector<int> fColorsMCSig;
  //fColorsMCSig.push_back(kMagenta-7);
  fColorsMCSig.push_back(kYellow-5);
  
  plotter->setFillColor(fColorsMC);
  plotter->setLineColor(fColorsMCSig);

  int numOfHistos = listOfHistos.size();
  for(int i = 0; i != numOfHistos; ++i) 
    plotter->makeStackPlots(listOfHistos.at(i));      

  printf("Plotting done\n");
    
  delete plotter;

}//end main
