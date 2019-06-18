configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(bulkmt main.cpp)

add_library(utils version.cpp)
add_library(logger record.cpp logger.cpp console_handler.cpp file_handler.cpp state_machine.cpp thread_console_handler.cpp thread_file_handler.cpp)

set_target_properties(bulkmt utils logger PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(bulkmt utils logger Threads::Threads)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS bulkmt RUNTIME DESTINATION bin)
