#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include <cstdlib> 
#include <exception>

std::vector<int>* CIndividual::getSolution()
{
	return &solution;
}

double CIndividual::getFitness()
{
	if (fitEvaluated)
		return fitness;
	else
		throw std::runtime_error("Cannot get fitness before evaluation");
}

double CIndividual::evaluateFitness()
{
	fitness = cEvaluator.dEvaluate(&solution);
	fitEvaluated = true;
	return fitness;
}

void CIndividual::mutate(double mutProb)
{
	for (size_t i = 0; i < solution.size(); i++)
		if (dRand() < mutProb)
		{
			solution.at(i) = lRand(cEvaluator.iGetNumberOfValues(i));
		}
}

void CIndividual::randomFill(std::vector<int>& solution)
{
	solution.resize((size_t)cEvaluator.iGetNumberOfBits());

	for (int i = 0; i < solution.size(); i++)
	{
		solution.at(i) = lRand(cEvaluator.iGetNumberOfValues(i));
	}
}
