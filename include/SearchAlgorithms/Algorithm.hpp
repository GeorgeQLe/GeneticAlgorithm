#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

class Algorithm
{
    public:
    Algorithm() : mMax_Nodes_Expanded(0), mNodes_Explored(0), mFound_Solution(0) { }

    virtual void search();

    unsigned int get_max_node() const { return mMax_Nodes_Expanded; }
    unsigned int get_num_nodes_explored() const { return mNodes_Explored; }
    bool found_solution() const { return mFound_Solution; }

    private:
    unsigned int mMax_Nodes_Expanded;
    unsigned int mNodes_Explored;
    bool mFound_Solution;
};

#endif