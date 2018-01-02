#ifndef GRAPH_EDGE_HPP
#define GRAPH_EDGE_HPP

#include <ostream>

struct Edge_layer_pair
{
    int from;
    int to;
};

struct Edge_index_pair
{
    int from;
    int to;
};

struct Edge_layer_index_pair
{
    Edge_layer_pair layer;
    Edge_index_pair index;
};

class Graph_edge
{
    public:
    Graph_edge(Edge_layer_index_pair from_and_to, double cost) 
        : m_layer_from(from_and_to.layer.from), m_layer_to(from_and_to.layer.to),
        m_from(from_and_to.index.from), m_to(from_and_to.index.to), m_cost(cost) { }

    Graph_edge(int from, int to, double cost) : m_from(from), m_to(to), m_cost(cost) { }

    Graph_edge(int from, int to) : m_from(from), m_to(to) { }

    Graph_edge() { }

    virtual ~Graph_edge() { }

    // accessor functions
    int get_layer_from() const { return m_layer_from; }
    int get_layer_to() const { return m_layer_to; }
    int get_from() const { return m_from; }
    int get_to() const { return m_to; }
    double get_cost() const { return m_cost; }

    // mutator functions
    void set_layer_from(int new_layer_from) { m_layer_from = new_layer_from; }
    void set_layer_to(int new_layer_to) { m_layer_to = new_layer_to; }
    void set_from(int new_from) { m_from = new_from; }
    void set_to(int new_to) { m_to = new_to; }
    void set_costs(int new_cost) { m_cost = new_cost; }

    bool operator==(const Graph_edge& rhs)
    {
        return (rhs.m_layer_from == this->m_layer_from) &&
                (rhs.m_layer_to == this->m_layer_to) &&
                (rhs.m_from == this->m_from) && 
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
    int m_layer_from = -1; // stores which layer of the graph the source node is in
    int m_layer_to = -1; // stores which layer of the graph the destination node is in

    int m_from = -1; // stores the index of the from node in the layer
    int m_to = -1; // stores the index of the to node in the layer

    double m_cost = -1; // stores the cost of traversing this edge
};

#endif // GRAPH_EDGE_HPP