/*
author : 변한빛, 이지혁
description : 모든 인풋 아웃풋을 정의하기 위한 쉐이더 인클루드 파일

version: 1.0.3
date: 2024-12-24
*/

#ifndef __HBSTD_HLSLI__
#define __HBSTD_HLSLI__

#define MAX_BONE_MAT 255

/*
---------------------------
        Shader Input
---------------------------
*/

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
    float3 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
    float3 worldPos : POSITION;
};

struct LinePsInput
{
    float4 p : SV_Position;
    float4 c : COLOR0;
};

struct CubePSInput
{
    float4 projPos : SV_Position;
    float3 worldPos : POSITION;
};

struct NormalGSInput
{
    float4 p : SV_Position;
    float3 n : NORMAL;
    float4 c : COLOR0;
};

struct ImagePSInput
{
    float4 p : SV_Position;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
};

struct AnimationInput
{
    float3 p : POSITION0;
    float3 n : NORMAL0;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
    uint4 i1 : BLENDINDICES0;
    uint4 i2 : BLENDINDICES1;
    float4 w1 : BLENDWEIGHT0;
    float4 w2 : BLENDWEIGHT1;
};

struct BlinnInfo
{
    float3 ambientColor;
    float3 diffuseColor;
    float3 specularColor;
    float1 ambientFactor;
    float1 diffuseFactor;
    float1 specularFactor;
    float1 shininess;
};

/*
---------------------------
        Shader API
---------------------------
*/

/*
param : lightDir -> 빛의 방향(물체를 향하는 방향)
        eye -> 시야 방향(물체를 향하는 방향)
description :
   블린 퐁 모델 계산함
*/
float3 ComputeBlinnPhong(float3 lightDir, float3 normal, float3 eyeDir, BlinnInfo info)
{
    float lDotN = saturate(dot(-lightDir, normal));
    float3 halfVector = normalize(-eyeDir + -lightDir);
    float hDotN = saturate(dot(halfVector, normal));
    float specularPower = pow(hDotN, info.shininess);
    
    float3 color = saturate(info.ambientColor * info.ambientFactor
    + info.diffuseColor * info.diffuseFactor * lDotN
    + info.specularColor * info.specularFactor * specularPower);

    return color;
}
#endif