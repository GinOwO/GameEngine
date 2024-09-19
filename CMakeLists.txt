# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(GameEngine VERSION 1.0)

SET(CMAKE_BUILD_TYPE DEBUG)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if(GIT_SUBMODULE)
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/include/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

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

set(GRAPHICS_SOURCES
	${PROJECT_SOURCE_DIR}/src/graphics/Shader.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Vertex.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Texture.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Material.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardAmbient.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardDirectional.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardPoint.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/ForwardSpot.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/RenderingEngine.cpp
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
)

# Assimp
find_package(assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})

# PhysX
set(PHYSX_BUILD_TYPE "release")
include_directories(${PROJECT_SOURCE_DIR}/external/PhysX/physx/include)

# link_directories(${PROJECT_SOURCE_DIR}/external/PhysX/physx/bin/linux.clang/debug)

if(CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("Building snippet in debug configuration")
	add_compile_definitions(_DEBUG)
	link_directories("${PROJECT_SOURCE_DIR}/external/PhysX/physx/bin/linux.clang/debug") # Debug libraries path
else()
	message("Building snippet in release configuration with PhysX ${PHYSX_BUILD_TYPE} configuration")
	add_compile_definitions(NDEBUG)
	link_directories("${PROJECT_SOURCE_DIR}/external/PhysX/physx/bin/linux.clang/${PHYSX_BUILD_TYPE}") # Release libraries path
endif()

# Add executable target
add_executable(GameEngine ${PROJECT_SOURCE_DIR}/main.cpp)

SET(PHYSX_LIBRARIES
	PhysXExtensions_static_64
	PhysX_static_64
	PhysXPvdSDK_static_64
	PhysXCommon_static_64
	PhysXFoundation_static_64
)

# Link the libraries to the executable
target_link_libraries(GameEngine GameEngineLib glfw OpenGL::GL ${ASSIMP_LIBRARIES} ${PHYSX_LIBRARIES})

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

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} -DPX_PHYSX_STATIC_LIBS")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
