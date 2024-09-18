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

# Quaternion Test
add_executable(QuaternionTest ${PROJECT_SOURCE_DIR}/tests/math/Quaternion_test.cpp)
target_link_libraries(QuaternionTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME QuaternionTest COMMAND QuaternionTest)

# Matrix4f Test
add_executable(Matrix4fTest ${PROJECT_SOURCE_DIR}/tests/math/Matrix4f_test.cpp)
target_link_libraries(Matrix4fTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME Matrix4fTest COMMAND Matrix4fTest)

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
