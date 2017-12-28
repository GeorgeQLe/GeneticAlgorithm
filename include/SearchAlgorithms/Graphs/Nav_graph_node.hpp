#ifndef NAV_GRAPH_NODE_HPP
#define NAV_GRAPH_NODE_HPP

#include "Graph_node.hpp"
#include "Utilities/2D/Vector2D.hpp"

template<class Occupant = void*>
class Nav_graph_node : public Graph_node
{
    public:
    Nav_graph_node(int layer, int index) : Graph_node(layer, index), m_occupant(Occupant()) { }

    Nav_graph_node(int layer, int index, Vector2D position) : Graph_node(layer, index), m_position(position), m_occupant(Occupant()) { }

    Nav_graph_node(std::ifstream& stream) : m_occupant(Occupant()) { }

    virtual ~Nav_graph_node() { }

    Vector2D get_position() const { return m_position; }
    Occupant get_occupant() const { return m_occupant; }

    void set_position(Vector2D new_position) { m_position = new_position; } 
    void set_occupant(Occupant new_occupant) { m_occupant = new_occupant; }

    friend std::ostream& operator<<(std::ostream& output, const Nav_graph_node& nodes)
    {
        output << "Index: " << nodes.m_index << " Position x: " << nodes.m_position.x;
        output << " Position y: " << nodes.m_position.y << "\n";

        return output;
    }

    protected:
    // optional record of the coordinates that this node lies on 
    // in the environment space
    Vector2D m_position;

    // optional storage of a handle to the occupant of this node
    Occupant m_occupant;
};

#endif // NAV_GRAPH_NODE_HPP