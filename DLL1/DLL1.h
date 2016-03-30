#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifndef DLL_EXPORT
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction(const LPCSTR sometext);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__


#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <cmath>
#include <string>



class DLL_EXPORT RandomVar{

		//	friend void* operator new(std::size_t obj);

	protected:
		//double mean, simulated_Mean;
		//double sigma, simulated_Sigma;
		//int numberOfVar;
		//std::vector <double> *simulatedVarVector = nullptr;
		RandomVar();
		RandomVar(double mean, double sigma);
		virtual ~RandomVar();

	public:
		double mean, simulated_Mean;
		double sigma, simulated_Sigma;
		int numberOfVar;
		std::vector <double> *simulatedVarVector = nullptr;
		void initializeMeanSigma(double& Mean, double&Sigma); // does not work for subclass RandUniform as there are up down limits. Another problem - user can input bad numbers or strings
		double& Mean();
		double& Sigma();
		double& simulatedMean();
		double& simulatedSigma();
		virtual std::vector<double>& simulate(int& numberOfVar) = 0;
	};

class DLL_EXPORT RandNormal : public RandomVar {

		//	friend <typename RandNormal> PDF::PDF(typename &object);

	public:
		RandNormal();
		virtual ~RandNormal();

	public:
		std::vector <double>& simulate(int& numberOfVar);
	};

class DLL_EXPORT RandPoisson : public RandomVar {

	public:
		RandPoisson();
		virtual ~RandPoisson();

	public:
		std::vector <double>& simulate(int& numberOfVar);
	};

class DLL_EXPORT RandUniform : public RandomVar  {

	protected:
		double downlimit;
		double uplimit;

	public:
		RandUniform();
		virtual ~RandUniform();

	public:
		std::vector <double>& simulate(int& numberOfVar);
		void initializeUpperLimit(double& uplimit);
		void initializeDownLimit(double& downlimit);
	};

class DLL_EXPORT StochasticProcess{

	protected: //attributes
		double drift, simulated_drift;
		double diffusion, simulated_diffusion;
		double initial_value;
		std::vector <double> *simulatedPathVector = nullptr;

	protected: //Constructors and destructor
		StochasticProcess();
		StochasticProcess(double drift);
		StochasticProcess(double drift, double diffusion);
		virtual ~StochasticProcess();

	public: // declaration of methods
		virtual std::vector <double>& simulate(int& numberOfValues) = 0;
		void initializeDriftDiffusion(double& drift, double& diffusion); // does not work for subclass RandUniform as there are up down limits. Another problem - user can input bad numbers or strings
		void initializeInitial_Value(double& initial_value);
		double& Drift();
		double& Diffusion();
		double& Simulated_drift();
		double& Simulated_diffusion();
	};

class DLL_EXPORT WienerProcess : public StochasticProcess{

	public:
		WienerProcess();
		virtual ~WienerProcess();

	public:
		std::vector <double>& simulate(int& numberOfValues);
	};

class DLL_EXPORT GBMProcess : public StochasticProcess {

	public:
		GBMProcess();
		virtual ~GBMProcess();

	public:
		std::vector <double>& simulate(int& numberOfValues);
	};
