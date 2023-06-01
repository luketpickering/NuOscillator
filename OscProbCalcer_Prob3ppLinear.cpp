#include "OscProbCalcer_Prob3ppLinear.h"

#include <iostream>

OscProbCalcerProb3ppLinear::OscProbCalcerProb3ppLinear() : OscProbCalcerBase()
{
  // Required variables
  fNOscParams = kNOscParams;

  nNeutrinoTypes = 2;
  NeutrinoTypes.resize(nNeutrinoTypes);
  NeutrinoTypes[0] = Nu;
  NeutrinoTypes[1] = Nubar;

  nInitialFlavours = 2;
  InitialFlavours.resize(nInitialFlavours);
  InitialFlavours[0] = Electron;
  InitialFlavours[1] = Muon;

  nFinalFlavours = 2;
  FinalFlavours.resize(nFinalFlavours);
  FinalFlavours[0] = Electron;
  FinalFlavours[1] = Muon;

  // This implementation only considers linear propagation, thus no requirement to set cosineZ array
  IgnoreCosineZBinning(true);

  // Implementation specific variables
  doubled_angle = true;
}

void OscProbCalcerProb3ppLinear::SetupPropagator() {
   bNu = new BargerPropagator();
   bNu->UseMassEigenstates(false);
   bNu->SetOneMassScaleMode(false);
   bNu->SetWarningSuppression(true); 
}

void OscProbCalcerProb3ppLinear::CalculateProbabilities(std::vector<FLOAT_T> OscParams) {
  // Prob3++ calculates oscillation probabilites for each NeutrinoType and each energy, so need to copy them from the calculator into fWeightArray
  for (int iNuType=0;iNuType<nNeutrinoTypes;iNuType++) {
    for (int iInitFlav=0;iInitFlav<nInitialFlavours;iInitFlav++) {
      for (int iFinalFlav=0;iFinalFlav<nFinalFlavours;iFinalFlav++) {

        // Mapping which links the oscillation channel, neutrino type and energy index to the fWeightArray index
        int IndexToFill = iNuType*nInitialFlavours*nFinalFlavours*fNEnergyPoints + iInitFlav*nFinalFlavours*fNEnergyPoints + iFinalFlav*fNEnergyPoints;

        for (int iOscProb=0;iOscProb<fNEnergyPoints;iOscProb++) {
	  bNu->SetMNS(OscParams[kTH12], OscParams[kTH23], OscParams[kTH13], OscParams[kDM12], OscParams[kDM23], OscParams[kDCP], fEnergyArray[iOscProb], doubled_angle);
	  bNu->propagateLinear(NeutrinoTypes[iNuType]*iInitFlav, OscParams[kPATHL], OscParams[kDENS]);
          fWeightArray[IndexToFill+iOscProb] = bNu->GetProb(NeutrinoTypes[iNuType]*iInitFlav, NeutrinoTypes[iNuType]*iFinalFlav);
        }
      }
    }
  }

}

int OscProbCalcerProb3ppLinear::ReturnWeightArrayIndex(int NuTypeIndex, int InitNuIndex, int FinalNuIndex, int EnergyIndex, int CosineZIndex) {
  int IndexToReturn = NuTypeIndex*nInitialFlavours*nFinalFlavours*fNEnergyPoints + InitNuIndex*nFinalFlavours*fNEnergyPoints + FinalNuIndex*fNEnergyPoints + EnergyIndex;
  return IndexToReturn;
}

long OscProbCalcerProb3ppLinear::DefineWeightArraySize() {
  long nCalculationPoints = fNEnergyPoints * nInitialFlavours * nFinalFlavours * nNeutrinoTypes;
  return nCalculationPoints;
}
