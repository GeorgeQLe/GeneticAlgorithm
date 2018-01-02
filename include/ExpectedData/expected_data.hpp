/*  Copyright 2017 George Le

*/
#ifndef GA_EXPECTED_DATA_HPP
#define GA_EXPECTED_DATA_HPP

#include <iostream> // std::ostream
#include <vector> // std::vector

class GA_expected_data
{
    public:
    GA_expected_data() { }
    GA_expected_data(std::vector<std::string> problems, std::vector<std::vector<std::string>> problem_solutions, 
                std::vector<std::vector<std::string>> problem_labels) 
    : m_problems(problems), m_problem_solutions(problem_solutions), m_problem_labels(problem_labels), m_number_of_problems(problems.size()) { }

    // accessor functions

    // returns to the user 
    std::string get_specific_name(unsigned int index) const 
    { 
        if(index < m_problems.size())
        {
            return m_problems.at(index); 
        }
    }

    // returns to the user all the problems in this expected data class
    // as a vector of a generic problem type
    std::vector<std::string> get_problem_names() const { return m_problems; }

    /*----------------------------------------------------------------------- 
        comparison operator between this expected data class and another one
    -----------------------------------------------------------------------*/
    friend bool operator==(const GA_expected_data& first, const GA_expected_data& second)
    {
        bool result = false;
        // checks if the two data sets have the same amount of problems in them
        if(first.m_number_of_problems == second.m_number_of_problems)
        {
            bool mismatch_found = false;
            // go through all the problem names if there are differences then
            // report a mismatch and break out of the loop
            for(unsigned int i = 0; i < first.m_number_of_problems; ++i)
            {
                if(first.m_problems.at(i) != second.m_problems.at(i))
                {
                    mismatch_found = true;
                    break;
                }
            }
            // if a mismatch wasn't found then set result equals to true
            if(!mismatch_found)
            {   
                result = true;
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& output, const GA_expected_data& data)
    {
        output << "Hello, the genetic algorithm has completed. Let's review the results of this algorithm\n";
        for(unsigned int i = 0; i < data.m_number_of_problems; ++i)
        {
            output << "For problem " << i + 1 << ", the best ";
            if(data.m_problem_labels.at(i).size() > 1)
            {
                output << "solutions to solve it are:\n\t";
                // increment through all of the problem labels
                for(auto e : data.m_problem_labels.at(i))
                {
                    output << e << "\n\t";
                }
            }
            else if(data.m_problem_labels.at(i).size() == 1)
            {
                output << "solution to solve it is:\n\t" << data.m_problem_labels.at(i).at(0) << "\n";
            }
            output << "\n";

            if(data.m_problem_solutions.at(i).size() > 1)
            {
                output << "The solutions to this problem are:\n";
                for(unsigned int j = 0; j < data.m_problem_solutions.at(i).size(); ++j)
                {
                    output << "\t" << data.m_problem_labels.at(i).at(j) << "\n";
                    output << data.m_problem_solutions.at(i).at(j) << "\n\n";
                }
            }
            else if(data.m_problem_solutions.at(i).size() == 1)
            {
                output << "The solution to this problem is:\n";
                output << "\t" << data.m_problem_labels.at(i).at(0) << "\n";
                output << data.m_problem_solutions.at(i).at(0) << "\n\n";
            }
        }
        
        return output;
    }

    void operator=(const GA_expected_data& rhs)
    {
        this->m_problems = rhs.m_problems;
        this->m_problem_solutions = rhs.m_problem_solutions;
        this->m_problem_labels = rhs.m_problem_labels;
        this->m_number_of_problems = rhs.m_number_of_problems;
    }

    private:
    std::vector<std::string> m_problems;
    std::vector<std::vector<std::string>> m_problem_solutions;
    std::vector<std::vector<std::string>> m_problem_labels;
    
    unsigned int m_number_of_problems = 0;
};

#endif // EXPECTED_DATA_HPP