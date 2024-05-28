#version 450 core
layout (location = 0) in vec3 aPosition;

out vec4 VertexColor;

uniform mat4 u_MVPTrans;

vec3 X_InstanceTrans(vec3 pos)
{
	return pos;
}

vec3 Y_InstanceTrans(vec3 pos)
{
	// 绕z轴90
	/*
	0	-1	0		x		-y
	1	0	0		y	=	x
	0	0	1		z		z
	*/
	return vec3(-pos.y, pos.x, pos.z);
}

vec3 Z_InstanceTrans(vec3 pos)
{
	// 绕y轴-90
	/*
	0	0	-1		x		-z
	0	1	0		y	=	y
	1	0	0		z		x
	*/
	return vec3(-pos.z, pos.y, pos.x);
}

void main()
{
	if(gl_InstanceID == 0)
	{
		gl_Position = u_MVPTrans * vec4(X_InstanceTrans(aPosition), 1.0f);
		VertexColor = vec4(1.0f, 0.0f, 0.0f, 0.6f);
		return;
	}
	
	if(gl_InstanceID == 1)
	{
		gl_Position = u_MVPTrans * vec4(Y_InstanceTrans(aPosition), 1.0f);
		VertexColor = vec4(0.0f, 1.0f, 0.0f, 0.6f);
		return;
	}


	if(gl_InstanceID == 2)
	{
		gl_Position = u_MVPTrans * vec4(Z_InstanceTrans(aPosition), 1.0f);
		VertexColor = vec4(0.0f, 0.0f, 1.0f, 0.6f);
		return;
	}
	
	gl_Position = u_MVPTrans * vec4(aPosition, 1.0f);
		VertexColor = vec4(1.0f, 1.0f, 1.0f, 0.6f);
}