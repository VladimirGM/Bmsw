cmake_minimum_required(VERSION 3.3)
project(bmSmallWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        bm/Cell.cpp
        bm/Cell.h
        bm/CellAstrocyte.cpp
        bm/CellAstrocyte.h
        bm/CellNeuron.cpp
        bm/CellNeuron.h
        bm/SmallWorld.cpp
        bm/SmallWorld.h

        bm/voro++/voro++.hh
        bm/voro++/voro++.cc

        bm/brainEC/ecNeuron.h
        bm/brainEC/ecNeuron.cpp
        bm/brainEC/ecAstrocyte.h
        bm/brainEC/ecAstrocyte.cpp
        bm/brainEC/ecConstant.h

        bm/ses/sesSolver.h
        bm/ses/sesSolver.cpp
        bm/ses/sesChordsSolver.h
        bm/ses/sesChordsSolver.cpp
        bm/ses/sesTangetSolver.h
        bm/ses/sesTangetSolver.cpp
        bm/ses/sesCombinedSolver.h
        bm/ses/sesCombinedSolver.cpp


        main.cpp)

add_executable(bmSmallWorld ${SOURCE_FILES})