#ifndef SEARCH_SCORER_HPP
#define SEARCH_SCORER_HPP

#include "Utilities/Method_scorer.hpp"

class Search_scorer : public Method_scorer
{
    private:
    typedef std::vector<std::string> Metric_names;
    typedef std::vector<double> Metric_scores;

    public:
    Search_scorer(std::vector<std::string> problem_names) : Method_scorer(problem_names) { }

    void add_metric(Metric_names names, Metric_scores scores);

    private:
    Metric_names m_metric_names;
    Metric_scores m_metric_scores;
};

#endif // SEARCH_SCORER_HPP