#include "CGeneticAlgorithm.h"

CIndividual* CGeneticAlgorithm::getBestSolution()
{
	double bestFitness = DBL_MIN;
	CIndividual* best = nullptr;
	for (size_t i = 0; i < popSize; i++)
	{
		double currFitness = population.at(i)->getFitness();
		if (bestFitness < currFitness)
		{
			bestFitness = currFitness;
			best = population.at(i);
		}
	}

    return best;
}

void CGeneticAlgorithm::crossPopulation()
{
	//find 2 parents and choose best 
	CIndividual* parent1_1 = population.at(lRand(population.size()));
	CIndividual* parent1_2 = population.at(lRand(population.size()));
	while (parent1_1 == parent1_2)
		parent1_2 = population.at(lRand(population.size())); //zeby nie bylo dwoch takich samych rodzicow

	CIndividual* parent1;

	if (parent1_1->getFitness() > parent1_2->getFitness())
		parent1 = parent1_1;
	else
		parent1 = parent1_2;

	//find 2 parents and choose best,
	CIndividual* parent2_1 = population.at(lRand(population.size()));
	CIndividual* parent2_2 = population.at(lRand(population.size()));
	while (parent2_1 == parent2_2)
		parent2_2 = population.at(lRand(population.size())); //zeby nie bylo dwoch takich samych rodzicow

	CIndividual* parent2;

	// if first already choosed, choose second
	if (parent1 == parent2_1)
		parent2 = parent2_2;
	else if (parent1 == parent2_2)
		parent2 = parent2_1;
	else //if not, choose best
	{
		if (parent2_1->getFitness() > parent2_2->getFitness())
			parent2 = parent2_1;
		else
			parent2 = parent2_2;
	}


	//losujemy krzyzowanie rand < crossProb


	//
}
