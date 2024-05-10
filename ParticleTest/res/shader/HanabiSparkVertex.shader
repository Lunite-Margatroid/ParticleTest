#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aVel;
layout(location = 2) in float aTime;

struct ParticleVertex
{
	vec4 uPosTime;
	vec3 uVel;
};

// 父级粒子的顶点属性
layout(std140, binding = 0 )buffer UnifVertexAtttib
{
	ParticleVertex particles[];
};

// transform feedback
out vec3 out_Pos;
out vec3 out_Vel;
out float out_T;

// uniform
uniform mat4 u_MVPTrans;
uniform mat4 u_MVTrans;
uniform float u_AverageVel;	// 初速度的平均
uniform float u_VelSD;		// 初速的标准差
uniform float u_AverageTime;// 存在时间的平均
uniform float u_TimeSD;		// 存在时间的标准差
uniform int u_Count;		// 每一个父粒子数量
uniform float u_Far;		// 远平面的距离
uniform float u_kDF;		// 阻力系数
uniform float u_VertexSize;	// 顶点大小
uniform float u_DeltaTime;	// 帧时间
uniform vec3 u_Accelerate;	// 重力加速度

// out to Fragment shader
out float ExistTime;

//void GenVertex();
//void Update();
//float FloatToRandFloat(float value);
//float FloatToGaussianRand(float value, float average, float sd);


// 生成[0 , 1]的随机数
float FloatToRandFloat(float value)
{
	float random = fract(sin(value + 432.3115) * 12985.3214);
	return random;
}

float FloatToGaussianRand(float value, float average, float sd)
{
	float random = fract(sin(value + 432.3115) * 12985.3214);
	random = random * 2 -1;
	return 2 * pow(random, 3) * sd + average;	// 三次函数近似 正态分布 cdf
}



void main()
{
	if(aTime <= 0)
	{// Gen new vertex
		int ind  = gl_VertexID % u_Count;
		vec4 posAndTime = particles[ind].uPosTime;
		if(posAndTime.w > 0.0f)
		{
			out_Pos = posAndTime.xyz;
			
			vec3 vel;
			float u = FloatToRandFloat(float(gl_VertexID)) * 2 - 1;
			float theta = FloatToRandFloat(float(gl_VertexID)) * 2 * 3.14159f;
			vel.z = u;
			u = sqrt(1 -u * u);
			vel.x = u * cos(theta);
			vel.y = u * sin(theta);
			out_T = FloatToGaussianRand(u,u_AverageTime ,u_TimeSD);
			float velocity = FloatToGaussianRand(out_T, u_AverageVel, u_VelSD);
			out_Vel = particles[ind].uVel + vel * velocity;
			//out_Vel = out_Vel * 0.0f;
			
		}
		else
		{
			out_Vel = vec3(0.0f,0.0f, 0.0f);
			out_Pos = vec3(0.0f);
			out_T = 0.0f;
		}
	}
	else
	{
		// update
		vec3 dragVel = abs(aVel) * aVel * u_kDF;
		out_Vel = aVel  + (u_Accelerate - dragVel) * u_DeltaTime; 
		out_T = aTime - u_DeltaTime;
		out_Pos = aPos + aVel * u_DeltaTime;
	}
	
	
	vec4 pos = u_MVPTrans * vec4(aPos, 1.0f);
	vec4 viewPos = u_MVTrans * vec4(aPos, 1.0f);
	ExistTime = aTime;
	
	if (viewPos.z < 0)
	{
		gl_PointSize = max((1.0f + viewPos.z / u_Far) * u_VertexSize, 1.0f);
	}
	gl_Position = pos;
}

