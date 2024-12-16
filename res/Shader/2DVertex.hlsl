/*
author : 변한빛
description : 기본적인 2D 버텍스 쉐이더 파일 기본적인 변환만 수행한다.

version: 1.0.0
date: 2024-11-30
*/

#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // 월드 행렬 역행렬 시키고 전치시킨거
    Matrix viewMat;
    Matrix projMat;
};

PSInput main(VSInput vsIn)
{
    PSInput psIn = (PSInput) 0;

    float4 localPos = float4(vsIn.p.xy, 1, 1);

    float4 worldPos = mul(worldMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);

    psIn.p = viewPos;
    psIn.c = vsIn.c;
    psIn.t = vsIn.t;

    return psIn;
}

