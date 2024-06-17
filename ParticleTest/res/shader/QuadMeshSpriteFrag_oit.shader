#version 450 core

in vec2 TexCoord;

uniform vec4 u_MeshColor;

out vec4 FragColor;

float fuzz = 0.03f;
const float c_fuzz = 0.03f;


float CoordToStrength(float u)
{
	
	u = fract(u);
	float frac1 = clamp((1.0f - u) / fuzz, 0.0f, 1.0f);
	float frac2  =clamp(u / fuzz, 0.0f, 1.0f);
	frac1 = frac1 < frac2? frac1 : frac2;
	frac1 = frac1 * frac1 * (3.0f - 2.0f * frac1);
	return 1.0f - frac1;
	
}

float CoordToStrength2D(float u, float v)
{
	u = CoordToStrength(u);
	v = CoordToStrength(v);
	return max(u, v);
}


vec4 FragmentShader()
{
//float samRate = abs(dot(normalize(FragCoord),NormalVec));
	//samRate = samRate * 0.99f + 0.01f;

	vec2 pw = fwidth(TexCoord);
	fuzz = clamp(max(pw.s, pw.t) * 2, c_fuzz, 1.0f);
	
	float lightRate = c_fuzz / fuzz;
	
	lightRate = 1.1f * lightRate / (0.1f + lightRate);
	lightRate = lightRate * 0.9f + 0.1f;
	float u = TexCoord.x;
	float v = TexCoord.y;
	float sum = CoordToStrength2D(u,v);
	
	vec3 temp = vec3(u_MeshColor);
	
	vec4 color = mix(
		vec4(temp, 0.0f),
		u_MeshColor,
		sum
	) * lightRate;
	
	//FragColor = vec4(1.0f ,1.0f, 1.0f ,1.0f);
	return color;
}


/*---------------OIT--------------------*/

// 开启片元预测试
layout(early_fragment_tests) in;


// 原子计数器
layout (binding = 0, offset = 0) uniform atomic_uint u_AtomicCounter;

// 颜色混合缓存
layout (binding = 0, rgba32ui) uniform uimageBuffer u_ListBuffer;

// 头指针缓存
layout (binding = 1, r32ui) uniform uimage2D u_HeadMat;

void main()
{
    if (gl_SampleID > 0)
        discard;

	// 绘制 获取片元颜色
    vec4 fragColor = FragmentShader();
    // 申请空间 即原子计数器+1
    uint newHead = atomicCounterIncrement(u_AtomicCounter);
    
    // 将新申请的空间作为新的头指针写入头指针缓存
    // 并返回原来的头指针
    uint oldHead =
		imageAtomicExchange(u_HeadMat, ivec2(gl_FragCoord.xy), newHead);
    
    // 初始化新头节点的数据
    uvec4 item;
    item.x = oldHead;	// next 指针
    item.y = packUnorm4x8(fragColor);	// 32位深 4通道颜色
    item.z = floatBitsToUint(gl_FragCoord.z);	// 深度
    item.w = 0;			// 预留  多重采样混合
    
    // 将节点数据写入头节点 index
    imageStore(u_ListBuffer, int(newHead), item);
}