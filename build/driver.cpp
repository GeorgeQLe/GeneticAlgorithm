/*  Copyright 2017 George Le

    Test driver program for the ANN
*/
#include <iostream>
#include "GA/GeneticAlgorithmBool.hpp"

int main()
{
    std::cout << "Starting Genetic Algorithm\n";
    GeneticAlgorithmBool* instance = GeneticAlgorithmBool::get_instance_ptr("scores.txt", "solutions.txt", 4, 50, 100, 100);
    std::cout << "Genetic Algorithm start up complete\n\n";

    std::cout << "Creating data table\n";
    ExpectedData data;
    std::cout << "Data table ready\n\n";

    std::cout << "Starting to gather data in the genetic algorithm\n";
    data = instance->generate_expected_data();
    std::cout << "Data gather complete\n\n";

    std::cout << data;
    std::cout << "Finished program\n";
    
    return 0;
}