#version 450 core

// 开启片元预测试
layout(early_fragment_tests) in;

in vec3 NormalVec;
in vec3 HalfVec;
in vec3 FragPos;		// 相机坐标系的顶点坐标
in vec2 TexCoord;

struct Material
{
	sampler2D DiffuseTex;
	vec2 DiffuseTexOffset;
	vec2 DiffuseTexScale;
	
	sampler2D SpecularTex;
	vec2 SpecularTexOffset;
	vec2 SpecularTexScale;
	
	sampler2D NormalTex;
	vec2 NormalTexOffset;
	vec2 NormalTexScale;
	
	sampler2D ParallaxTex;
	vec2 ParallaxTexOffset;
	vec2 ParallaxTexScale;
	
	float shininess;
};

uniform Material u_Material;

uniform vec4 u_Color;

out vec4 FragColor;

vec4 FragmentShader()
{
	vec2 texCoord = TexCoord / u_Material.DiffuseTexScale + u_Material.DiffuseTexOffset;
	return texture2D(u_Material.DiffuseTex, texCoord) * u_Color;
}



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