/*  Copyright 2017 George Le

*/
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <vector> // std::vector

#include "ExpectedData/expected_data.hpp"
#include "Utilities/Method_scorer.hpp"

class GeneticAlgorithmBool
{
    public:

    // 
    static GeneticAlgorithmBool* get_instance_ptr(std::string scores_file, std::string solutions_file, unsigned int number_of_traits, 
                                                unsigned int size_of_initial_population, unsigned int number_of_generations, unsigned int mutation_rate) {
        static GeneticAlgorithmBool* instance = new GeneticAlgorithmBool(scores_file, 
                                                                        solutions_file, 
                                                                        number_of_traits, 
                                                                        size_of_initial_population, 
                                                                        number_of_generations, 
                                                                        mutation_rate);
        return instance;
    }

    static std::shared_ptr<GeneticAlgorithmBool> get_instance(std::string scores_file, std::string solutions_file, unsigned int number_of_traits, 
                                                            unsigned int size_of_initial_population, unsigned int number_of_generations, unsigned int mutation_rate) {
        static std::shared_ptr<GeneticAlgorithmBool> instance(new GeneticAlgorithmBool(scores_file, 
                                                                                    solutions_file, 
                                                                                    number_of_traits, 
                                                                                    size_of_initial_population, 
                                                                                    number_of_generations, 
                                                                                    mutation_rate));
        return instance;
    }
    /*----------------------------------------------------------------
        User calls this function which will return an ExpectedData 
        class that the genetic algorithm will generate, storing a 
    ----------------------------------------------------------------*/
    ExpectedData generate_expected_data();

    ~GeneticAlgorithmBool();

    private:
    // The constructor of the genetic algorithm is private because the class
    // is a singleton.
    GeneticAlgorithmBool(std::string scores_file, std::string solutions_file, unsigned int number_of_traits, 
                            unsigned int size_of_initial_population, unsigned int number_of_generations, unsigned int mutation_rate)
        : m_scores(scores_file, solutions_file), m_number_of_traits(number_of_traits), m_size_of_population(size_of_initial_population), 
            m_number_of_generations(number_of_generations), m_current_generation(0), m_mutation_rate(mutation_rate) { }

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
    void fitness_function(int problem_number);

    std::vector<bool> last_fitness_function(std::vector<std::vector<bool>>& last_generation, int problem_number);
    
    /*-----------------------------------------------------------------
        Performs two point crossover on the parent organism strings.
    -----------------------------------------------------------------*/
    void crossover();

    /*--------------------------------------------------------------------
        Performs a bit string mutation on the child of the new generation.
    --------------------------------------------------------------------*/
    void mutation(std::vector<bool>& child);

    // this holds all the generations of the genetic algorithm
    std::map<int, std::vector<std::vector<bool>>> m_generations;
    // temporarily holds the fittest population for crossover
    std::vector<std::vector<bool>> m_fittest_population;

    Method_scorer m_scores;

    // useful variables for the genetic algorithm during runtime

    // number of traits that each individual will have
    unsigned int m_number_of_traits;
    // population size
    unsigned int m_size_of_population;
    // number of generations
    unsigned int m_number_of_generations;
    // percantage survival rate (i.e. a value of 50 will be fifty percent survival rate)
    unsigned int m_survival_rate;
    // percentage mutation rate ()
    unsigned int m_mutation_rate;

    // counter value
    unsigned int m_current_generation;
};

#endif // GENETIC_ALGORITHM_HPP