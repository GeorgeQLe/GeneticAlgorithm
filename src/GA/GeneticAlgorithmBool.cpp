#include <algorithm> // std::swap_ranges
#include <iostream> // std::cout 
#include <random> // std::mt19937, std::random_device, std::uniform_int_distribution

#include "GA/GeneticAlgorithmBool.hpp"

int return_rand_index(int smallest_index, int greatest_index)
{
    int random_number = -1;
	
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(smallest_index, greatest_index);
	random_number = dist(gen); 

    return random_number;
}

bool return_random_bool()
{
    int random_number = return_rand_index(0, 1);

    if(random_number)
    {
        return true;
    }
    return false;
}

bool percentage_chance(unsigned int percentage_chance)
{
    unsigned int num = return_rand_index(1, 100);

    if(num <= percentage_chance)
    {
        return true;
    }
    return false;
}

int partition(std::vector<double>& list, unsigned int left, unsigned int right)
{
    // set partition equal to the right
    int f_partition = left;
    // create a temporary reference to the element in the vector at the left
    double f_temp = list.at(left);
    
    // compare from the left hand element to the right hand element, the right
    // hand element being the partition
    for(unsigned int i = left + 1; i < right; ++i)
    {
        // generic function in condition for what you want to compare in the vectors
        // if the element in the vector at the left+1 position is (comp definition)
        // to the element at the left position then execute within this
        // (assume less than for smallest to largest, greater than for largest to smallest)
        if(list.at(i) <= f_temp)
        {
            // increment the partition
            f_partition++;
            // swap the elements at the partition with the element at the 
            // i'th position
            std::swap(list.at(f_partition), list.at(i));
        }
    }
    // swap the partition with the left hand side
    std::swap(list.at(f_partition), list.at(left));
    return f_partition;
}

void quicksort(std::vector<double>& list, unsigned int left, unsigned int right)
{
    int f_partition;
    
    // ensure that left is less than right as it should
    if(left < right)
    {
        // get the partition for the quick sort and sort from the left to the right
        f_partition = partition(list, left, right);
        // recursively call quicksort with the new partition being the right
        quicksort(list , left, f_partition);  
        // recursively call quicksort with the new partition incremented by 1 being
        // the left hand side
        quicksort(list, f_partition+1, right);
    }
}

struct Swap_points
{
    Swap_points(unsigned int new_start_point, unsigned int new_end_point) : start_point(new_start_point), end_point(new_end_point) { }

    unsigned int start_point;
    unsigned int end_point;
};

void swap_range(std::vector<bool>& child1, std::vector<bool>& child2, Swap_points start_and_end)
{
    if(child1.size() == child2.size())
    {
        for(unsigned int i = start_and_end.start_point; i < start_and_end.end_point; ++i)
        {
            std::swap(child1.at(i), child2.at(i));
        }
    }
    else
    {
        std::cout << "Children dont have the same amount of traits\n";
    }
}

Individual GeneticAlgorithmBool::generate_expected_data()
{
    Individual fittest_individual;
    Population fittest_individuals;
    // Runs one genetic algorithm for each of the problems
    generate_random_population();
    for (unsigned int index_generation = 1; index_generation < m_number_of_generations; ++index_generation)
    {
        fitness_function();
        crossover();
        m_generations.first = m_generations.second;
    }
    fittest_individuals.push_back(last_fitness_function(m_generations.first));
    return fittest_individual;
}

void GeneticAlgorithmBool::generate_random_population()
{
    // start the genetic algorithm and incremement the current generation
    ++m_current_generation;
    for(unsigned int index = 0; index < m_size_of_population; ++index)
    {
        std::vector<bool> temp_individual;
        for(unsigned int j = 0; j < m_number_of_traits; ++j)
        {
            /*------------------------------------------------------
                Creates a member of the population with n number
                of traits; each trait is generated randomly.
             Ex: 
              For a member with four traits, it could be a vector
              containing:
                  { true, false, true, false }
              This individual would have the first and third trait
              and not the second and fourth trait. The use of a map
              allows for each individual of a generation to be mapped
              to an integer value for easy lookup. 
            -------------------------------------------------------*/
            temp_individual.push_back(return_random_bool());
        }
        m_generations.first.push_back(temp_individual);
    }
}
    
