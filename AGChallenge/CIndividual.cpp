#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include <cstdlib> 
#include <exception>



std::pair<CIndividual*, CIndividual*> CIndividual::cross(CIndividual* parent2, double crossProb)
{
	//draw a crossRand < crossProb and cross

	//CIndividual* parent1 = this;

	std::vector<int> v1;
	std::vector<int> v2;

	//if a crossover is drawn, crossPlace will receive a number of place to cross,
	//otherwise i > crossPlace will always return false
	int crossPlace = this->getSolution()->size();
	if (dRand() < crossProb)
		crossPlace = lRand(this->getSolution()->size() - 1);

	/* slightly optimized but cross place starts 1 place earlier
	for (size_t i = 0; i < crossPlace; i++)
	{
		v1.push_back(this->getSolution()->at(i));
		v2.push_back(parent2->getSolution()->at(i));
	}
	for (int i = crossPlace; i < this->getSolution()->size(); i++)
	{
		v1.push_back(parent2->getSolution()->at(i));
		v2.push_back(this->getSolution()->at(i));
	}/**/

	///*
	for (size_t i = 0; i < this->getSolution()->size(); i++)
	{
		if (i > crossPlace) {
			v1.push_back(parent2->getSolution()->at(i));
			v2.push_back(this->getSolution()->at(i));
		}
		else
		{
			v1.push_back(this->getSolution()->at(i));
			v2.push_back(parent2->getSolution()->at(i));
		}
	}/**/

	std::pair<CIndividual*, CIndividual*> pair(new CIndividual(cEvaluator, v1), new CIndividual(cEvaluator, v2));

	return pair;
}

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
