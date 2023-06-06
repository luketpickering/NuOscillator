#ifndef __OSCILLATOR_BASE_H__
#define __OSCILLATOR_BASE_H__

#include "OscProbCalcerBase.h"

/**
 * @file OscillatorBase.h
 *
 * @class OscillatorBase
 *
 * @brief Oscillation calculation (binned, unbinned, etc.) implementation agnostic base class.
 *
 * The base class which controls the calculation of neutrino oscillation probabilities through various calculation techniques. There are
 * oscillation calculation techniques which can be implemented (e.g. binned, unbinned) which are expected to be derived classes of this
 * base function.
 */
class OscillatorBase {
 public:

  // ========================================================================================================================================================================
  // Public functions which are calculation implementation agnostic

  /**
   * @brief Perform a sanity check which ensures that #fOscProbCalcers have been set correctly.
   *
   * Ensure that: the #fOscProbCalcers has been initialised with atleast one OscProbCalcerBase::OscProbCalcerBase() instance, each OscProbCalcerBase::OscProbCalcerBase()
   * instance passes the sanity check, and that each OscProbCalcerBase::OscProbCalcerBase() instance has the same CosineZ treatement as the OscillatorBase()
   * instance expects.
   */
  void SanityCheck();

  /**
   * @brief Calculate the oscillation probabilities for the providied oscillation probabilities.
   *
   * For each instance of OscProbCalcerBase::OscProbCalcerBase in #fOscProbCalcers, calculate the oscillation probabilites for the provided oscillation parameters.
   *
   * @param OscParams Vector of oscillation parameters to calculate probabities at.
   */
  void CalculateProbabilities(std::vector<FLOAT_T> OscParams);

  /**
   * @brief Return number of expected oscillation parameters for a particular OscProbCalcerBase::OscProbCalcerBase() instance in #fOscProbCalcers.
   *
   * Each instance of OscProbCalcerBase::OscProbCalcerBase expects a particular number of oscillation parameters. This function returns this value for an 
   * OscProbCalcerBase::OscProbCalcerBase instance in #fOscProbCalcers.
   *
   * @param CalcerIndex Index of #fOscProbCalcers instance in which to query
   * @return The number of expected oscillation parameters from the CalcerIndex-th index in #fOscProbCalcers
   */
  int ReturnNOscParams(int CalcerIndex=0);

  /**
   * @brief Print the oscillation probabilities for a particular OscProbCalcerBase::OscProbCalcerBase() instance in #fOscProbCalcers.
   *
   * Print the calculated oscillation probability values for a particular OscProbCalcerBase::OscProbCalcerBase() instance in #fOscProbCalcers.
   * This is typically performed after a call to CalculateProbabilities()
   *
   * @param CalcerIndex Index of #fOscProbCalcers instance in which to query
   */
  void PrintWeights(int CalcerIndex=0);

  /**
   * @brief Setup each instance of OscProbCalcerBase::OscProbCalcerBase() instance in #fOscProbCalcers
   *
   * Setup function is public so that OscProbCalcerBase::OscProbCalcerBase() instances, when using the unbinned calculation implementation, can be setup. The unbinned
   * implementation assumes that the Energy and CosineZ arrays will be set after the OscillatorBase() object has been initialised.
   */
  void Setup();

  //DB
  std::string ReturnImplementationName();

  //DB
  int ReturnNEnergyPoints(int CalcerIndex=0);

  // ========================================================================================================================================================================
  // Public virtual functions which need calculater specific implementations

  /**
   * @brief Return a pointer to the oscillation probability for the requested event attributes
   *
   * Determine the memory address address where the calculated oscillation probability for events of the specific requested type will be stored. This will be different
   * depending on the calculation implementation. For the binned approach, the particular bin in which the requested energy and cosine falls will need to be determined.
   * For unbinned approach, the exact neutrino energy and cosine are expected to be used. Alternative approachs which smear the oscillation probability will be able to
   * use this function to apply the smear.
   *
   * @param InitNuFlav Initial neutrino flavour of the neutrino
   * @param FinalNuFlav Final neutrino flavour of the neutrino
   * @param EnergyVal True energy of the neutrino
   * @param CosineZVal True direction of the neutrino in CosineZ
   *
   * @return Pointer to the memory address where the calculated oscillation probability for events of the specific requested type will be stored
   */
  virtual const FLOAT_T* ReturnWeightPointer(int InitNuFlav, int FinalNuFlav, FLOAT_T EnergyVal, FLOAT_T CosineZVal=DUMMYVAL) = 0;

 protected:
  // ========================================================================================================================================================================
  // Protected functions which are calculation implementation agnostic

  /**
   * @brief Default constructor
   */
  OscillatorBase();