void GeneticAlgorithmBool::fitness_function()
{
    // initializes a vector of doubles with 0.0 for each of the
    // member of the population
    Scores average_scores(m_size_of_population, 0.0);
    // counter for the number of active traits of each individual
    // refreshed after each average calculations
    double active_traits;

    // calculates the averages for each of the individuals of the generations
    for(unsigned int index_population = 0; index_population < m_size_of_population; ++index_population)
    {
        active_traits = 0.0;
        
        // adding up the total score of the individual
        for(unsigned int index_traits = 0; index_traits < m_number_of_traits; ++index_traits)
        {
            if(m_generations.first.at(index_population).at(index_traits))
            {
                average_scores.at(index_population) += m_method_scores.at(index_traits);
                ++active_traits;
            }
        }
        if(active_traits != 0.0)
        {
            average_scores.at(index_population) /= active_traits;
        }
    }

    // sorts the average scores from greatest to least
    quicksort(average_scores, 0, average_scores.size());

    // calculates the cutoff score for individuals
    double radix = average_scores.at(average_scores.size() / percentage_chance(m_survival_rate));
    // clears the fittest population if it has been used before
    if(m_fittest_population.size() > 0)
    {
        m_fittest_population.clear();
    }
    // for each of the scores
    for(unsigned int index = 0; index < average_scores.size(); ++index)
    {
        // if the scores is greater than or equal to the cuttoff score
        // then add it to the fittest population for crossover
        if(average_scores.at(index) >= radix)
        {
            m_fittest_population.push_back(m_generations.first.at(index));
        }
    }
}

Individual GeneticAlgorithmBool::last_fitness_function(const Population& last_generation)
{
    // initializes a vector of doubles with 0.0 for each of the
    // member of the population
    Scores average_scores(m_size_of_population, 0.0);
    // counter for the number of active traits of each individual
    // refreshed after each average calculations
    double active_traits;

    // gather the individual's averages
    for(unsigned int index = 0; index < m_size_of_population; ++index)
    {
        active_traits = 0.0;
        // adding up the total score of the individual
        for(unsigned int i = 0; i < m_number_of_traits; ++i)
        {
            if(m_generations.first.at(index).at(i))
            {
                average_scores.at(index) += m_method_scores.at(i);
                ++active_traits;
            }   
        }
        if(active_traits != 0.0)
        {
            average_scores.at(index) /= active_traits;
        }
    }

    // then find the fittest individual
    unsigned int highest_score = 0, highest_index = 0;
    for(unsigned int i = 0; i < average_scores.size(); ++i)
    {
        if(average_scores.at(i) >= highest_score)
        {
            highest_score = average_scores.at(i);
            highest_index = i;
        }
    }
    // then return that fittest individual
    return last_generation.at(highest_index);
}

void GeneticAlgorithmBool::crossover()
{
    Individual child1, child2; // std::vector<bool>
    int index_parent1 = -1, index_parent2 = -1;

    // clear the next generation if it has been used
    if(m_generations.second.size() > 0)
    {
        m_generations.second.clear();
    }

    // push all the fittest population into the next generation
    for(unsigned int i = 0; i < m_fittest_population.size(); ++i)
    {
        m_generations.second.push_back(m_fittest_population.at(i));
    }

    // select two at random of the fittest population to reproduce
    // a new individual of the next generation and there is a coin
    // flip to see if the individual has a mutation. Add the new 
    // individual to the next generation.
    while(m_generations.second.size() < m_size_of_population)
    {
        // generates where the start and the end points of the uniform crossover
        unsigned int index_start_flip = return_rand_index(0, m_number_of_traits - 2);
        unsigned int index_end_flip = return_rand_index(index_start_flip + 1, m_number_of_traits - 1);
        
        // randomly selects two parents
        index_parent1 = return_rand_index(0, m_fittest_population.size() - 1);
        index_parent2 = return_rand_index(0, m_fittest_population.size() - 1);
        
        // creates two children from the two parents
        child1 = m_fittest_population.at(index_parent1);
        child2 = m_fittest_population.at(index_parent2);

        // applies the crossover to the children at the randomly generated start and end points
        swap_range(child1, child2, { index_start_flip, index_end_flip });

        // coin flip to see if the child recieves a mutation
        if(percentage_chance(m_mutation_rate))
        {
            bit_string_mutation(child1);
        }
        if(percentage_chance(m_mutation_rate))
        {
            bit_string_mutation(child2);
        }
        // adds the child to the new generation
        m_generations.second.push_back(child1);
        // checks if the child can join the new generation or if its addition will
        // overpopulate the next generation
        if(m_generations.second.size() < m_size_of_population)
        {
            // if there is still space in the next generation, the child is added
            m_generations.second.push_back(child2);
        }
    }
    // move onto the next generation
    ++m_current_generation;
}

void GeneticAlgorithmBool::bit_string_mutation(Individual& child)
{   
    int random_index = return_rand_index(0, child.size() - 1);
    
    // selects a random trait of the child individual and flips the bit
    if(child.at(random_index))
    {
        child.at(random_index) = false;
    }
    else
    {
        child.at(random_index) = true;
    }
}