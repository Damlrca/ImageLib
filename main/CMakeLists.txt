add_executable(main main.cpp)

target_include_directories(main PUBLIC ../ImageLib)
target_link_libraries(main ImageLib)
