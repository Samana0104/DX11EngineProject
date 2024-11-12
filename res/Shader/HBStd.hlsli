#ifndef __HBSTD_HLSLI__
#define __HBSTD_HLSLI__

struct VSInput
{
    float3 p : POSITION0;
    float3 n : NORMAL;
    float4 c : COLOR;
    float2 t : TEXCOORD0;
};

struct PSInput
{
    float4 p : SV_Position;
    float4 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
};

#endif