#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec2 aTangent;

uniform mat4 u_MVPTrans;
uniform mat3 u_NormalTrans;
uniform mat4 u_MVTrans;
uniform mat4 u_VTrans;
uniform mat4 u_MTrans;
uniform vec3 u_CameraPos;

out vec3 NormalVec;		// 世界坐标法向量
out vec3 FragPos;		// 世界坐标系的顶点坐标
out vec3 ViewVec;

out vec2 TexCoord;
out mat3 InverseLocalTrans;

void main()
{
	FragPos = vec3(u_MTrans * vec4(aPosition, 1.0f));
	NormalVec = normalize(u_NormalTrans * aPosition);
	
	ViewVec = normalize(u_CameraPos - FragPos);
	
	gl_Position = u_MVPTrans * vec4(aPosition, 1.0f);
	
	TexCoord = aTexCoord;
	
	vec3 tangentVec = normalize(u_NormalTrans * vec3(aTangent.x, 0.0f, aTangent.y));
	mat3 localTrans = transpose(mat3(tangentVec, cross(NormalVec, tangentVec), NormalVec));
	InverseLocalTrans = inverse(localTrans);
}