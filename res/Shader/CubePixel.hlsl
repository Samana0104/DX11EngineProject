#include "HBStd.hlsli"

TextureCube g_textureCube0 : register(t0);
SamplerState g_sampler : register(s0);

float4 main(CubePSInput psIn) : SV_Target0
{
    float4 output;
    output = g_textureCube0.Sample(g_sampler, psIn.worldPos.xyz);
    
    return output;
}