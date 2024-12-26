/*
author : 변한빛
description : 기본적인 픽셀 쉐이더 파일 이미지 한장 출력이 가능하다.

version: 1.0.3
date: 2024-12-26
*/

#include "HBStd.hlsli"

cbuffer DefaultLight : register(b0)
{
    float3 lightDir;
    float1 lightPower;
    float3 eyePos;
    float1 dummy;
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
    float3 eyeDir = psIn.worldPos - eyePos;
    float4 outputPixel;
    float4 pixel = g_txTexture.Sample(sampler0, psIn.t);

    BlinnInfo info;
    info.ambientColor = ambient.xyz;
    info.diffuseColor = diffuse.xyz;
    info.specularColor = specular.xyz;
    info.shininess = shininess;
    info.ambientFactor = ambientFactor;
    info.diffuseFactor = diffuseFactor;
    info.specularFactor = specularFactor;

    float4 lightColor = float4(ComputeBlinnPhong(lightDir, psIn.n, eyeDir, info), 1.f);
    outputPixel = pixel * psIn.c * lightColor;
    outputPixel = float4(outputPixel.rgb * lightPower, outputPixel.a);
 
    return outputPixel;
}