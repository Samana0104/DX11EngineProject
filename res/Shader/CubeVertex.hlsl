/*
author : 변한빛
description : 큐브텍스쳐 전용으로 사용하기 위한 버텍스 쉐이더 파일

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

CubePSInput main(VSInput vsIn)
{
    CubePSInput psIn;

    float4 localPos = float4(vsIn.p.xyz, 1);

    float4 worldPos = mul(worldMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);
    
    psIn.worldPos = worldPos;
    psIn.projPos = projPos;

    return psIn;
}