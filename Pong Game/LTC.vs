cbuffer MatrixBuffer
{
    matrix world;
    matrix view;
    matrix projection;
};

struct VertexInputType
{
    float4 position : POSITION;
    float3 normal : NORMAL;

};

// world space
struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 WorldPos : POSITION;
    float3 normal : NORMAL;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    input.position.w = 1.0f;
    
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    output.normal = mul(input.normal, (float3x3)world);
    output.normal = normalize(output.normal);
    
    output.WorldPos = input.position.xyz;
    
    return output;
}