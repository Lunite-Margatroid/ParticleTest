#version 450 core

// 头指针缓存
uniform sampler2D head_pointer_image;

// 颜色混合缓存
uniform samplerBuffer list_buffer;

#define MAX_FRAGMENTS 15

// 用来暂存混合颜色的数组
uvec4 fragments[MAX_FRAGMENTS];

// 输出颜色
layout (location  =0) out vec4 output_color;


int build_local_fragment_list();
void sort_fragment_list(int frag_count);
vec4 calculate_final_color(int frag_count);

void main()
{
    int frag_count;
    
    // 遍历链表 把混合颜色存入数组fragments
    frag_count = build_local_fragment_list();
    
    // 按照深度顺序进行排序
    sort_fragment_list(frag_count);
    
    // 将数组中的颜色混合 得到最终颜色
    output_color = calculate_final_color(frag_count);
}

int build_local_fragment_list()
{
    uint current;
    int frag_count = 0;
    
    current = floatBitsToUint(texelFetch(head_pointer_image, ivec2(gl_FragCoord.xy), 0).r);
    
    while(current != 0xffffffff && frag_count < MAX_FRAGMENTS)
    {
        uvec4 item = floatBitsToUint(texelFetch(list_buffer, int(current)));
        current = item.x;	// next 指针
        fragments[frag_count] = item;
        frag_count ++;
    }
    return frag_count;
}

void sort_fragment_list(int frag_count)
{
    // 用最少的交换次数 '选择排序'可能更好一些？
    int iMax, i, j;
    for(i = 0; i < frag_count - 1;i++)
    {
        float depth_max, depth_j;
        depth_max = uintBitsToFloat(fragments[i].z);
        iMax = i;
        for(j = i+ 1;j<frag_count;j++)
        {
            depth_j = uintBitsToFloat(fragments[j].z);
            if(depth_j > depth_max)
            {
                iMax = j;
                depth_max =depth_j;
            }
        }
        uvec4 temp = fragments[iMax];
        fragments[iMax]  =fragments[i];
        fragments[i] = temp;
    }
}

vec4 calculate_final_color(int frag_count)
{
    vec4 final_color = vec4(0.0f);
    int i;
    for(i =0;i < frag_count;i++ )
    {
        vec4 frag_color = unpackUnorm4x8(fragments[i].y);
        final_color = mix(final_color, frag_color, frag_color.a);
    }
    return final_color;
}