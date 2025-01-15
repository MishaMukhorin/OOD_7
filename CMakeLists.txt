cmake_minimum_required(VERSION 3.24)
project(OOD_7) 

set(CMAKE_CXX_STANDARD 20)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(ood7 ShapesOut.cpp
        Commands/ShapesCommandProcessor.cpp
        Factory/ShapeTypeFactory.cpp
        Picture/Picture.cpp
        Canvas/CCanvas.cpp)

target_link_libraries(ood7 PRIVATE sfml-graphics)
target_compile_features(ood7 PRIVATE cxx_std_17)


add_executable(ood7_Tests tests/ShapesTests.cpp)
#
#
target_link_libraries(ood7_Tests gtest gmock gtest_main)

add_test(NAME ood7_Tests COMMAND tests)
install(TARGETS ood7)
