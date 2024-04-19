#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



#include <functional>


#define ASSERT(x)	if(!(x)) __debugbreak();

#ifdef _DEBUG
#define GLCall(x)	GLClearError();\
					x;\
					ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x)	x
#endif

#define PI 3.1416f

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);