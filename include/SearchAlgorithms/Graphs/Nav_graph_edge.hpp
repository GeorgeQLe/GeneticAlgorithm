#ifndef NAV_GRAPH_EDGE_HPP
#define NAV_GRAPH_EDGE_HPP

#include "Graph_edge.hpp"

class Nav_graph_edge : public Graph_edge
{
    public:
    Nav_graph_edge(int from, int to, double cost)
        : Graph_edge(from, to, cost), m_id_intersecting(-1) { }

    Nav_graph_edge(int from, int to, double cost, int id)
        : Graph_edge(from, to, cost), m_id_intersecting(id) { }

    Nav_graph_edge(std::ifstream& stream)
    {
        char buffer[50];
        stream >> buffer >> m_from >> buffer >> m_to >> buffer >> m_cost;
        stream >> buffer >> m_id_intersecting;
    }

    int get_id() const { return m_id_intersecting; }
    void set_id(int id) { m_id_intersecting = id; }

    friend std::ostream& operator<<(std::ostream& output, const Nav_graph_edge& edge)
    {
        output << "From: " << edge.m_from << " To: " << edge.m_to;
        output << " Cost: " << edge.m_cost << " Id: " << edge.m_id_intersecting << "\n";
    }

    protected:
    int m_id_intersecting;
};

#endif // NAV_GRAPH_EDGE_HPP