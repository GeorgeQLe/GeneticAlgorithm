/*-----------------------------------------------------------------------------------------------
|    Copyright 2017 George Le                                                                   |
|                                                                                               |
|    A finite graph is a graph in which the vertex set and the edge set are finite sets.        |
|                                                                                               |
|    The class below is my implementation of a finite graph. The central data structure of      |
|    my graph is a pair of graph nodes and their corresponding edges. These edges go from       |
|    the nodes they are paired with, known as source nodes, to the edges' destination nodes.    |
|    Edges link their source node to a destination node that is in a layer below it. Each       |
|    pair forms a layer of the graph and are stored in a map structure with a key value         |
|    corresponding to the layer's index. Nodes are labeled by an index number that corresponds  |
|    to the nodes' horizontal position in that layer.                                           |
|                                                                                               |
-----------------------------------------------------------------------------------------------*/
#ifndef FINITE_GRAPH
#define FINITE_GRAPH

#include <map> // std::map
#include <utility> // std::pair
#include <vector> // std::vector

#include "Graph_edge.hpp"
#include "Graph_node.hpp"

class Finite_graph
{
    public:
    Finite_graph(unsigned int min_x, unsigned int max_x, unsigned int min_y, unsigned int max_y) 
        : m_min_x(min_x), m_max_x(max_x), m_min_y(min_y), m_max_y(max_y) { }

    /*---------------------------------------------------------------------------
        Adds a node to the layer specified which serves as the top of the graph.
    ---------------------------------------------------------------------------*/
    void add_node(int start_layer);
    /*--------------------------------------------------------------------------
        Adds a node to the layer specified, adds a layer if that layer doesn't
        exist yet. Also takes in a list of coordinate pairs (layer, index) of
        a source node in a previous layer.
    --------------------------------------------------------------------------*/
    void add_node(int add_layer, std::vector<std::pair<int, int>> from_coords);

    /*-------------------------------------------------------------------------
        Sets all the costs of a node's edges to be a certain value. Nodes are
        selected by their layer by index coordinates not their actual coordi-
        nates
    -------------------------------------------------------------------------*/
    void add_edge_cost(std::pair<int, int> source_coords, int cost);
    /*---------------------------------------------------------------------------------------
        Modifies the cost of an edge between the two nodes selected by their layer by index
        coordinates not their actual coordinates 
    ---------------------------------------------------------------------------------------*/
    void add_edge_cost(std::pair<int,int> from_coords, std::pair<int, int> to_coords, int cost);

    /*-----------------------------------------------------------------------------
        Finds the node that is at the location requests. Location parameters are 
        not explicitly the x,y coordinates of the node in the environment (though
        the y-value generally happens to be the same value), but are the layer by
        index coordinate in the graph.
    -----------------------------------------------------------------------------*/
    const Graph_node access_node(int index, int layer);

    /*-----------------------------------------------------------------------------
        Finds all the edges that go from the node at the specified index and layer
        and stores them into a vector data structure, returning it.
    -----------------------------------------------------------------------------*/
    const std::vector<Graph_node> access_edges(int index, int layer);

    /*-------------------------------------------------------------------------------------------------------------
        Finds the edge that goes from the specified source node to the specified destination nodes and returns it
    -------------------------------------------------------------------------------------------------------------*/
    const Graph_edge access_edge(int source_index, int source_layer, int destination_index, int destination_layer);

    private:
    /*-------------------------------------------------------------------------------
        Private member function that creates a node and adds it to a user specified 
        layer. Returns true if the node can be inserted and false if the node 
        cannot be inserted.
    -------------------------------------------------------------------------------*/
    bool create_node(int layer);

    // this container holds the nodes and edges that comprise this graph
    std::map<int, std::pair<std::vector<Graph_node>, std::vector<std::vector<Graph_edge>>>> m_graph;

    unsigned int m_min_x, m_max_x, m_min_y, m_max_y;

    bool m_directed;
    bool m_has_cost;
    bool m_all_nodes_have_cost;
};

#endif // FINITE_GRAPH_HPP