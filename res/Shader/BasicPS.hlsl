/*
author : 변한빛
description : 기본적인 픽셀 쉐이더 파일 이미지 한장 출력이 가능하다.

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

cbuffer DefaultLight : register(b0)
{
    float3 lightDir;
    float1 lightPower;
    float3 eyePos;
    
};
    
cbuffer Material : register(b1)
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float shininess;
    float ambientFactor;
    float diffuseFactor;
    float specularFactor;
};

Texture2D g_txTexture : register(t0);
SamplerState sampler0 : register(s0);

float4 main(PSInput psIn) : SV_Target0
{
    float3 eyeDir = psIn.worldP

    float4 outputPixel;
    float4 pixel = g_txTexture.Sample(sampler0, psIn.t);

    BlinnInfo info = 0;
    info.ambientColor = ambient;
    info.diffuseColor = diffuse;
    info.specularColor = specular;
    info.shininess = shininess;
    info.ambientFactor = ambientFactor;
    info.diffuseFactor = diffuseFactor;
    info.specularFactor = specularFactor;

    outputPixel = pixel * psIn.c;
 
    return outputPixel;
}