#pragma once
#include <vector>
#include <random>
#include "Evaluator.h"

class CIndividual
{
private:
	std::vector<int> solution;
	CLFLnetEvaluator &cEvaluator;
	double fitness;
	bool fitEvaluated;

	void randomFill(std::vector<int>& solution);
public:

	CIndividual(CLFLnetEvaluator& cEvaluator) : cEvaluator(cEvaluator), fitEvaluated(false) , fitness(0.0){
		randomFill(solution);
	}

	CIndividual(CLFLnetEvaluator& cEvaluator, std::vector<int> &solution) : cEvaluator(cEvaluator) , solution(solution), fitEvaluated(false), fitness(0.0) {}

	~CIndividual() {
		solution.clear();
	}

	std::pair<CIndividual*, CIndividual*> cross(CIndividual* parent2, double crossProb);

	std::vector<int>* getSolution();

	double getFitness();

	double evaluateFitness();

	void mutate(double mutProb);

};

