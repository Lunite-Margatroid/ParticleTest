#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_MVPTrans;
uniform mat3 u_NormalTrans;
uniform mat4 u_MVTrans;
uniform mat4 u_VTrans;
uniform mat4 u_MTrans;
uniform vec3 u_CameraPos;

out vec3 NormalVec;		// 世界坐标法向量
out vec3 HalfVec;		// 世界坐标半向量
out vec3 FragPos;		// 世界坐标系的顶点坐标

out vec2 TexCoord;

void main()
{
	FragPos = vec3(u_MTrans * vec4(aPosition, 1.0f));
	NormalVec = normalize(u_NormalTrans * aNormal);
	
	HalfVec = NormalVec + normalize(u_CameraPos - FragPos);
	
	gl_Position = u_MVPTrans * vec4(aPosition, 1.0f);
	
	TexCoord = aTexCoord;
}