/*
author : 변한빛
description : 기본적인 2D 버텍스 쉐이더 파일 기본적인 변환만 수행한다.

version: 1.0.0
date: 2024-11-30
*/

#include "HBStd.hlsli"

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

