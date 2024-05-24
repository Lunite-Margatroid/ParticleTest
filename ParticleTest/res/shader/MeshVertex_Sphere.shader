#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 u_MVPTrans;
uniform mat3 u_NormalTrans;
uniform mat4 u_MVTrans;
uniform mat4 u_VTrans;

out vec3 NormalVec;
out vec3 HalfVec;
out vec3 FragPos;		// 相机坐标系的顶点坐标

out vec2 TexCoord;


void main()
{


	FragPos = vec3(u_MVTrans * vec4(aPosition, 1.0f));
	NormalVec = mat3(u_VTrans) * u_NormalTrans * aPosition;
	HalfVec = normalize(NormalVec) - normalize(FragPos);

	gl_Position = u_MVPTrans * vec4(aPosition, 1.0f);

	TexCoord = aTexCoord;
}