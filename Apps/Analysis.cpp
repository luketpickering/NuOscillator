#include "OscillatorBinned.h"
#include "OscillatorUnbinned.h"

#include "OscillatorConstants.h"

#include <iostream>
#include <math.h>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

std::vector<FLOAT_T> logspace(FLOAT_T Emin, FLOAT_T  Emax, int nDiv);
std::vector<FLOAT_T> linspace(FLOAT_T Emin, FLOAT_T Emax, int nDiv);

int main() {
  int Verbose = NONE;
  bool PrintWeights = false;

  std::vector<FLOAT_T> OscParams_Atm(7);
  OscParams_Atm[0] = 3.07e-1;
  OscParams_Atm[1] = 5.28e-1;
  OscParams_Atm[2] = 2.18e-2;
  OscParams_Atm[3] = 7.53e-5;
  OscParams_Atm[4] = 2.509e-3;
  OscParams_Atm[5] = -1.601;
  OscParams_Atm[6] = 25.0;

  std::vector<FLOAT_T> OscParams_Beam(8);
  OscParams_Beam[0] = 3.07e-1;
  OscParams_Beam[1] = 5.28e-1;
  OscParams_Beam[2] = 2.18e-2;
  OscParams_Beam[3] = 7.53e-5;
  OscParams_Beam[4] = 2.509e-3;
  OscParams_Beam[5] = -1.601;
  OscParams_Beam[6] = 250.0;
  OscParams_Beam[7] = 2.6;

  std::vector<FLOAT_T> EnergyArray = logspace(0.1,100.,1e3);
  std::vector<FLOAT_T> CosineZArray = linspace(-1.0,1.0,1e3);

  std::cout << "========================================================" << std::endl;
  std::cout << "Starting setup in executable" << std::endl;

  std::vector<OscillatorBase*> Oscillators;
  std::string ConfigName;

#if UseCUDAProb3 == 1
  std::cout << "========================================================" << std::endl;
  std::cout << "Setting up Binned_CUDAProb3" << std::endl;

  ConfigName = "./Configs/Binned_CUDAProb3.yaml";
  OscillatorBinned* Oscillator_CUDAProb3Binned = new OscillatorBinned(ConfigName);
  Oscillators.push_back((OscillatorBase*)Oscillator_CUDAProb3Binned);

  std::cout << "========================================================" << std::endl;
  std::cout << "Setting up Unbinned_CUDAProb3" << std::endl;

  ConfigName = "./Configs/Unbinned_CUDAProb3.yaml";
  OscillatorUnbinned* Oscillator_CUDAProb3Unbinned = new OscillatorUnbinned(ConfigName);
  Oscillator_CUDAProb3Unbinned->SetEnergyArray(EnergyArray);
  Oscillator_CUDAProb3Unbinned->SetCosineZArray(CosineZArray);
  Oscillators.push_back((OscillatorBase*)Oscillator_CUDAProb3Unbinned);
#endif

#if UseCUDAProb3Linear == 1
  std::cout << "========================================================" << std::endl;
  std::cout << "Initialising Binned_CUDAProb3Linear" << std::endl;

  ConfigName = "./Configs/Binned_CUDAProb3Linear.yaml";
  OscillatorBinned* Oscillator_CUDAProb3LinearBinned = new OscillatorBinned(ConfigName);
  Oscillators.push_back((OscillatorBase*)Oscillator_CUDAProb3LinearBinned);

  std::cout << "========================================================" << std::endl;
  std::cout << "Initialising Unbinned_CUDAProb3Linear" << std::endl;

  ConfigName = "./Configs/Unbinned_CUDAProb3Linear.yaml";
  OscillatorUnbinned* Oscillator_CUDAProb3LinearUnbinned = new OscillatorUnbinned(ConfigName);
  Oscillator_CUDAProb3LinearUnbinned->SetEnergyArray(EnergyArray);
  Oscillators.push_back((OscillatorBase*)Oscillator_CUDAProb3LinearUnbinned);
#endif

#if UseProbGPULinear == 1
  std::cout << "========================================================" << std::endl;
  std::cout << "Initialising Binned_ProbGPULinear" << std::endl;

  ConfigName = "./Configs/Binned_ProbGPULinear.yaml";
  OscillatorBinned* Oscillator_ProbGPULinearBinned = new OscillatorBinned(ConfigName);
  Oscillators.push_back((OscillatorBase*)Oscillator_ProbGPULinearBinned);

  std::cout << "========================================================" << std::endl;
  std::cout << "Initialising Unbinned_ProbGPULinear" << std::endl;

  ConfigName = "./Configs/Unbinned_ProbGPULinear.yaml";
  OscillatorUnbinned* Oscillator_ProbGPULinearUnbinned = new OscillatorUnbinned(ConfigName);
  Oscillator_ProbGPULinearUnbinned->SetEnergyArray(EnergyArray);
  Oscillators.push_back((OscillatorBase*)Oscillator_ProbGPULinearUnbinned);
#endif 

#if UseProb3ppLinear == 1
  std::cout << "========================================================" << std::endl;
  std::cout << "Initialising Binned_Prob3ppLinear" << std::endl;

  ConfigName = "./Configs/Binned_Prob3ppLinear.yaml";
  OscillatorBinned* Oscillator_Prob3ppLinearBinned = new OscillatorBinned(ConfigName);
  Oscillators.push_back((OscillatorBase*)Oscillator_Prob3ppLinearBinned);

  std::cout << "========================================================" << std::endl;
  std::cout << "Initialising Unbinned_Prob3ppLinear" << std::endl;

  ConfigName = "./Configs/Binned_Prob3ppLinear.yaml";
  OscillatorUnbinned* Oscillator_Prob3ppLinearUnbinned = new OscillatorUnbinned(ConfigName);
  Oscillator_Prob3ppLinearUnbinned->SetEnergyArray(EnergyArray);
  Oscillators.push_back((OscillatorBase*)Oscillator_Prob3ppLinearUnbinned);
#endif

  /*
  //Alternative option to show how all information can be held in a single YAML file rather than using a preset
  ConfigName = "./Configs/CUDAProb3_Binned-SelfContainedFile.yaml";
  OscillatorBinned* MyOscillator = new OscillatorBinned(ConfigName);
  Oscillators.push_back((OscillatorBase*)MyOscillator);
  */

  std::cout << "========================================================" << std::endl;
  std::cout << "Setting up Oscillators" << std::endl;

  // Setup propagators
  for (size_t iOsc=0;iOsc<Oscillators.size();iOsc++) {
    Oscillators[iOsc]->Setup();
  }
  
  std::cout << "Finished setup in executable" << std::endl;
  std::cout << "========================================================" << std::endl;
  std::cout << "Starting reweight in executable" << std::endl;

  // Reweight and calculate oscillation probabilities
  for (size_t iOsc=0;iOsc<Oscillators.size();iOsc++) {
    // These don't have to be explicilty beam or atmospheric specific, all they have to be is equal to the number of oscillation parameters expected by the implementation
    // If you have some NSI calculater, then it will work providing the length of the vector of oscillation parameters is equal to the number of expected oscillation parameters
    if (Oscillators[iOsc]->ReturnNOscParams() == (int)OscParams_Beam.size()) {
      Oscillators[iOsc]->CalculateProbabilities(OscParams_Beam); 
    } else if (Oscillators[iOsc]->ReturnNOscParams() == (int)OscParams_Atm.size()) {
      Oscillators[iOsc]->CalculateProbabilities(OscParams_Atm);
    } else {
      std::cerr << "Did not find viable oscillation parameters to hand to the oscillation probability calculater" << std::endl;
      std::cerr << "Oscillator->ReturnNOscParams():" << Oscillators[iOsc]->ReturnNOscParams() << std::endl;
      throw;
    }
  
    if (PrintWeights) {
      Oscillators[iOsc]->PrintWeights();
    }
  }

  std::cout << "Finished reweight in executable" << std::endl;
  std::cout << "========================================================" << std::endl;
}

