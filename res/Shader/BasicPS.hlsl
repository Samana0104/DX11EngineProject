/*
author : 변한빛
description : 기본적인 픽셀 쉐이더 파일 이미지 한장 출력이 가능하다.

version: 1.0.0
date: 2024-11-17
*/

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