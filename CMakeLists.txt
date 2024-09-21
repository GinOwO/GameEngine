# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(GameEngine VERSION 1.0)

SET(CMAKE_BUILD_TYPE "Debug")

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source files for the library
set(MATH_SOURCES
	${PROJECT_SOURCE_DIR}/src/math/Vector2f.cpp
	${PROJECT_SOURCE_DIR}/src/math/Vector3f.cpp
	${PROJECT_SOURCE_DIR}/src/math/Matrix4f.cpp
	${PROJECT_SOURCE_DIR}/src/math/Quaternion.cpp
	${PROJECT_SOURCE_DIR}/src/math/Transform.cpp
)

set(CORE_SOURCES
	${PROJECT_SOURCE_DIR}/src/core/Window.cpp
	${PROJECT_SOURCE_DIR}/src/core/Engine.cpp
	${PROJECT_SOURCE_DIR}/src/core/Timer.cpp
	${PROJECT_SOURCE_DIR}/src/core/Input.cpp
)

set(RESOURCE_MANAGEMENT
	${PROJECT_SOURCE_DIR}/src/graphics/resource_management/ShaderResource.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/resource_management/MeshResource.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/resource_management/TextureResource.cpp
)

set(MESH_MODELS
	${PROJECT_SOURCE_DIR}/src/graphics/Mesh.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/mesh_models/OBJModel.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/mesh_models/FBXModel.cpp
)

SET(SHADER_CLASSES
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardAmbient.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardDirectional.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardPoint.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardSpot.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardAnimation.cpp
)

set(GRAPHICS_SOURCES
	${PROJECT_SOURCE_DIR}/src/graphics/Shader.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Vertex.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Texture.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Material.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/RenderingEngine.cpp
	${SHADER_CLASSES}
	${MESH_MODELS}
)

set(GAME_SOURCES
	${PROJECT_SOURCE_DIR}/src/game/TestGame.cpp
)

set(COMPONENT_SOURCES
	${PROJECT_SOURCE_DIR}/src/components/GameObject.cpp
	${PROJECT_SOURCE_DIR}/src/components/Camera.cpp
	${PROJECT_SOURCE_DIR}/src/components/MeshRenderer.cpp
	${PROJECT_SOURCE_DIR}/src/components/SharedGlobals.cpp
)

set(PHYSICS_SOURCES
	${PROJECT_SOURCE_DIR}/src/physics/Skeleton.cpp
)

set(MISC_SOURCES
	${PROJECT_SOURCE_DIR}/src/misc/glad.c
)


# Create a static library for common sources
add_library(GameEngineLib STATIC
	${MATH_SOURCES}
	${CORE_SOURCES}
	${GRAPHICS_SOURCES}
	${MISC_SOURCES}
	${COMPONENT_SOURCES}
	${GAME_SOURCES}
	${RESOURCE_MANAGEMENT}
	${PHYSICS_SOURCES}
)

# Bullet
find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})
link_libraries(${BULLET_LIBRARIES})

# Assimp
find_package(assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})

# OpenEXR
set(IMATH_INCLUDE_DIRS /usr/include/Imath)
set(IMATH_LIBRARIES Imath-3_1)

set(OPENEXR_INCLUDE_DIRS /usr/include/OpenEXR)
set(OPENEXR_LIBRARIES OpenEXR-3_1 OpenEXRUtil-3_1 OpenEXRCore-3_1 Iex-3_1 IlmThread-3_1 Imath-3_1)

find_package(Imath REQUIRED)
include_directories(${IMATH_INCLUDE_DIRS})
find_package(OpenEXR REQUIRED)
include_directories(${OPENEXR_INCLUDE_DIRS})

# Add executable target
add_executable(GameEngine ${PROJECT_SOURCE_DIR}/main.cpp)


# Link the libraries to the executable
target_link_libraries(GameEngine 
	GameEngineLib 
	glfw OpenGL::GL 
	BulletDynamics BulletCollision LinearMath
	${ASSIMP_LIBRARIES}
	${OPENEXR_LIBRARIES}
	${Imath_LIBRARIES}
)
	
# Add include directories
target_include_directories(GameEngineLib PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(GameEngine PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(GameEngine PRIVATE ${PHYSX}/include)

add_subdirectory(include/glfw EXCLUDE_FROM_ALL)

# # Add GoogleTest
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# enable_testing()

# # Add test directory
# add_subdirectory(tests)

SET(GCC_COMPILE_FLAGS "-g -O0")
SET(GCC_LINK_FLAGS    "-lm -lpthread -lGL -ldl -lassimp")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
