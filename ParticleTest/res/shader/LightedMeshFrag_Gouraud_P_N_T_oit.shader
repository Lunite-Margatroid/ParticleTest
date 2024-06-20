#version 450 core

in vec3 Ambient;
in vec3 Diffuse;
in vec3 Specular;
in vec2 TexCoord;

out vec4 FragColor;

// 材质系统
struct Material
{
	sampler2D DiffuseTex;
	vec2 DiffuseTexOffset;
	vec2 DiffuseTexScale;
	float DiffuseTexWeight;
	
	sampler2D SpecularTex;
	vec2 SpecularTexOffset;
	vec2 SpecularTexScale;
	float SpecularTexWeight;
	
	sampler2D NormalTex;
	vec2 NormalTexOffset;
	vec2 NormalTexScale;
	float NormalTexWeight;
	
	sampler2D ParallaxTex;
	vec2 ParallaxTexOffset;
	vec2 ParallaxTexScale;
	float ParallaxTexWeight;
	
	float shininess;
};

uniform Material u_Material;
uniform vec4 u_Color;


vec4 FragmentShader()
{
	// 纹理颜色
	vec2 texCoord = TexCoord / u_Material.DiffuseTexScale + u_Material.DiffuseTexOffset;
	vec2 specularTexCoord = TexCoord / u_Material.SpecularTexScale + u_Material.SpecularTexOffset;
	
	vec4 diffuseTexColor = texture2D(u_Material.DiffuseTex, texCoord);
	diffuseTexColor = diffuseTexColor * u_Material.DiffuseTexWeight;
	
	vec4 specularTexColor = texture2D(u_Material.SpecularTex, specularTexCoord);
	specularTexColor = specularTexColor * u_Material.SpecularTexWeight;
	
	return (
			diffuseTexColor * vec4((Ambient + Diffuse),1.0f)
			+ specularTexColor * vec4(Specular, 1.0f)
			)
			* u_Color;

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