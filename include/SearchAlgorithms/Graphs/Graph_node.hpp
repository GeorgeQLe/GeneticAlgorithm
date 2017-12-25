#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP

#include <ostream>
#include <fstream>

class Graph_node
{
    protected:
    // every node has an index. A valid index is >= 0
    int m_index;

    public:
    Graph_node() : m_index(-1) { }
    Graph_node(int index) : m_index(index) { }
    Graph_node(std::ifstream& stream) { 
        char buffer[50];
        stream >> buffer >> m_index;
    }

    virtual ~Graph_node() { }

    int index() const { return m_index; }
    void set_index(int index) { m_index = index; }

    friend std::ostream& operator<<(std::ostream& output, const Graph_node& n)
    {
        output << "Index: " << n.m_index << "\n";
        return output;
    }
};

#endif // GRAPH_NODE_HPP