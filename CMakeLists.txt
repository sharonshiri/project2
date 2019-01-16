cmake_minimum_required(VERSION 3.12)
project(project2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(project2 Server.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.cpp FileCacheManager.h Main.cpp Main.h MatrixSolver.h main.cpp MyReverseClientHandler.cpp MyReverseClientHandler.h MatrixSolver.cpp State.h
        DFS.h Searchable.h Searcher.h MatrixSearchable.h MatrixSolution.cpp MatrixSolution.h BestFirstSearch.h BFS.h AStar.h MyParallelServer.cpp MyParallelServer.h)