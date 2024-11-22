/*
author : 변한빛
description : 
    라인의 정점 변환을 위한 버텍스 파일
    invMat이 없는게 특징

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

LinePsInput main(VSInput vsIn)
{
    LinePsInput psIn = (LinePsInput) 0;

    float4 localPos = float4(vsIn.p.xyz, 1);
    float4 worldPos = mul(worldMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);
    
    psIn.p = projPos;
    psIn.c = vsIn.c;

    return psIn;
}