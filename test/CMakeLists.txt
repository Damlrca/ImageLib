add_executable(test test_main.cpp test_Image.cpp)

target_include_directories(test PUBLIC ../ImageLib)
target_link_libraries(test ImageLib)

target_include_directories(test PUBLIC ../gtest)
target_link_libraries(test gtest)