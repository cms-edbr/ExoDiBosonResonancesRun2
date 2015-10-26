#include "PUWeight.h"

#include "TFile.h"

#include <iostream>

//==============================================================================================
// Get MC pile-up scenario from string representation
PUWeight::Scenario PUWeight::toScenario(const std::string& str) {
  PUWeight::Scenario sc = Winter15_25ns;
  if( str == "PUS25ns" ) sc = Winter15_25ns;
  else {
    std::cerr << "\n\nERROR unknown scenario '" << str << "'" << std::endl;
    throw std::exception();
  }

  return sc;
}

//==============================================================================================
// MC pile-up scenario to string representation
std::string PUWeight::toString(const PUWeight::Scenario sc) {
  std::string str;
  if( sc == Winter15_25ns ) str = "PUS25ns";
  else {
    std::cerr << "\n\nERROR unknown scenario '" << sc << "'" << std::endl;
    throw std::exception();
  }

  return str;
}

//==============================================================================================
// Constructor. Initializes default behaviour to return PU weight of 1
PUWeight::PUWeight()
  : isInit_(false), nPUMax_(0) {}

//==============================================================================================
// Initialise weights for a given MC pile-up scenario. Can only be
// called once.
void PUWeight::initPUWeights(const std::string& nameOfDataDistribution, const PUWeight::Scenario sc) {

  if( isInit_ ) {
    std::cerr << "\n\nERROR in PUWeight: weights already initialised" << std::endl;
    throw std::exception();
  }

  // Get data distribution from file
  TFile file(nameOfDataDistribution.c_str(), "READ");
  TH1* h = NULL;
  file.GetObject("pileup",h);
  if( h == NULL ) {
    std::cerr << "\n\nERROR in PUWeight: Histogram 'pileup' does not exist in file '" << nameOfDataDistribution << "'\n.";
    throw std::exception();
  }
  h->SetDirectory(0);
  file.Close();

  // Computing weights
  puWeigths_ = generateWeights(sc,h);
  nPUMax_ = puWeigths_.size();

  // Clean up
  delete h;

  isInit_ = true;
}

//==============================================================================================
// Get weight factor dependent on number of added PU interactions
double PUWeight::getPUWeight(const int nPU) const {

  double w = 1.;
  if( isInit_ ) {
    if( nPU >= nPUMax_ ) {
      //std::cerr << "WARNING: Number of PU vertices = " << nPU << " out of histogram binning." << std::endl;
      // In case nPU is out-of data-profile binning,
      // use weight from last bin
      w = puWeigths_.back();
    } else {
      w = puWeigths_.at(nPU);
    }
  }

  return w;
}

//==============================================================================================
// Generate weights for given data PU distribution
// Scenarios from: https://twiki.cern.ch/twiki/bin/view/CMS/Pileup_MC_Gen_Scenarios
// Code adapted from: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupReweighting
std::vector<double> PUWeight::generateWeights(const PUWeight::Scenario sc, const TH1* data_npu_estimated) const {

  // Store probabilites for each pu bin
  unsigned int nPUMax = 0;
  double *npuProbs = 0;

  //if( sc == Winter15_25ns ) {
  
    nPUMax = 52;
    double npuWinter15_25ns[52] = {
                              4.8551E-07,
                              1.74806E-06,
                              3.30868E-06,
                              1.62972E-05,
                              4.95667E-05,
                              0.000606966,
                              0.003307249,
                              0.010340741,
                              0.022852296,
                              0.041948781,
                              0.058609363,
                              0.067475755,
                              0.072817826,
                              0.075931405,
                              0.076782504,
                              0.076202319,
                              0.074502547,
                              0.072355135,
                              0.069642102,
                              0.064920999,
                              0.05725576,
                              0.047289348,
                              0.036528446,
                              0.026376131,
                              0.017806872,
                              0.011249422,
                              0.006643385,
                              0.003662904,
                              0.001899681,
                              0.00095614,
                              0.00050028,
                              0.000297353,
                              0.000208717,
                              0.000165856,
                              0.000139974,
                              0.000120481,
                              0.000103826,
                              8.88868E-05,
                              7.53323E-05,
                              6.30863E-05,
                              5.21356E-05,
                              4.24754E-05,
                              3.40876E-05,
                              2.69282E-05,
                              2.09267E-05,
                              1.5989E-05,
                              4.8551E-06,
                              2.42755E-06,
                              4.8551E-07,
                              2.42755E-07,
                              1.21378E-07,
                              4.8551E-08};
    npuProbs = npuWinter15_25ns;

  //}


  // Check that binning of data-profile matches MC scenario
  if( nPUMax != static_cast<unsigned int>(data_npu_estimated->GetNbinsX()) ) {
    std::cerr << "\n\nERROR number of bins (" << data_npu_estimated->GetNbinsX() << ") in data PU-profile does not match number of bins (" << nPUMax << ") in MC scenario " << toString(sc) << std::endl;
    throw std::exception();
  }

  std::vector<double> result(nPUMax,0.);
  double s = 0.;
  for(unsigned int npu = 0; npu < nPUMax; ++npu) {
    const double npu_estimated = data_npu_estimated->GetBinContent(data_npu_estimated->GetXaxis()->FindBin(npu));
    result[npu] = npu_estimated / npuProbs[npu];
    s += npu_estimated;
  }
  // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
  for(unsigned int npu = 0; npu < nPUMax; ++npu) {
    result[npu] /= s;
  }

  return result;
}

