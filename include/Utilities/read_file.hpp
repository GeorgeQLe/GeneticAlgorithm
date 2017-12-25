#ifndef READ_FILE_HPP
#define READ_FILE_HPP

#include <string>
#include <vector>

void read_scores_file(std::vector<std::vector<double>>& scores, std::vector<std::vector<std::string>>& score_label, 
                        std::vector<std::string>& problem_names, std::string file_scores);

void read_solution(std::string file_solutions, std::vector<std::vector<std::string>>& solution, 
                    unsigned int num_problems, unsigned int num_potential_solutions);

#endif // READ_FILE_HPP