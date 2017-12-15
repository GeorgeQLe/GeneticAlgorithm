/*  Copyright 2017 George Le

*/
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <vector> // std::vector

#include "ExpectedData/expected_data.hpp"

class GeneticAlgorithmBool
{
    public:
    static GeneticAlgorithmBool* get_instance_ptr(unsigned int number_of_traits, unsigned int size_of_initial_population, unsigned int number_of_generations) {
        static GeneticAlgorithmBool* instance = new GeneticAlgorithmBool(number_of_traits, size_of_initial_population, number_of_generations);
        return instance;
    }

    static std::shared_ptr<GeneticAlgorithmBool> get_instance(unsigned int number_of_traits, unsigned int size_of_initial_population, unsigned int number_of_generations) {
        static std::shared_ptr<GeneticAlgorithmBool> instance(new GeneticAlgorithmBool(number_of_traits, size_of_initial_population, number_of_generations));
        return instance;
    }

    void add_problem(const std::string& filename) { m_problems.push_back(filename); }

    /*----------------------------------------------------------------
        User calls this function which will return the ExpectedData 
        that the genetic algorithm 
    ----------------------------------------------------------------*/
    ExpectedData<std::string> generate_expected_data();

    ~GeneticAlgorithmBool();

    private:
    // The constructor of the genetic algorithm is private because the class
    // is a singleton.
    GeneticAlgorithmBool(unsigned int number_of_traits, unsigned int size_of_initial_population, unsigned int number_of_generations)
        : m_number_of_traits(number_of_traits), m_size_of_population(size_of_initial_population), m_number_of_generations(number_of_generations), m_current_generation(0) { }

    /*-----------------------------------------------------------------
        This function generates pseudo-random sequences for each of the
        members of the population. Because this genetic algorithm uses
        boolean values to model the traits of the individuals of the
        population.
    -----------------------------------------------------------------*/
    void generate_random_population();
    
    /*-----------------------------------------------------------------
        This function determines which member of the population is the
        fittest member of the generation which will survive and 
        reproduce for the next generation. 
    -----------------------------------------------------------------*/
    void fitness_function(const ProblemScore& scores);

    std::vector<bool> last_fitness_function(const ProblemScore& scores, std::vector<std::vector<bool>>& last_generation);
    
    /*-----------------------------------------------------------------
        Performs two point crossover on the parent organism strings.
    -----------------------------------------------------------------*/
    void crossover();

    /*--------------------------------------------------------------------
        Performs a bit string mutation on the child of the new generation.
    --------------------------------------------------------------------*/
    void mutation(std::vector<bool>& child);

    std::map<int, std::vector<std::vector<bool>>> m_generations;

    std::vector<std::vector<bool>> m_fittest_population;

    std::vector<std::string> m_problems;

    unsigned int m_number_of_traits;
    unsigned int m_size_of_population;
    unsigned int m_number_of_generations;
    unsigned int m_current_generation;
};

#endif // GENETIC_ALGORITHM_HPP