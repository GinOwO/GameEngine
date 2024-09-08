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

# Shader Test
add_executable(ShaderTest ${PROJECT_SOURCE_DIR}/tests/graphics/Shader_test.cpp)
target_link_libraries(ShaderTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME ShaderTest COMMAND ShaderTest)

# Mesh Test
add_executable(MeshTest ${PROJECT_SOURCE_DIR}/tests/graphics/Mesh_test.cpp)
target_link_libraries(MeshTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME MeshTest COMMAND MeshTest)

# Material Test
add_executable(MaterialTest ${PROJECT_SOURCE_DIR}/tests/graphics/Material_test.cpp)
target_link_libraries(MaterialTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME MaterialTest COMMAND MaterialTest)

# BasicShader Test
add_executable(BasicShaderTest ${PROJECT_SOURCE_DIR}/tests/graphics/BasicShader_test.cpp)
target_link_libraries(BasicShaderTest GTest::gtest GTest::gtest_main GameEngineLib)
add_test(NAME BasicShaderTest COMMAND BasicShaderTest)
