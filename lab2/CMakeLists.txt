cmake_minimum_required(VERSION 3.15)
project(MethOpt_labs)

set(CMAKE_CXX_STANDARD 17)

add_executable(Compute_gradient.h ConjugateGradients_method.h get_Number.h GradientDescent_method.h
        main.cpp Output.h Parser.h SteepestDescent_method.h main.cpp)
