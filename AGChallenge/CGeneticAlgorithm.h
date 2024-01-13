#pragma once
#include "CIndividual.h"
#include "Evaluator.h"
#include <vector>


class CGeneticAlgorithm
{
private:
	int popSize;
	double crossProb;
	double mutProb;
	CLFLnetEvaluator cEvaluator;
	std::vector<CIndividual*> population;
public:

	CGeneticAlgorithm(CLFLnetEvaluator& cEvaluator, int popSize, double crossProb, double mutProb) : popSize(popSize), crossProb(crossProb), mutProb(mutProb), cEvaluator(cEvaluator) {
		for (size_t i = 0; i < popSize; i++)
		{
			population.push_back(&CIndividual(cEvaluator)); 
		}
	}

	CIndividual* getBestSolution();

	void crossPopulation();
};