std::vector<FLOAT_T> logspace(FLOAT_T Emin, FLOAT_T  Emax, int nDiv) {
  if (nDiv==0) {
    std::cerr << "Requested log spacing distribution with 0 divisions" << std::endl;
    throw;
  }

  std::vector<FLOAT_T> logpoints(nDiv+1, 0.0);
  logpoints[0]=Emin;

  if (Emin == 0.) {
    Emin = 0.01;
  }

  FLOAT_T Emin_log,Emax_log;
  Emin_log = log10(Emin);
  Emax_log = log10(Emax);

  FLOAT_T step_log = (Emax_log - Emin_log)/FLOAT_T(nDiv);

  FLOAT_T EE = Emin_log+step_log;

  for (int i=1; i<nDiv; i++) {
    logpoints[i] = pow(10.,EE);
    EE += step_log;
  }

  logpoints[nDiv]=Emax;

  return logpoints;
}

std::vector<FLOAT_T> linspace(FLOAT_T Emin, FLOAT_T Emax, int nDiv) {
  if (nDiv==0) {
    std::cerr << "Requested linear spacing distribution with 0 divisions" << std::endl;
    throw;
  }

  std::vector<FLOAT_T> linpoints(nDiv+1, 0.0);

  FLOAT_T step_lin = (Emax - Emin)/FLOAT_T(nDiv);

  FLOAT_T EE = Emin;

  for (int i=0; i<nDiv; i++) {
    if (fabs(EE)<1e-6) {EE = 0.;}

    linpoints[i] = EE;
    EE += step_lin;
  }

  linpoints[nDiv] = Emax;

  return linpoints;
}
