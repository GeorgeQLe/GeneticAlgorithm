#include <algorithm> // std::swap_ranges
#include <random> // std::mt19937, std::random_device, std::uniform_int_distribution

#include <iostream>

#include "GA/GeneticAlgorithmBool.hpp"

bool return_random_bool()
{
    int random_number = -1;
	
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(0, 1);
	random_number = dist(gen);

    if(random_number)
    {
        return true;
    }
    return false;
}

int return_rand_index(int smallest_index, int greatest_index)
{
    int random_number = -1;
	
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(smallest_index, greatest_index);
	random_number = dist(gen); 

    return random_number;
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

void swap_range(std::vector<bool>& child1, std::vector<bool>& child2, unsigned int start_point, unsigned int end_point)
{
    if(child1.size() == child2.size())
    {
        for(unsigned int i = start_point; i < end_point; ++i)
        {
            std::swap(child1.at(i), child2.at(i));
        }
    }
    else
    {
        std::cout << "Children dont have the same amount of traits\n";
    }
}

ExpectedData GeneticAlgorithmBool::generate_expected_data()
{
    std::vector<std::vector<bool>> fittest_individuals;
    std::vector<std::vector<std::string>> problem_solutions;
    std::vector<std::vector<std::string>> problem_labels;
    
    for (unsigned int index_problem = 0; index_problem < m_scores.get_problem_names().size(); ++index_problem)
    {
        // Runs one genetic algorithm for each of the problems
        generate_random_population();
        for (unsigned int index_generation = 1; index_generation < m_number_of_generations; ++index_generation)
        {
            fitness_function(index_problem);
            crossover();
        }
        fittest_individuals.push_back(last_fitness_function(m_generations.at(m_current_generation - 1), index_problem));
        std::vector<std::string> labels_for_specific_problem;
        std::vector<std::string> solution_for_specific_problem;
        for (unsigned int index_trait = 0; index_trait < fittest_individuals.at(index_problem).size(); ++index_trait)
        {
            if (fittest_individuals.at(index_problem).at(index_trait))
            {
                labels_for_specific_problem.push_back(m_scores.get_score_labels().at(index_problem).at(index_trait));
                solution_for_specific_problem.push_back(m_scores.get_solutions().at(index_problem).at(index_trait));
            }
        }
        problem_labels.push_back(labels_for_specific_problem);
        problem_solutions.push_back(solution_for_specific_problem);
    }
    ExpectedData data(m_scores.get_problem_names(), problem_solutions, problem_labels);
    return data;
}

void GeneticAlgorithmBool::generate_random_population()
{
    // start the genetic algorithm and incremement the current generation
    ++m_current_generation;
    for(unsigned int index = 0; index < m_size_of_population; ++index)
    {
        std::vector<bool> temp_individual;
        if(index == 0)
        {
            m_generations.emplace(m_current_generation, std::vector<std::vector<bool>>());
        }
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
        m_generations.at(m_current_generation).push_back(temp_individual);
    }
}
    
void GeneticAlgorithmBool::fitness_function(int problem_number)
{
    std::vector<double> average_scores(m_size_of_population, 0.0);
    double active_traits;
    for(unsigned int index = 0; index < m_size_of_population; ++index)
    {
        active_traits = 0.0;
        
        for(unsigned int i = 0; i < m_number_of_traits; ++i)
        {
            if(m_generations.at(m_current_generation).at(index).at(i))
            {
                average_scores.at(index) += m_scores.get_scores().at(problem_number).at(i);
                ++active_traits;
            }
        }
        if(active_traits != 0.0)
        {
            average_scores.at(index) /= active_traits;
        }
    }

    quicksort(average_scores, 0, average_scores.size());

    double radix = average_scores.at(average_scores.size() / 2);
    
    if(m_fittest_population.size() > 0)
    {
        m_fittest_population.clear();
    }

    for(unsigned int index = 0; index < average_scores.size(); ++index)
    {
        if(average_scores.at(index) >= radix)
        {
            m_fittest_population.push_back(m_generations.at(m_current_generation).at(index));
        }
    }
}

std::vector<bool> GeneticAlgorithmBool::last_fitness_function(std::vector<std::vector<bool>>& last_generation, int problem_number)
{
    std::vector<double> average_scores(m_size_of_population , 0.0);
    double active_traits;

    // gather the individual's averages
    for(unsigned int index = 0; index < m_size_of_population; ++index)
    {
        active_traits = 0.0;
        for(unsigned int i = 0; i < m_number_of_traits; ++i)
        {
            if(m_generations.at(m_current_generation).at(index).at(i))
            {
                average_scores.at(index) += m_scores.get_scores().at(problem_number).at(i);
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
    std::vector<bool> child1, child2;
    int index_parent1 = -1, index_parent2 = -1;

    // push all the fittest population into the next generation
    for(unsigned int i = 0; i < m_fittest_population.size(); ++i)
    {
        m_generations[m_current_generation + 1].push_back(m_fittest_population.at(i));
    }

    // select two at random of the fittest population to reproduce
    // a new individual of the next generation and there is a coin
    // flip to see if the individual has a mutation. Add the new 
    // individual to the next generation.
    while(m_generations.at(m_current_generation + 1).size() < m_size_of_population)
    {
        // generates where the start and the end points of the uniform crossover
        int index_start_flip = return_rand_index(0, m_number_of_traits - 2);
        int index_end_flip = return_rand_index(index_start_flip + 1, m_number_of_traits - 1);
        
        // randomly selects two parents
        index_parent1 = return_rand_index(0, m_fittest_population.size() - 1);
        index_parent2 = return_rand_index(0, m_fittest_population.size() - 1);
        
        // creates two children from the two parents
        child1 = m_fittest_population.at(index_parent1);
        child2 = m_fittest_population.at(index_parent2);

        // applies the crossover to the children at the randomly generated start and end points
        swap_range(child1, child2, index_start_flip, index_end_flip);

        // coin flip to see if the child recieves a mutation
        if(return_rand_index(1, m_mutation_rate) == 1)
        {
            mutation(child1);
        }
        if(return_rand_index(1, m_mutation_rate) == 1)
        {
            mutation(child2);
        }
        // adds the child to the new generation
        m_generations.at(m_current_generation + 1).push_back(child1);
        // checks if the child can join the new generation or if its addition will
        // overpopulate the next generation
        if(m_generations.at(m_current_generation + 1).size() < m_size_of_population)
        {
            // if there is still space in the next generation, the child is added
            m_generations.at(m_current_generation + 1).push_back(child2);
        }
    }
    // move onto the next generation
    ++m_current_generation;
}

void GeneticAlgorithmBool::mutation(std::vector<bool>& child)
{   
    int random_index = return_rand_index(0, child.size() - 1);
    
    if(child.at(random_index))
    {
        child.at(random_index) = false;
    }
    else
    {
        child.at(random_index) = true;
    }
}