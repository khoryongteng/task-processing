cmake_minimum_required(VERSION 3.14) # Updated to a more recent version

# Set project name and version
project(task VERSION 0.1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable target
add_executable(${PROJECT_NAME})

# Add source files to the target
target_sources(${PROJECT_NAME}
  PRIVATE
    src/main.cpp
    src/task.cpp
    src/task_queue.cpp
    src/producer_manager.cpp
    src/consumer_manager.cpp
)

# Specify include directories
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# target_link_libraries(${PROJECT_NAME}
#   PRIVATE
# )

# Optional: Set C++ standard for targets
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)