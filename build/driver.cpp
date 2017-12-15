/*  Copyright 2017 George Le

    Test driver program for the ANN
*/
#include <iostream>
#include "GA/GeneticAlgorithmBool.hpp"

int main()
{
    std::cout << "Starting Genetic Algorithm\n";
    GeneticAlgorithmBool* instance = GeneticAlgorithmBool::get_instance_ptr(6, 10, 10);
    std::cout << "Genetic Algorithm start up complete\n\n";
    std::cout << "Creating data table\n";
    ExpectedData data;
    std::cout << "Data table ready\n\n";
    std::cout << "Adding problem\n";
    instance->add_problem("prob1.map");
    std::cout << "Added problem\n\n";
    std::cout << "Starting to gather data in the genetic algorithm\n";
    data = instance->generate_expected_data();
    std::cout << "Data gather complete\n\n";
    std::cout << data;
}