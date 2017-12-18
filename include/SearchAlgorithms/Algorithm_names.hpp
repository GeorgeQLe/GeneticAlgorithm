#ifndef ALGORITHM_NAMES_HPP
#define ALGORITHM_NAMES_HPP

#include <string>
#include <vector>

class Algorithm_names
{
    typedef std::vector<std::string> Filename_list;

    public:
    void add_names();

    std::string get_names(int index) { return m_names.at(index); }

    private:
    Algorithm_names(std::string filename) { }

    Filename_list m_names;
};

#endif // ALGORITHM_NAMES_HPP