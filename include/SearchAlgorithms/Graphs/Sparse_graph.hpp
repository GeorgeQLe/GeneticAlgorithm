#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

#include <map> // std::map
#include <utility> // std::pair
#include <vector> // std::vector

#include "Graph_edge.hpp"
#include "Graph_node.hpp"

class Sparse_graph
{
    public:
    Sparse_graph(unsigned int min_x, unsigned int max_x, unsigned int min_y, unsigned int max_y) : m_min_x(min_x), m_max_x(max_x), m_min_y(min_y), m_max_y(max_y) { }

    bool create_node(int layer, int index)

    /*---------------------------------------------------------------------------
        Adds a node to the layer specified which serves as the top of the graph.
    ---------------------------------------------------------------------------*/
    void add_node(int start_layer);
    /*-------------------------------------------------------------------------
        Adds a node to the layer specified, adds a layer if that layer doesn't
        exist yet. Also takes in a list of coordinate pairs (layer, index) of
        a source node in a previous layer.
    -------------------------------------------------------------------------*/
    void add_node(int add_layer, std::vector<std::pair<int, int>> from_coords);

    private:
    // this container holds the nodes and edges that comprise this graph
    std::map<int, std::pair<std::vector<Graph_node>, std::vector<std::vector<Graph_edge>>>> m_graph;

    unsigned int m_min_x, m_max_x, m_min_y, m_max_y;

    bool m_directed;
};

#endif