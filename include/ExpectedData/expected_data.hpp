/*  Copyright 2017 George Le

*/
#ifndef EXPECTED_DATA_HPP
#define EXPECTED_DATA_HPP

#include <vector> // std::vector

template<class ProblemType>
class ExpectedData
{
    typedef std::vector<ProblemType> ProblemArray;

    public:
    ExpectedData() : m_number_of_problems(0) { }
    ExpectedData(ProblemArray problems) 
        : m_problems(problems), m_number_of_problems(problems.size()) { }

    /*---------------------------------------------------------------
        Adds a problem of a generic problem type to the ExpectedData
        class's array of problems
    ---------------------------------------------------------------*/
    void add_problem(ProblemType problem_name) 
    { 
        m_problems.push_back(problem_name); 
        ++m_number_of_problems;
    }

    /*-------------------------------------------------------------
        Clears the current problems stored in the ExpectedData
        class and adds new ones.
    -------------------------------------------------------------*/
    void add_all_problems(std::vector<ProblemType> problem_names) 
    {
        m_problems.clear();
        m_problems = problem_names;
        m_number_of_problems = problem_names.size();
    }

    // accessor functions

    // returns to the user 
    ProblemType get_specific_name(int index) const 
    { 
        if(index < m_problems.size())
        {
            return m_problems.at(index); 
        }
    }

    // returns to the user all the problems in this expected data class
    // as a vector of a generic problem type
    ProblemArray get_problem_names() const { return m_problems; }

    /*----------------------------------------------------------------------- 
        comparison operator between this expected data class and another one
    -----------------------------------------------------------------------*/
    friend bool operator==(const ExpectedData& first, const ExpectedData& second)
    {
        bool result = false;
        if(first.m_number_of_problems == second->m_number_of_problems)
        {
            bool mismatch_found = false;
            for(unsigned int i = 0; i < first.m_number_of_problems.size(); ++i)
            {
                if(first.m_problems.at(i) != second->m_problems.at(i))
                {
                    mismatch_found = true;
                }
            }
            if(!mismatch_found)
            {   
                result = true;
            }
        }
        return result;
    }

    private:
    // holds the problems of the type that the user will specify when
    // creating the ExpectedData class
    ProblemArray m_problems;
    
    unsigned int m_number_of_problems;
};

#endif // EXPECTED_DATA_HPP