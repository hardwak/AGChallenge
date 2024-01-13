#pragma once
#include <vector>
#include <random>
#include "Evaluator.h"

class CIndividual
{
private:
	std::vector<int> solution;
	CLFLnetEvaluator cEvaluator;
	double fitness;

	void randomFill(std::vector<int>& solution);
public:

	CIndividual(CLFLnetEvaluator& cEvaluator) : cEvaluator(cEvaluator){
		randomFill(solution);
		fitness = cEvaluator.dEvaluate(&solution);
	}

	std::vector<int>* getSolution();

	double getFitness();

	int mutate(int number, int n, double mutProb);


	//cross();
};

