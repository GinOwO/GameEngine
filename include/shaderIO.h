#ifndef includeshaderIOh_
#define includeshaderIOh_

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string read_shader(const std::string &filepath);
GLuint create_shader_module(const std::string &shader_source);
GLuint create_shader_program(const std::string &vertex_filepath,
			     const std::string &fragment_filepath);

#endif // includefileIOfileIOh_
