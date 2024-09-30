# cmake_minimum_required(VERSION 3.10)

# project(CentipedeArcadeGame VERSION 1.0)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Add source files from src directory
# file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# # Add the executable
# add_executable(CentipedeArcadeGame ${SOURCES})

# # Include directories for headers
# target_include_directories(CentipedeArcadeGame PRIVATE ${PROJECT_SOURCE_DIR}/include)

# # Include SFML headers
# include_directories(${PROJECT_SOURCE_DIR}/../../SFML/include)

# # Link SFML libraries
# link_directories(${PROJECT_SOURCE_DIR}/../../SFML/lib)

# target_link_libraries(CentipedeArcadeGame PUBLIC sfml-graphics sfml-system sfml-window)

# # Set working directory to the binary directory
# set_target_properties(
#     CentipedeArcadeGame PROPERTIES
#     VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
# )

# # Copy the assets folder to the binary directory
# file(COPY ${PROJECT_SOURCE_DIR}/assets
#     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets")


# CMakeLists.txt inside src

# Find all .cpp files in this directory
file(GLOB_RECURSE SOURCES *.cpp)

# Create the executable
add_executable(CentipedeGame ${SOURCES})

# Link SFML libraries
target_link_libraries(CentipedeGame sfml-graphics sfml-window sfml-system)
