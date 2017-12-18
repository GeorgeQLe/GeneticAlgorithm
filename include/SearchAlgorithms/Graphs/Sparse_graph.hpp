#ifndef SPARSE_GRAPH_HPP
#define SPARSE_GRAPH_HPP


#include <list>
#include <string>
#include <vector>

#include "Graph_nodes.hpp"
#include "include/Utilities/2D/Vector2D.hpp"
#include "include/Utilities/Utilities.hpp"

template<class Node_type, class Edge_type>
class Sparse_graph
{
    public:
    typedef std::vector<Node_type> NodeVector;
    typedef std::list<Edge_type> EdgeList;
    typedef std::vector<EdgeList> EdgeListVector;
    
    Sparse_graph(bool digraph) : m_directed(digraph), m_next_node_index(0) { }

    const Node_type get_node(int index) const;
    Node_type& get_node(int index);
    const Edge_type& get_edge(int from, int to) const;
    Edge_type& get_edge(int from, int to);

    // retrieves the next free node index
    int get_next_index() const { return m_next_node_index; }

    int add_node(Node_type node);

    void remove_node(int node);

    void add_edge(Edge_type edge);

    void remove_edge(int from, int to);

    void set_edge_cost(int from, int to, double cost);

    int num_nodes() const { return m_nodes.size(); }

    int num_active_nodes() const;

    int num_edges() const;

    bool is_direct() const { return m_directed; }

    bool is_empty() const { return m_nodes.empty(); }

    bool is_node_present(int index) const;

    bool is_edge_present(int from, int to) const;

    bool save(const char* filename) const;
    bool save(std::ofstream& stream) const;

    bool load(const char* filename);
    bool load(std::ifstream& stream);

    void clear();

    void remove_edges();

    private:
    // the nodes that constitute the graph
    NodeVector m_nodes;

    // a vector of adjacency edge lists (each node index keys
    // into the list of edges associated with that node)
    EdgeListVector m_edges;

    // is this graph a directed graph?
    bool m_directed;

    // the index of the next node to be added
    int m_next_node_index;
};

template<class Node_type, class Edge_type>
int Sparse_graph::num_active_nodes() const
{
    int count = 0; 

    for(unsigned int i = 0; i < m_nodes.size(); ++i)
    {
        if(m_nodes[i].index() != -1)
        {
            ++count;
        }
    }
    return count;
}

template<class Node_type, class Edge_type>
int Sparse_graph::num_edges() const
{
    int total = 0;

    for(EdgeListVector::const_iterator it = m_edges.begin(); it != m_edges.end(); ++it)
    {
        total += it->size();
    }

    return total;
}

template<class Node_type, class Edge_type>
void Sparse_graph::clear()
{
    m_next_node_index = 0;
    m_nodes.clear();
    m_edges.clear();
}

template<class Node_type, class Edge_type>
void Sparse_graph::remove_edges()
{
    for(EdgeListVector::iterator it = m_edges.begin(); it != m_edges.end(); ++it)
    {
        it->clear();
    }
}

#endif // SPARSE_GRAPH_HPP