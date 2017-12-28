#ifndef GRAPH_EDGE_HPP
#define GRAPH_EDGE_HPP

#include <ostream>
#include <fstream>

class Graph_edge
{
    public:
    Graph_edge(int from, int to, double cost) : m_from(from), m_to(to), m_cost(cost) { }

    Graph_edge(int from, int to) : m_from(from), m_to(to), m_cost(1.0) { }

    Graph_edge() : m_from(-1), m_to(-1), m_cost(1.0) { }

    Graph_edge(std::ifstream& stream)
    {
        char buffer[50];
        stream >> buffer >> m_from >> buffer >> m_to >> buffer >> m_cost;
    }

    virtual ~Graph_edge() { }

    int get_from() const { return m_from; }
    int get_to() const { return m_to; }
    double get_cost() const { return m_cost; }

    void set_from(int new_index) { m_from = new_index; }
    void set_to(int new_index) { m_to = new_index; }
    void set_costs(int new_index) { m_cost = new_index; }

    bool operator==(const Graph_edge& rhs)
    {
        return (rhs.m_from == this->m_from) && 
                (rhs.m_to == this->m_to) && 
                (rhs.m_cost == this->m_cost);
    }

    bool operator!=(const Graph_edge& rhs)
    {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& output, const Graph_edge& edge)
    {
        output << "From: " << edge.m_from << " To: " << edge.m_to;
        output << " Cost: " << edge.m_cost << "\n";

        return output;
    }

    protected:
    int layer_from; // stores which layer of the graph the source node is in
    int layer_to; // stores which layer of the graph the destination node is in

    int m_from; // stores the index of the from node in the layer
    int m_to; // stores the index of the to node in the layer

    double m_cost; // stores the cost of traversing this edge
};

#endif // GRAPH_EDGE_HPP