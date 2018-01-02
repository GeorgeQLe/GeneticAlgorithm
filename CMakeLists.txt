project(AI_PROJECT)

cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11 /MP /Wall")
endif()

set(SRC
    build/driver.cpp
    src/ANN/FeedForwardANN.cpp
    src/ANN/Neurons/ANN_layers.cpp
    src/GA/GeneticAlgorithmBool.cpp
    src/Utilities/Graphs/Finite_graph.cpp
    src/Utilities/Method_scorer.cpp
)

set(INCLUDES
    #include/ANN/Activation_Functions/activation_functions.hpp
    #include/ANN/Activation_Functions/sigmoid.hpp
    #include/ANN/Activation_Functions/step.hpp
    #include/ANN/FeedForwardANN.hpp
    #include/ANN/Neurons/ANN_layers.hpp
    #include/ANN/Neurons/ANN_neuron.hpp
    #include/CNN/convolutional_NN.hpp
    include/ExpectedData/expected_data.hpp
    include/GA/GeneticAlgorithmBool.hpp
    include/SearchAlgorithms/Algorithm_types/Astar_heuristic.hpp
    include/SearchAlgorithms/Algorithm_types/Astar_search.hpp
    include/SearchAlgorithms/Algorithm_types/Beam_search.hpp
    include/SearchAlgorithms/Algorithm_types/BFS_search.hpp
    include/SearchAlgorithms/Algorithm_types/DFS_search.hpp
    include/SearchAlgorithms/Algorithm_types/Hill_climbing.hpp
    include/SearchAlgorithms/Algorithm_types/UCS_search.hpp
    include/SearchAlgorithms/Graphs/Finite_graph.hpp
    include/SearchAlgorithms/Graphs/Graph_edge.hpp
    include/SearchAlgorithms/Graphs/Graph_node.hpp
    include/SearchAlgorithms/Graphs/Nav_graph_edge.hpp
    include/SearchAlgorithms/Graphs/Nav_graph_node.hpp
    include/SearchAlgorithms/Graphs/Searcher.hpp
    include/SearchAlgorithms/Algorithm_names.hpp
    include/SearchAlgorithms/Algorithm.hpp
    include/Utilities/2D/Vector2D.hpp
    include/Utilities/Method_scorer.hpp
    include/Utilities/Useful_constants.hpp
    include/Utilities/Utilities.hpp
)

include_directories(include)

add_executable(${PROJECT_NAME}
    ${SRC}
    ${INCLUDES}
)