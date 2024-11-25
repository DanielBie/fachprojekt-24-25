cmake_minimum_required(VERSION 3.10)
project(vectorization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -mavx2 -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -DNDEBUG -fno-tree-vectorize -mavx2 -march=native")
set(CMAKE_BUILD_TYPE RELEASE)

### Get the underlying Linux Kernel version to check feature availability.
execute_process(COMMAND uname -r OUTPUT_VARIABLE UNAME_RESULT OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX MATCH "[0-9]+.[0-9]+" LINUX_KERNEL_VERSION ${UNAME_RESULT})

### Disable specific features if not provided by the Linux Kernel.
if (LINUX_KERNEL_VERSION VERSION_LESS 5.13)
    add_definitions(-DNO_PERF_COUNT_SW_CGROUP_SWITCHES)
endif ()

if (LINUX_KERNEL_VERSION VERSION_LESS 5.12)
    add_definitions(-DNO_PERF_SAMPLE_WEIGHT_STRUCT)
endif ()

if (LINUX_KERNEL_VERSION VERSION_LESS 5.11)
    add_definitions(-DNO_PERF_SAMPLE_DATA_PAGE_SIZE -DNO_PERF_SAMPLE_CODE_PAGE_SIZE)
endif ()


### Add include directory.
include_directories(../perf-cpp/include/)

### Library
add_library(perf-cpp ../perf-cpp/src/counter.cpp ../perf-cpp/src/group.cpp ../perf-cpp/src/counter_definition.cpp ../perf-cpp/src/event_counter.cpp ../perf-cpp/src/sampler.cpp)


add_executable(vectorization vectorization.cpp)

target_link_libraries(vectorization perf-cpp)
