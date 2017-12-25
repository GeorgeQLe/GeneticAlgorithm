#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Utilities/read_file.hpp"

std::string read_file(std::string file_name)
{
    std::string line;
    std::ifstream file;
    file.open(file_name);

    if(file.is_open())
    {
        
    }
}

void read_scores_file(std::vector<std::vector<double>>& scores, std::vector<std::vector<std::string>>& score_label, 
                        std::vector<std::string>& problem_names, std::string file_scores)
{
    std::string line;
    std::ifstream file;
    file.open(file_scores);

    if(file.is_open())
    {
        std::cout << "Adding information from " << file_scores << "\n";
        int number_line = 0;
        std::vector<std::string> temp_labels;
        std::vector<double> temp_scores;
        while(getline(file, line))
        {
            ++number_line;
            if(number_line == 10)
            {
                number_line = 0;
                score_label.push_back(temp_labels);
                temp_labels.clear();
                scores.push_back(temp_scores);
                temp_scores.clear();
            }
            else if(number_line == 1)
            {
                problem_names.push_back(line);
            }
            else if(number_line % 2 == 0)
            {
                temp_labels.push_back(line);
            }    
            else if(number_line % 2 == 1)
            {
                temp_scores.push_back(atof(line.c_str()));
            }
        }
        file.close();
    }
}

void read_solution(std::string file_solutions, std::vector<std::vector<std::string>>& solution, 
                    unsigned int num_problems, unsigned int num_potential_solutions)
{
    std::string line;
    std::ifstream file;
    file.open(file_solutions);

    if(file.is_open())
    {
        std::cout << "Adding information from " << file_solutions << "\n";
        while(getline(file, line))
        {
            for(unsigned int i = 0; i < num_problems; ++i)
            {
                std::vector<std::string> temp;
                for(unsigned int j = 0; j < num_potential_solutions; ++j)
                {
                    temp.push_back(line);
                }
                solution.push_back(temp);
            }
        }
    }
}