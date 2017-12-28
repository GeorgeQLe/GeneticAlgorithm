/*  Copyright 2017  George Le

    This class will attempt to score solution methods for a set of problems based on a series of
    user specified methods. 
*/
#ifndef METHOD_SCORER_HPP
#define METHOD_SCORER_HPP

#include <iostream>
#include <list>
#include <vector>

#include "read_file.hpp"

class Method_scorer
{
    private:
    typedef std::vector<double> Score_vector;
    typedef std::vector<std::string> Method_vector;
    typedef std::vector<std::string> Solution_vector;

    public:
    Method_scorer(std::vector<std::string> problem_names) : m_number_of_problems(problem_names.size())
    {
        m_problem_names = problem_names;
    }
    
    void add_results(std::string method, std::string solution);

    std::vector<std::vector<double>> get_scores() const { return m_scores; }
    std::vector<std::vector<std::string>> get_score_labels() const { return m_methods; }
    std::vector<Solution_vector> get_solutions() const { return m_solutions; }

    std::vector<std::string> get_problem_names() const { return m_problem_names; }

    void operator=(const Method_scorer& rhs)
    {
        this->m_scores = rhs.m_scores;
        this->m_methods = rhs.m_methods;
        this->m_solutions = rhs.m_solutions;
    }

    private:
    std::vector<Score_vector> m_scores;
    std::vector<Method_vector> m_methods;
    std::vector<Solution_vector> m_solutions;

    std::vector<std::string> m_problem_names;
    unsigned int m_number_of_problems;
};

#endif // METHOD_SCORER_HPP