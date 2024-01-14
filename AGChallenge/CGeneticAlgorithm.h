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
	CLFLnetEvaluator &cEvaluator;
	std::vector<CIndividual*> population;
	CIndividual* best;

	void crossPopulation();

	void mutatePopulation();

	void evaluateFitnessForAll();
public:

	CGeneticAlgorithm(CLFLnetEvaluator& cEvaluator, int popSize, double crossProb, double mutProb) : popSize(popSize), crossProb(crossProb), mutProb(mutProb), cEvaluator(cEvaluator), best(nullptr) {
		for (size_t i = 0; i < popSize; i++)
			population.push_back(new CIndividual(cEvaluator));

		evaluateFitnessForAll();

		//find first best solution
		double bestFitness = DBL_MIN; 
		for (size_t i = 0; i < popSize; i++)
		{
			double currFitness = population.at(i)->getFitness();
			if (bestFitness < currFitness)
			{
				bestFitness = currFitness;
				best = population.at(i);
			}
		}
	}

	~CGeneticAlgorithm() {
		for (size_t i = 0; i < population.size(); i++)
		{
			delete population.at(i);
		}
		population.clear();
	}

	CIndividual* getBestSolution();

	void vRunIteration();
};

