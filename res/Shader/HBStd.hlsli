/*
author : 변한빛, 이지혁
description(변한빛) : 모든 인풋 아웃풋을 정의하기 위한 쉐이더 인클루드 파일
description(이지혁) : 기본 상수 버퍼에 조명 연산을 위한 변수 추가

version: 1.0.4
date: 2024-12-10
*/

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

/*
-------------------------------
        Constant Buffers
-------------------------------
*/
cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // 월드 행렬 역행렬 시키고 전치시킨거
    Matrix viewMat;
    Matrix projMat;
    
    //float3 g_vLightDir : packoffset(c0);
    //float1 g_vDistance : packoffset(c0.w);
    //float3 g_vLightPos : packoffset(c1);
    //float1 g_vRadius : packoffset(c1.w);
    
    float3 g_vLightDir;
    float1 g_vDistance;
    float3 g_vLightPos;
    float1 g_vRadius;
};

//cbuffer DiffuseLight : register(b1) // 조명 연산 버퍼
//{
//    float3 g_vLightDir : packoffset(c0);
//    float1 g_vDistance : packoffset(c0.w);
//    float3 g_vLightPos : packoffset(c1);
//    float1 g_vRadius : packoffset(c1.w);
//};
#endif