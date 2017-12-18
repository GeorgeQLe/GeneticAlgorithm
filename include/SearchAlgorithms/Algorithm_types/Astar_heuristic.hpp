#ifndef ASTAR_HEURISTIC_HPP
#define ASTAR_HEURISTIC_HPP

typedef enum heuristic_type { NO_HEURISTIC_TYPE, DIJKSTRA, EUCLIDIAN, MANHATTAN } Heuristic_type;

#include "include/Utilities/2D/Vector2D.hpp"
#include "include/Utilities/Utilities.hpp"

class Heuristic_euclid
{
    public:
    Heuristic_euclid() { }

    // calculate the straight line distance from node 1 and node 2
    template <class Graph_type>
    static double calculate(const Graph_type& graph, int node1, int node2)
    {
        return Vec2DDistance(graph.get_node(node1).position(), graph.get_node(node2).position());
    }
};

class Noisy_heuristic_euclid
{
    public:
    Noisy_heuristic_euclid() { }

    // calculate the straight line distance from node 1 to node 1
    template <class Graph_type>
    static double calculate(const Graph_type& graph, int node1, int node2)
    {
        return Vec2DDistance(graph.get_node(node1).position(), graph.get_node(node2).position()) * RandInRange(0.9f, 1.1f);
    }
};

class Heuristic_djikstra
{
    public:
    template<class Graph_type>
    static double calculate(const Graph_type& graph, int node1, int node2)
    {
        return 0;
    }
};

#endif // ASTAR_HEURISTIC_HPP