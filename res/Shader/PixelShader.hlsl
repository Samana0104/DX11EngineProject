#include "HBStd.hlsli"
Texture2D g_txTexture : register(t0);
SamplerState sampler0 : register(s0);

float4 main(PSInput psIn) : SV_Target0
{
    float4 outputPixel;
    float4 pixel = g_txTexture.Sample(sampler0, psIn.t);
    outputPixel = pixel * psIn.c;
 
    return outputPixel;
}