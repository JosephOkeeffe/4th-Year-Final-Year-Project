float4 main(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}


// Vertex shader
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

VS_OUTPUT vs_main(float4 position : POSITION, float2 texcoord : TEXCOORD0)
{
    VS_OUTPUT output;
    output.position = position;
    output.texcoord = texcoord;
    return output;
}

// Pixel shader
float4 ps_main(float2 texcoord : TEXCOORD0, sampler2D textureSampler : register(s0)) : SV_TARGET
{
    float4 color = tex2D(textureSampler, texcoord);
    color.r = 0.0;
    color.g = 0.0;
    color.b = 1.0;
    return color;
}

