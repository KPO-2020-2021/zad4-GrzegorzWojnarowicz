cmake_minimum_required(VERSION 3.12)
project(ROTATION3D)

set(EXECUTABLE ${CMAKE_PROJECT_NAME}_run)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tst)
add_subdirectory(lib/googletest-master)
add_subdirectory(lib/GNUPlot)

include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/lib/GNUPlot)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true inc/*.h src/*.cpp)

add_executable(${EXECUTABLE} ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
target_link_libraries(${EXECUTABLE} PRIVATE GNUPlot_lib)





# Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
include(Documentation)
include(LTO)



# Check for LTO support.
find_lto(CXX)

# --------------------------------------------------------------------------------
#                         Locate files (change as needed).
# --------------------------------------------------------------------------------

set(TESTFILES        # All .cpp files in tests/
        tst/main.cpp
)
set(LIBRARY_NAME engine)  # Default name for the library built from src/*.cpp (change if you wish)

# --------------------------------------------------------------------------------
#                            Build! (Change as needed)
# --------------------------------------------------------------------------------
# Compile all sources into a library.
add_library(${LIBRARY_NAME} OBJECT ${SOURCES})

# Lib needs its header files, and users of the library must also see these (PUBLIC). (No change needed)
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)




