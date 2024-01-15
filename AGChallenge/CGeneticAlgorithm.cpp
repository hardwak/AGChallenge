#include "CGeneticAlgorithm.h"

CIndividual* CGeneticAlgorithm::getBestSolution()
{
	double bestFitness = best->getFitness();
	CIndividual* newBest = nullptr;
	for (size_t i = 0; i < popSize; i++)
	{
		double currFitness = population.at(i)->getFitness();
		if (bestFitness < currFitness)
		{
			bestFitness = currFitness;
			newBest = population.at(i);
		}
	}

	if (newBest != nullptr)
	{
		delete best;
		best = newBest;
	}
	std::cout << best->getFitness() << "\n";

    return best;
}

void CGeneticAlgorithm::vRunIteration()
{
	crossPopulation();
	mutatePopulation();
	evaluateFitnessForAll();
	//std::cout << getBestSolution()->getFitness() << "\n";
}

void CGeneticAlgorithm::crossPopulation()
{
	std::vector<CIndividual*> newPopulation;

	while (newPopulation.size() < popSize)
	{
		//-----------------------------STEP 1--------------------------------------

		//find 2 parents and choose best 
		CIndividual* parent1_1 = population.at(lRand(population.size()));
		CIndividual* parent1_2 = population.at(lRand(population.size()));
		while (parent1_1 == parent1_2)
			parent1_2 = population.at(lRand(population.size())); //no two same parents

		CIndividual* parent1;

		if (parent1_1->getFitness() > parent1_2->getFitness())
			parent1 = parent1_1;
		else
			parent1 = parent1_2;



		//-----------------------------STEP 2--------------------------------------

		//find another 2 parents and choose best,
		CIndividual* parent2_1 = population.at(lRand(population.size()));
		CIndividual* parent2_2 = population.at(lRand(population.size()));
		while (parent2_1 == parent2_2)
			parent2_2 = population.at(lRand(population.size())); //no two same parents

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



		//-----------------------------STEP 3--------------------------------------
		
		//cross parent1 with parent2
		std::pair<CIndividual*, CIndividual*> pair(parent1->cross(parent2, crossProb));

		newPopulation.push_back(pair.first);
		newPopulation.push_back(pair.second);

	}



	//-----------------------------STEP 4--------------------------------------
	
	//set new population
	for (size_t i = 0; i < population.size(); i++)
	{
		if (population.at(i) != best)  // in case to not delete best saved solution
		{
			delete population.at(i);
		}
		
	}
	population.clear();
	population = newPopulation;
}

void CGeneticAlgorithm::mutatePopulation()
{
	for (size_t i = 0; i < population.size(); i++)
		population.at(i)->mutate(mutProb);
}

void CGeneticAlgorithm::evaluateFitnessForAll()
{
	for (size_t i = 0; i < population.size(); i++)
		population.at(i)->evaluateFitness();
}
