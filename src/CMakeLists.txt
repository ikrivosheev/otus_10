configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(bulk main.cpp)

add_library(utils version.cpp)
add_library(logger record.cpp logger.cpp console_handler.cpp file_handler.cpp state_machine.cpp)

set_target_properties(bulk utils logger PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(bulk utils logger)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS bulk RUNTIME DESTINATION bin)
