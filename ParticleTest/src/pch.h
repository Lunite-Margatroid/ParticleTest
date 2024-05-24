#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Quaternion
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <random>


#include <functional>

#include <queue>
#include <unordered_set>

// #include <stb/stb_image.h>


#define ASSERT(x)	if(!(x)) __debugbreak()

#ifdef _DEBUG
#define GLCall(x)	do{\
					GLClearError();\
					x;\
					ASSERT(GLLogCall(#x, __FILE__, __LINE__));\
					}while(false)
					
#else
#define GLCall(x)	x
#endif

#define PI 3.1416f

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);