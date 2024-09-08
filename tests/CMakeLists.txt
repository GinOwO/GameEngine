# CMakeLists.txt for tests

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add test executable
add_executable(Vector3fTest ${PROJECT_SOURCE_DIR}/tests/math/Vector3f_test.cpp)

# Link GoogleTest and the GameEngineLib library
target_link_libraries(Vector3fTest GTest::gtest GTest::gtest_main GameEngineLib)

# Add tests
add_test(NAME Vector3fTest COMMAND Vector3fTest)