  /**
   * @brief Initialise an OscProbCalcerBase::OscProbCalcerBase() instance for each entry in #fOscProbCalcerImplementationToCreate
   *
   * #fOscProbCalcerImplementationToCreate is expected to be initialised within the costructor of the calculation specific code. For each entry in this vector, create an 
   * instance of OscProbCalcerBase::OscProbCalcerBase() and store it in #fOscProbCalcers. This function first parses the #fOscProbCalcerImplementationToCreate vector to
   * ensure that it is correctly filled by the calculation specific code. It then calls InitialiseOscProbCalcer(), for each entry in #fOscProbCalcerImplementationToCreate
   * and it is that function which actually initialises a specific OscProbCalcerBase::OscProbCalcerBase() object and returns it.
   */
  void InitialiseOscProbCalcers();

  /**
   * @brief Set the energy array which will be used by the OscProbCalcerBase::OscProbCalcerBase() instance stored in a particular index in #fOscProbCalcers
   *
   * Each instance of OscProbCalcerBase::OscProbCalcerBase() needs an energy array which will be used to calculate the oscillation probabilities. This function sets that
   * array
   *
   * @param Array The energy array which will be passed to the OscProbCalcerBase::OscProbCalcerBase() instance
   * @param CalcerIndex The index iin #fOscProbCalcers which will be handed the energy array
   */
  void SetEnergyArrayInCalcer(std::vector<FLOAT_T> Array, int CalcerIndex=0);

  /**
   * @brief Set the energy array which will be used by the OscProbCalcerBase::OscProbCalcerBase() instance stored in a particular index in #fOscProbCalcers
   *
   * Each instance of OscProbCalcerBase::OscProbCalcerBase() needs an energy array which will be used to calculate the oscillation probabilities. This function sets that
   * array
   *
   * @param Array The energy array which will be passed to the OscProbCalcerBase::OscProbCalcerBase() instance
   * @param CalcerIndex The index iin #fOscProbCalcers which will be handed the energy array
   */
  void SetCosineZArrayInCalcer(std::vector<FLOAT_T> Array, int CalcerIndex=0);

  /**
   * @brief Return a pointer to the oscillation probability memory address in a particular index of #fOscProbCalcers for a particular event
   *
   * Return the memory address for the oscillation probability which is calculated for neutrinos of a particular initial and final flavour, energy and cosine value. This is
   * a memory address for a particular OscProbCalcerBase::OscProbCalcerBase() instance stored in a particular index in #fOscProbCalcers.
   *
   * @param CalcerIndex The index in #fOscProbCalcers.
   * @param InitNuFlav Initial neutrino flavour of event
   * @param FinalNuFlav Final neutrino flavour of event
   * @param EnergyVal Neutrino energy of event
   * @param CosineZVal Netrino cosine zenith direction of event
   *
   * @return Memory address associated with given event attributes for CalcerIndex-th index in #fOscProbCalcers
   */
  const FLOAT_T* ReturnPointerToWeightinCalcer(int CalcerIndex, int InitNuFlav, int FinalNuFlav, FLOAT_T EnergyVal, FLOAT_T CosineZVal=DUMMYVAL);
  
  // ========================================================================================================================================================================
  // Protected virtual functions which are calculation implementation agnostic
  
  // ========================================================================================================================================================================
  // Basic protected variables required for oscillation probability calculation

  /**
   * @brief A vector used for initialising #fOscProbCalcers. It contains strings for the different OscProbCalcerBase::OscProbCalcerBase() objects to initialise. These 
   * strings should match those in InitialiseOscProbCalcer()
   */
  std::vector<std::string> fOscProbCalcerImplementationToCreate;

  /**
   * @brief A boolean used for declaring whether the OscillatorBase() object expects to care about the CosineZ dimension
   */
  bool fCosineZIgnored;

  /**
   * @brief This is a vector object to accomodate any implementations which require multiple calculators to perform the reweight
   * For instance, this could be used to deal with the MaCh3 Event-by-Event approach by having a OscProbCalcerBase object for each oscillation channel
   */
  int fNCalcers;

  /**
   * @brief A vector which contains all instances of OscProbCalcerBase()
   */
  std::vector<OscProbCalcerBase*> fOscProbCalcers;

  //DB
  std::string fCalculationTypeName;

  /**
   * @brief The verbosity level of console output
   */
  int fVerbose;

 private:

  /**
   * @brief Return an OscProbCalcerBase::OscProbCalcerBase() object from the requested string input
   *
   * Create and return an instance of OscProbCalcerBase::OscProbCalcerBase() associated from the particular string input. The string is used as a switch statement to create
   * a particular calculator implementation object (e.g. OscProbCalcer_CUDAProb3::OscProbCalcer_CUDAProb3() ) and recasts it into the base object 
   * OscProbCalcerBase::OscProbCalcerBase()
   *
   * @param OscProbCalcerImplementationToCreate Type of implementation specific OscProbCalcerBase::OscProbCalcerBase() to build. E.g. ProbGPULinear
   *
   * @return OscProbCalcerBase::OscProbCalcerBase() object corresponding to the request string input
   */
  OscProbCalcerBase* InitialiseOscProbCalcer(std::string OscProbCalcerImplementationToCreate);

  // ========================================================================================================================================================================
  // Basic private variables required for oscillation probability calculation

  /**
   * @brief A boolean which declares whether #fOscProbCalcers has been initialised
   */
  bool fOscProbCalcerSet;
};

#endif
