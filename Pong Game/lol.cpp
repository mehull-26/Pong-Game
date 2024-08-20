// Input structure for pixel shader
struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
};

// Light structure and uniform buffer
cbuffer LightBuffer : register(b0)
{
    float intensity;
    float3 lightColor;
    float3 points[4];
};

// Material structure and uniform buffer
cbuffer MaterialBuffer : register(b1)
{
    float3 diffuse;
    float3 specular;
    float roughness;
};

// Camera position and additional uniform data
cbuffer CameraAndFlags : register(b2)
{
    float3 cameraPos;
    bool twoSided;
};

// Samplers and textures
SamplerState samplerState : register(s0);
Texture2D LTC1 : register(t0);
Texture2D LTC2 : register(t1);

// Constants for LUT size and scaling
const float LUT_SIZE = 64.0;
const float LUT_SCALE = 63.0f / 64.0f;
const float LUT_BIAS = 0.5f / 64.0f;

// Function for edge integration
float3 IntegrateEdgefloat(float3 v1, float3 v2)
{
    float x = dot(v1, v2);
    float y = abs(x);

    float a = 0.8543985 + (0.4965155 + 0.0145206 * y) * y;
    float b = 3.4175940 + (4.1616724 + y) * y;
    float v = a / b;

    float theta_sintheta = (x > 0.0) ? v : 0.5 * rsqrt(max(1.0 - x * x, 1e-7)) - v;

    return cross(v1, v2) * theta_sintheta;
}

float IntegrateEdge(float3 v1, float3 v2)
{
    return IntegrateEdgefloat(v1, v2).z;
}

// Evaluate LTC shading
float3 LTC_Evaluate(float3 N, float3 V, float3 P, float3x3 Minv, float3 points[4], bool twoSided)
{
    float3 T1 = normalize(V - N * dot(V, N));
    float3 T2 = cross(N, T1);

    Minv = Minv * transpose(float3x3(T1, T2, N));

    float3 L[4];
    L[0] = mul(Minv, (points[0] - P));
    L[1] = mul(Minv, (points[1] - P));
    L[2] = mul(Minv, (points[2] - P));
    L[3] = mul(Minv, (points[3] - P));

    float sum = 0.0;

    float3 dir = points[0] - P;
    float3 lightNormal = cross(points[1] - points[0], points[3] - points[0]);
    bool behind = (dot(dir, lightNormal) < 0.0);

    L[0] = normalize(L[0]);
    L[1] = normalize(L[1]);
    L[2] = normalize(L[2]);
    L[3] = normalize(L[3]);

    float3 vsum = float3(0.0);

    vsum += IntegrateEdgefloat(L[0], L[1]);
    vsum += IntegrateEdgefloat(L[1], L[2]);
    vsum += IntegrateEdgefloat(L[2], L[3]);
    vsum += IntegrateEdgefloat(L[3], L[0]);

    float len = length(vsum);
    float z = vsum.z / len;

    if (behind)
        z = -z;

    float2 uv = float2(z * 0.5 + 0.5, len);
    uv = uv * LUT_SCALE + LUT_BIAS;

    float scale = LTC2.Sample(samplerState, uv).w;

    sum = len * scale;

    if (!behind && !twoSided)
        sum = 0.0;

    float3 Lo_i = float3(sum, sum, sum);

    return Lo_i;
}

// Gamma correction function
float3 Powfloat3(float3 v, float p)
{
    return float3(pow(v.x, p), pow(v.y, p), pow(v.z, p));
}

const float gamma = 2.2;
float3 ToLinear(float3 v)
{
    return Powfloat3(v, gamma);
}

// Pixel shader main function
float4 main(PixelInputType fs_in) : SV_TARGET
{
    float3 mDiffuse = ToLinear(diffuse);
    float3 mSpecular = ToLinear(specular);

    float3 result = float3(0.0);

    float3 N = normalize(fs_in.normal);
    float3 V = normalize(cameraPos - fs_in.position.xyz);
    float NdotV = clamp(dot(N, V), 0.0, 1.0);

    float2 uv = float2(roughness, sqrt(1.0 - NdotV));
    uv = uv * LUT_SCALE + LUT_BIAS;

    float4 t1 = LTC1.Sample(samplerState, uv);
    float4 t2 = LTC2.Sample(samplerState, uv);

    float3x3 Minv = float3x3(
        float3(t1.x, 0, t1.y),
        float3(0, 1, 0),
        float3(t1.z, 0, t1.w)
    );
    float3x3 identityMatrix = float3x3
    (
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    );
    float3 diffuse = LTC_Evaluate(N, V, fs_in.position.xyz, identityMatrix, points, twoSided);
    float3 specular = LTC_Evaluate(N, V, fs_in.position.xyz, Minv, points, twoSided);

    specular *= mSpecular * t2.x + (1.0 - mSpecular) * t2.y;

    result = intensity * lightColor * (specular + mDiffuse * diffuse);

    return float4(result, 1.0);
}
