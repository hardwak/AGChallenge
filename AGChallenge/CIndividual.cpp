#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include <cstdlib> 

std::vector<int>* CIndividual::getSolution()
{
	return &solution;
}

double CIndividual::getFitness()
{
	return fitness;
}

int CIndividual::mutate(int number, int n, double mutProb)
{
	if (mutProb )
	{

	}
	

	return 0;
}

void CIndividual::randomFill(std::vector<int>& solution)
{
	solution.resize((size_t)cEvaluator.iGetNumberOfBits());

	for (int i = 0; i < solution.size(); i++)
	{
		solution.at(i) = lRand(cEvaluator.iGetNumberOfValues(i));
	}
}
