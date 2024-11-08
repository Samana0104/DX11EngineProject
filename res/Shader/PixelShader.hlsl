#include "HBStd.hlsli"
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)
Texture2D g_txTexture : register(t0);
SamplerState sampler0 : register(s0);

float4 main(PSInput psIn) : SV_Target
{
    float4 outputPixel = 0;
    float4 pixel = g_txTexture.Sample(sampler0, psIn.t);
    outputPixel = pixel * psIn.c;
 
    return outputPixel;
}