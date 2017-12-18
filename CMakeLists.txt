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
)

set(INCLUDES
    include/ANN/Activation_Functions/activation_functions.hpp
    include/ANN/Activation_Functions/sigmoid.hpp
    include/ANN/Activation_Functions/step.hpp
    include/ANN/FeedForwardANN.hpp
    include/ANN/Neurons/ANN_layers.hpp
    include/ANN/Neurons/ANN_neuron.hpp
    include/CNN/convolutional_NN.hpp
    include/ExpectedData/expected_data.hpp
    include/GA/GeneticAlgorithmBool.hpp
    include/SearchAlgorithms/Algorithm_types/Astar_heuristic.hpp
    include/SearchAlgorithms/Algorithm_types/Astar_search.hpp
    include/SearchAlgorithms/Algorithm_types/Beam_search.hpp
    include/SearchAlgorithms/Algorithm_types/BFS_search.hpp
    include/SearchAlgorithms/Algorithm_types/DFS_search.hpp
    include/SearchAlgorithms/Algorithm_types/Hill_climbing.hpp
    include/SearchAlgorithms/Algorithm_types/UCS_search.hpp
    include/SearchAlgorithms/Graphs/Graph_edge.hpp
    include/SearchAlgorithms/Graphs/Graph_nodes.hpp
    include/SearchAlgorithms/Graphs/Nav_graph_edge.hpp
    include/SearchAlgorithms/Graphs/Nav_graph_nodes.hpp
    include/SearchAlgorithms/Graphs/Searcher.hpp
    include/SearchAlgorithms/Graphs/Sparse_graph.hpp
    include/SearchAlgorithms/Algorithm_names.hpp
    include/SearchAlgorithms/Algorithm.hpp
    include/Utilities/2D/Vector2D.hpp
    include/Utilities/Useful_constants.hpp
    include/Utilities/Utilities.hpp
)

include_directories(include)

add_executable(${PROJECT_NAME}
    ${SRC}
    ${INCLUDES}
)

set(PROJECT_DATA
    TestProblems/prob1.map
    TestProblems/prob2.map
    TestProblems/prob3.map
    TestProblems/prob4.map
    TestProblems/prob5.map
    TestProblems/prob6.map
    TestProblems/prob7.map
    TestProblems/prob8.map
    TestProblems/prob9.map
    TestProblems/prob10.map
    TestProblems/prob11.map
    TestProblems/prob12.map
    TestProblems/prob13.map
    TestProblems/prob14.map
    TestProblems/prob15.map
    TestProblems/prob16.map
    TestProblems/prob17.map
    TestProblems/prob18.map
    TestProblems/prob19.map
    TestProblems/prob20.map
    TestProblems/prob21.map
    TestProblems/prob22.map
    TestProblems/prob23.map
    TestProblems/prob24.map
    TestProblems/prob25.map
    TestProblems/prob26.map
    TestProblems/prob27.map
    TestProblems/prob28.map
    TestProblems/prob29.map
    TestProblems/prob30.map
)

foreach(DATA ${PROJECT_DATA})
    configure_file(${DATA} ${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILENAME} COPYONLY)
endforeach()