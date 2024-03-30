cmake_minimum_required (VERSION 3.0)

Project(MEEv
        LANGUAGES CXX
        VERSION 1.0.0
)
add_executable(MEEv src/main.cpp src/main.cpp src/Calculator.h src/Calculator.cpp src/Utility.h src/Utility.cpp)


target_include_directories(MEEv PRIVATE src)
set_target_properties(MEEv PROPERTIES CXX_STANDARD 20)
