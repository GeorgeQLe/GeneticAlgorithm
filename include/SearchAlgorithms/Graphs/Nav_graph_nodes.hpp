#ifndef NAV_GRAPH_NODES_HPP
#define NAV_GRAPH_NODES_HPP

#include "include/Utilities/2D/Vector2D.hpp"
#include "Graph_nodes.hpp"

template<class Occupant = void*>
class Nav_graph_nodes : public Graph_node
{
    public:
    Nav_graph_nodes() : m_occupant(Occupant()) { }

    Nav_graph_nodes(int index, Vector2D position) 
        : Graph_nodes(index), m_position(position), m_occupant(Occupant()) { }

    Nav_graph_nodes(std::ifstream& stream) : m_occupant(Occupant()) { }

    virtual ~Nav_graph_nodes() { }

    Vector2D get_position() const { return m_position; }
    Occupant get_occupant() const { return m_occupant; }

    void set_position(Vector2D new_position) { m_position = new_position; } 
    void set_occupant(Occupant new_occupant) { m_occupant = new_occupant; }

    friend std::ostream& operator<<(std::ostream& output, const Nav_graph_nodes& nodes)
    {
        output << "Index: " << nodes.m_index << " Position x: " << nodes.m_position.x;
        output << " Position y: " << n.m_position.y << "\n";

        return output;
    }

    protected:
    Vector2D m_position;

    Occupant m_occupant;
};

#endif // NAV_GRAPH_NODES_HPP