#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP

#include <ostream>

static int OVERALL_INDEX = 1;

struct Node_location
{
    Node_location(int new_layer, int new_index) : layer(new_layer), index(new_index) {} 

    const int layer;
    const int index;
};

class Graph_node
{
    public:
    Graph_node(Node_location location) : m_layer(location.layer), m_layer_index(location.index) { m_index = OVERALL_INDEX; OVERALL_INDEX++; }

    virtual ~Graph_node() { }

    // accessor function
    int layer_index() const { return m_layer_index; }
    int index() const { return m_index; }

    // mutator function
    void set_index(int index) { m_layer_index = index; }

    friend std::ostream& operator<<(std::ostream& output, const Graph_node& n)
    {
        output << "Index: " << n.m_index << ", Layer: " << n.m_layer << "\n";
        return output;
    }

    private:
    // every node has a record of the layer it is a part of
    int m_layer;
    // every node has a record of its index in its layer
    int m_layer_index;
    // every node has an overall index of where it is in the graph
    int m_index;
};

#endif // GRAPH_NODE_HPP