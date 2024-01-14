#include "CGeneticAlgorithm.h"

CIndividual* CGeneticAlgorithm::getBestSolution()
{
	double bestFitness = DBL_MIN;
	CIndividual* best = nullptr;
	for (size_t i = 0; i < popSize; i++)
	{
		double currFitness = population.at(i)->evaluateFitness();
		if (bestFitness < currFitness)
		{
			bestFitness = currFitness;
			best = population.at(i);
		}
	}
	std::cout << best->getFitness() << "\n";

    return best;
}

void CGeneticAlgorithm::vRunIteration()
{
	crossPopulation();
	mutatePopulation();
	//std::cout << getBestSolution()->getFitness() << "\n";
}

void CGeneticAlgorithm::crossPopulation()
{
	std::vector<CIndividual*> newPopulation;

	while (newPopulation.size() < popSize)
	{

		//find 2 parents and choose best 
		CIndividual* parent1_1 = population.at(lRand(population.size()));
		CIndividual* parent1_2 = population.at(lRand(population.size()));
		while (parent1_1 == parent1_2)
			parent1_2 = population.at(lRand(population.size())); //no two same parents

		CIndividual* parent1;

		if (parent1_1->evaluateFitness() > parent1_2->evaluateFitness())
			parent1 = parent1_1;
		else
			parent1 = parent1_2;



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
			if (parent2_1->evaluateFitness() > parent2_2->evaluateFitness())
				parent2 = parent2_1;
			else
				parent2 = parent2_2;
		}


		//draw a crossRand < crossProb and cross

		std::vector<int> v1;
		std::vector<int> v2;

		//if a crossover is drawn, crossPlace will receive a number of place to cross,
		//otherwise i > crossPlace will always return false
		int crossPlace = parent1->getSolution()->size();
		if (dRand() < crossProb)
			crossPlace = lRand(parent1->getSolution()->size() - 1);

		for (size_t i = 0; i < parent1->getSolution()->size(); i++)
		{
			if (i > crossPlace) {
				v1.push_back(parent2->getSolution()->at(i));
				v2.push_back(parent1->getSolution()->at(i));
			}
			else
			{
				v1.push_back(parent1->getSolution()->at(i));
				v2.push_back(parent2->getSolution()->at(i));
			}
		}

		newPopulation.push_back(&CIndividual(cEvaluator, v1));
		newPopulation.push_back(&CIndividual(cEvaluator, v2));

	}

	//set new population
	population.clear();
	population = newPopulation;
}

void CGeneticAlgorithm::mutatePopulation()
{
	for (size_t i = 0; i < population.size(); i++)
		population.at(i)->mutate(mutProb);
}
