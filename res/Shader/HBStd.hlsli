/*
author : ���Ѻ�
description : ��� ��ǲ �ƿ�ǲ�� �����ϱ� ���� ���̴� ��Ŭ��� ����

version: 1.0.3
date: 2024-11-30
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

struct NormalGeoInput
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

#endif