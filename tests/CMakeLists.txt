# CMakeLists.txt for tests

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Vector3f Test
add_executable(Vector3fTest ${PROJECT_SOURCE_DIR}/tests/math/Vector3f_test.cpp)
target_link_libraries(Vector3fTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME Vector3fTest COMMAND Vector3fTest)

# Vector2f Test
add_executable(Vector2fTest ${PROJECT_SOURCE_DIR}/tests/math/Vector2f_test.cpp)
target_link_libraries(Vector2fTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME Vector2fTest COMMAND Vector2fTest)

# Transform Test
add_executable(TransformTest ${PROJECT_SOURCE_DIR}/tests/math/Transform_test.cpp)
target_link_libraries(TransformTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME TransformTest COMMAND TransformTest)

# Vertex Test
add_executable(VertexTest ${PROJECT_SOURCE_DIR}/tests/graphics/Vertex_test.cpp)
target_link_libraries(VertexTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME VertexTest COMMAND VertexTest)

# Texture Test
add_executable(TextureTest ${PROJECT_SOURCE_DIR}/tests/graphics/Texture_test.cpp)
target_link_libraries(TextureTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME TextureTest COMMAND TextureTest)

# Material Test
add_executable(MaterialTest ${PROJECT_SOURCE_DIR}/tests/graphics/Material_test.cpp)
target_link_libraries(MaterialTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME MaterialTest COMMAND MaterialTest)

# Input
add_executable(InputTest ${PROJECT_SOURCE_DIR}/tests/core/Input_test.cpp)
target_link_libraries(InputTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME InputTest COMMAND InputTest)

# Timer
add_executable(TimerTest ${PROJECT_SOURCE_DIR}/tests/core/Timer_test.cpp)
target_link_libraries(TimerTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME TimerTest COMMAND TimerTest)
