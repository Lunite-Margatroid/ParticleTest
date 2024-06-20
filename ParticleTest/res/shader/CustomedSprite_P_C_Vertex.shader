#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 u_MVPTrans;

uniform mat4 u_MVTrans;
uniform float u_VertexSize;	// 顶点大小
uniform float u_Far;		// 远平面的距离



out vec4 Color;

void main()
{
	Color = aColor;
	
	vec4 pos = u_MVPTrans * vec4(aPos, 1.0f);
	vec4 viewPos = u_MVTrans * vec4(aPos, 1.0f);
	
	//if (viewPos.z < 0)
		gl_PointSize = max((1.0f - abs(viewPos.z / u_Far)) * u_VertexSize, 1.0f);
		
	gl_Position = pos;
}