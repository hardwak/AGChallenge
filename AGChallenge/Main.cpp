#include "Evaluator.h"
#include "Timer.h"
#include "CGeneticAlgorithm.h"

#include <exception>
#include <iostream>
#include <random>
#include <iomanip>

using namespace TimeCounters;

using namespace std;

#define dMAX_TIME 20 * 60

int popSize = 20;
double crossProb = 0.8;
double mutProb = 0.5;


void vRunExperiment(CLFLnetEvaluator &cConfiguredEvaluator)
{
	try
	{
		CTimeCounter c_time_counter;

		double d_time_passed;

		CGeneticAlgorithm c_genetic_algorithm(cConfiguredEvaluator, popSize, crossProb, mutProb);

		c_time_counter.vSetStartNow();

		c_time_counter.bGetTimePassed(&d_time_passed);

//		std::cout << std::fixed << std::setprecision(18);

		while (d_time_passed <= dMAX_TIME)
		{
			c_genetic_algorithm.vRunIteration();
			c_genetic_algorithm.getBestSolution();

			c_time_counter.bGetTimePassed(&d_time_passed);
		}//while (d_time_passed <= MAX_TIME)
	}//try
	catch (exception &c_exception)
	{
		cout << c_exception.what() << endl;
	}//catch (exception &c_exception)
}//void vRunExperiment(const CEvaluator &cConfiguredEvaluator)



void  vRunLFLExperiment(CString  sNetName)
{
	CLFLnetEvaluator c_lfl_eval;
	c_lfl_eval.bConfigure(sNetName);
	vRunExperiment(c_lfl_eval);
	
}//void vRunRastriginExperiment(int iNumberOfBits, int iBitsPerFloat, int iMaskSeed)



void main(int iArgCount, char **ppcArgValues)
{
	random_device c_mask_seed_generator;
	int i_mask_seed = (int)c_mask_seed_generator();

	cout << "start\n";
#pragma omp parallel for
	for (int i = 0; i < 10; i++)
		Sleep(1000);
	

	CString  s_test;
	vRunLFLExperiment("104b00");
	cout << "end\n";

	/*vRunIsingSpinGlassExperiment(81, 0, i_mask_seed);
	vRunIsingSpinGlassExperiment(81, 0, iSEED_NO_MASK);

	vRunLeadingOnesExperiment(50, i_mask_seed);
	vRunLeadingOnesExperiment(50, iSEED_NO_MASK);

	vRunMaxSatExperiment(25, 0, 4.27f, i_mask_seed);
	vRunMaxSatExperiment(25, 0, 4.27f, iSEED_NO_MASK);

	vRunNearestNeighborNKExperiment(100, 0, 4, i_mask_seed);
	vRunNearestNeighborNKExperiment(100, 0, 4, iSEED_NO_MASK);

	vRunOneMaxExperiment(100, i_mask_seed);
	vRunOneMaxExperiment(100, iSEED_NO_MASK);

	vRunRastriginExperiment(200, 10, i_mask_seed);
	vRunRastriginExperiment(200, 10, iSEED_NO_MASK);*/
}//void main(int iArgCount, char **ppcArgValues)