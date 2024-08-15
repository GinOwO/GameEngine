# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MandelbrotSet VERSION 1.0)

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

# Add source files
SET(MATH_SOURCES
	${PROJECT_SOURCE_DIR}/src/math/Vector2f.cpp
	${PROJECT_SOURCE_DIR}/src/math/Vector3f.cpp
	${PROJECT_SOURCE_DIR}/src/math/Matrix4f.cpp
	${PROJECT_SOURCE_DIR}/src/math/Quaternion.cpp
	${PROJECT_SOURCE_DIR}/src/math/Transform.cpp
)


SET(CORE_SOURCES
	${PROJECT_SOURCE_DIR}/src/core/Window.cpp
	${PROJECT_SOURCE_DIR}/src/core/Engine.cpp
	${PROJECT_SOURCE_DIR}/src/core/Timer.cpp
	${PROJECT_SOURCE_DIR}/src/core/Input.cpp
	${PROJECT_SOURCE_DIR}/src/core/Camera.cpp
	${PROJECT_SOURCE_DIR}/src/core/RenderUtil.cpp
)

SET(GRAPHICS_SOURCES
	${PROJECT_SOURCE_DIR}/src/graphics/Shader.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Vertex.cpp
	${PROJECT_SOURCE_DIR}/src/graphics/Mesh.cpp
)

SET(GAME_SOURCES
	${PROJECT_SOURCE_DIR}/src/game/Game.cpp
)

SET(MISC_SOURCES
	${PROJECT_SOURCE_DIR}/src/misc/glad.c
)

set(SOURCES
	${MATH_SOURCES}
	${CORE_SOURCES}
	${MISC_SOURCES}
	${GAME_SOURCES}
	${GRAPHICS_SOURCES}

	${PROJECT_SOURCE_DIR}/main.cpp
)

# Add executable target
add_executable(GameEngine ${SOURCES})

# Add include directories
target_include_directories(GameEngine PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(GameEngine glfw OpenGL::GL)

add_subdirectory(include/glfw EXCLUDE_FROM_ALL)

SET(GCC_COMPILE_FLAGS "-g -O0")
SET(GCC_LINK_FLAGS    "")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")