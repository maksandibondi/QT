#include "DLL1.h"

using namespace std;

/*extern "C"*/ DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{


    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}


RandomVar::RandomVar() : numberOfVar(100), simulated_Mean(0), simulated_Sigma(0), mean(0), sigma(1) {
	simulatedVarVector = new vector <double>[numberOfVar];
}

RandomVar::RandomVar(double mean, double sigma) : numberOfVar(100), simulated_Mean(0), simulated_Sigma(0), mean(mean), sigma(sigma) {
	simulatedVarVector = new vector <double>[numberOfVar];
}

RandomVar :: ~RandomVar(){
	delete simulatedVarVector;
}

double& RandomVar::Mean(){
	return (this->mean);
}

double& RandomVar::Sigma(){
	return (this->sigma);
}

double& RandomVar::simulatedMean(){
	return (this->simulated_Mean);
}

double& RandomVar::simulatedSigma(){
	return (this->simulated_Sigma);
}

// error processing has to exist as distribution works really well for Mean = [5:700]
void RandomVar::initializeMeanSigma(double& Mean, double&Sigma){
	this->mean = Mean;
	this->sigma = Sigma;
}

RandNormal::RandNormal() : RandomVar(0, 1) {
}

RandNormal :: ~RandNormal(){
}

vector <double>& RandNormal::simulate(int& numberOfVar){

	double tempVar = 0;

	for (int i = 0; i < numberOfVar; i++){
		double arithmetic_mean = 0;

		for (int k = 0; k < 50; k++){
			arithmetic_mean = arithmetic_mean + (rand() / static_cast<double>(RAND_MAX)) / 50;
		}

		double temp = (arithmetic_mean - 0.5) * pow((12 * 50), 0.5) * (this->sigma) + this->mean;

		this->simulatedVarVector->push_back(temp);
		this->simulated_Mean = this->simulated_Mean + temp / static_cast<double>(numberOfVar);
		tempVar = tempVar + temp*temp / static_cast<double>(numberOfVar);

	}

	this->simulated_Sigma = sqrt(tempVar - (this->simulated_Mean)*(this->simulated_Mean));
	return *(this->simulatedVarVector);
}

RandPoisson::RandPoisson() : RandomVar(10, 10) {
}

RandPoisson :: ~RandPoisson(){
}

vector <double>& RandPoisson::simulate(int& numberOfVar){

	double tempVar = 0;
	for (int i = 0; i < numberOfVar; i++){
		double random = rand() / static_cast<double>(RAND_MAX);
		double pdf = exp(-this->mean);
		int temp = 0;
		for (double sum = pdf; (sum < random) && (temp < this->mean * 5); sum = sum + pdf){
			temp = temp + 1;
			pdf = pdf*(this->mean) / temp;
		}
		this->simulatedVarVector->push_back(temp);
		this->simulated_Mean = this->simulated_Mean + temp / static_cast<double>(numberOfVar);
		tempVar = tempVar + temp*temp / static_cast<double>(numberOfVar);
	}
	this->simulated_Sigma = sqrt(tempVar - (this->simulated_Mean)*(this->simulated_Mean));
	return *(simulatedVarVector);
}

RandUniform::RandUniform() : downlimit(0), uplimit(1), RandomVar(0.5, sqrt(1 / 12)) {
}

RandUniform :: ~RandUniform(){
}

vector <double>& RandUniform::simulate(int& numberOfVar){

	double tempVar = 0;
	for (int i = 0; i < numberOfVar; i++){
		double temp = this->downlimit + (this->uplimit - this->downlimit)*(rand() / static_cast<double>(RAND_MAX));
		this->simulatedVarVector->push_back(temp);
		this->simulated_Mean = this->simulated_Mean + temp / numberOfVar;
		tempVar = tempVar + temp*temp / numberOfVar;
	}
	this->simulated_Sigma = sqrt(tempVar - (this->simulated_Mean)*(this->simulated_Mean));
	return *(simulatedVarVector);
}

void RandUniform::initializeUpperLimit(double& uplimit){
	this->uplimit = uplimit;
	this->sigma = sqrt((this->uplimit - this->downlimit)*(this->uplimit - this->downlimit) / 12);
	this->mean = (this->uplimit + this->downlimit) / 2;
}

void RandUniform::initializeDownLimit(double& downlimit){
	this->downlimit = downlimit;
	this->sigma = sqrt((this->uplimit - this->downlimit)*(this->uplimit - this->downlimit) / 12);
	this->mean = (this->uplimit + this->downlimit) / 2;
}





StochasticProcess::StochasticProcess() : drift(0), diffusion(1), initial_value(0), simulated_drift(0), simulated_diffusion(0) {
	simulatedPathVector = new vector <double>[100];
}

StochasticProcess::StochasticProcess(double drift) : drift(drift), diffusion(1), initial_value(0), simulated_drift(0), simulated_diffusion(0){
	simulatedPathVector = new vector <double>[100];
}

StochasticProcess::StochasticProcess(double drift, double diffusion) : drift(drift), diffusion(diffusion), initial_value(0), simulated_drift(0), simulated_diffusion(0){
	simulatedPathVector = new vector <double>[100];
}

StochasticProcess::~StochasticProcess(){
	delete simulatedPathVector;
}

void StochasticProcess::initializeDriftDiffusion(double& drift, double& diffusion){
	this->drift = drift;
	this->diffusion = diffusion;
}

void StochasticProcess::initializeInitial_Value(double& initial_value){
	this->initial_value = initial_value;
}

double& StochasticProcess::Drift(){
	return this->drift;
}

double& StochasticProcess::Diffusion(){
	return this->diffusion;
}

double& StochasticProcess::Simulated_drift(){
	return this->simulated_drift;
}

double& StochasticProcess::Simulated_diffusion(){
	return this->simulated_diffusion;
}

WienerProcess::WienerProcess() : StochasticProcess(){

}

WienerProcess::~WienerProcess(){

}

vector <double>& WienerProcess::simulate(int& numberOfValues){
	RandomVar *Rand;
	Rand = new RandNormal();
	vector <double> array = Rand->simulate(numberOfValues);

	double tempvalue = this->initial_value;
	for (int i = 0; i < numberOfValues; i++){
		tempvalue = tempvalue + (this->drift) + (this->diffusion)*array[i];
		this->simulatedPathVector->push_back(tempvalue);
	}

	return *(simulatedPathVector);
}

GBMProcess::GBMProcess() : StochasticProcess(2, 5){

}

GBMProcess::~GBMProcess(){

}

vector <double>& GBMProcess::simulate(int& numberOfValues){
	RandomVar *Rand;
	Rand = new RandNormal();
	vector <double> array = Rand->simulate(numberOfValues);

	double tempvalue = this->initial_value;
	for (int i = 0; i < numberOfValues; i++){
		tempvalue = tempvalue + (this->drift)*tempvalue + (this->diffusion)*tempvalue*array[i];
		this->simulatedPathVector->push_back(tempvalue);
	}

	return *(simulatedPathVector);
}
