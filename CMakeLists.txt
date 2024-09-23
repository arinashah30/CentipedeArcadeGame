# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CentipedeGame VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(OPENAL_LIBRARY ${PROJECT_SOURCE_DIR}/../SFML/extlibs/libs-msvc/x64/openal32.lib)


# Add source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/centipede.cpp
    ${PROJECT_SOURCE_DIR}/laserblast.cpp
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/mushroom.cpp
    ${PROJECT_SOURCE_DIR}/spider.cpp
    ${PROJECT_SOURCE_DIR}/starship.cpp
)

# Add the executable
add_executable(CentipedeGame ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/../SFML/include)

link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)

# Link the executable to the libraries in the lib directory
target_link_libraries(CentipedeGame PUBLIC sfml-graphics sfml-system sfml-window)

set_target_properties(
    CentipedeGame PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${COMMON_OUTPUT_DIR}/bin"
)
# Copy DLLs using file(COPY ...)
file(COPY ${PROJECT_SOURCE_DIR}/fonts
     DESTINATION "${COMMON_OUTPUT_DIR}/bin")
file(COPY ${PROJECT_SOURCE_DIR}/graphics
     DESTINATION "${COMMON_OUTPUT_DIR}/bin")
 file(COPY "${PROJECT_SOURCE_DIR}/low res"
 DESTINATION "${COMMON_OUTPUT_DIR}/bin")
 file(COPY ${PROJECT_SOURCE_DIR}/sound
 DESTINATION "${COMMON_OUTPUT_DIR}/bin")
