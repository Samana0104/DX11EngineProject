/*
author : 변한빛
description : 
    컬러값만 있는 메쉬의 픽셀을 출력하기 위한
    픽셀 쉐이더 파일

version: 1.0.4
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

float4 main(PSInput psIn) : SV_Target0
{
    float3 eyeDir = psIn.worldPos - eyePos;
    float4 outputPixel;

    BlinnInfo info;
    info.ambientColor = ambient.xyz;
    info.diffuseColor = diffuse.xyz;
    info.specularColor = specular.xyz;
    info.shininess = shininess;
    info.ambientFactor = ambientFactor;
    info.diffuseFactor = diffuseFactor;
    info.specularFactor = specularFactor;

    float4 lightColor = float4(ComputeBlinnPhong(lightDir, psIn.n, eyeDir, info), 1.f);
    outputPixel = psIn.c * lightColor;
    outputPixel = float4(outputPixel.rgb * lightPower, outputPixel.a);
 
    return outputPixel;
}