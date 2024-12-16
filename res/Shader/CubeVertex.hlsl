/*
author : 변한빛
description : 큐브텍스쳐 전용으로 사용하기 위한 버텍스 쉐이더 파일

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // 월드 행렬 역행렬 시키고 전치시킨거
    Matrix viewMat;
    Matrix projMat;
};

CubePSInput main(VSInput vsIn)
{
    CubePSInput psIn;

    float4 localPos = float4(vsIn.p.xyz, 1);

    float4 worldPos = mul(worldMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);
    
    psIn.worldPos = worldPos.xyz;
    psIn.projPos = projPos;

    return psIn;
}