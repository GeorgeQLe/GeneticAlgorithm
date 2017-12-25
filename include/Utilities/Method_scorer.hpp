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
    Method_scorer(std::string score_file, std::string solution_file) 
    {
        std::cout << "\nGathering scores\n";
        read_scores_file(m_scores, m_methods, m_problem_names, score_file);
        std::cout << "\nGathering solutions\n";
        if(m_methods.size() >= 1)
        {
            read_solution(solution_file, m_solutions, m_problem_names.size(), m_methods.at(0).size());
        }
        else
        {
            std::cout << "No scores provided!\n";
        }
    }

    void add_scores(const std::vector<Score_vector>& scores) { m_scores = scores; }
    void add_methods(const std::vector<Method_vector>& methods) { m_methods = methods; }
    void add_solutions(const std::vector<Solution_vector>& solutions) { m_solutions = solutions; }

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
};

#endif // METHOD_SCORER_HPP