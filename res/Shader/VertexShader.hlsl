/*
author : 변한빛, 이지혁
description(변한빛) : 기본적인 버텍스 쉐이더 파일 기본적인 변환만 수행한다.
description(이지혁) : 버텍스 노말값을 기준으로 한 조명 연산 코드 추가.

version: 1.0.1
date: 2024-12-10
*/

#include "HBStd.hlsli"

PSInput main(VSInput vsIn)
{
    PSInput psIn = (PSInput) 0;

    float4 localPos = float4(vsIn.p.xyz, 1);

    float4 worldPos = mul(worldMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);

    float4 normal = mul(normalMat, float4(vsIn.n.xyz, 0));
    
    psIn.p = projPos;
    psIn.n = normal;
    psIn.c = vsIn.c;
    psIn.t = vsIn.t;

    
    
    float fDotDirection = dot(vsIn.n, -g_vLightDir.xyz);
    float3 vDir = normalize(g_vLightPos.xyz - worldPos.xyz);
    float fDot = dot(vsIn.n, vDir);
    
    float fDistance = distance(worldPos.xyz, g_vLightPos.xyz);
    fDistance /= g_vDistance;
    fDistance = 1.0f - min(fDistance, 1.0f);
    
    float4 fAmbientColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    psIn.c = fAmbientColor + float4(fDotDirection, fDotDirection, fDotDirection, 1.0f) +
		float4(1.0f * fDistance * fDot, 0.0f * fDistance * fDot, 0.0f * fDistance * fDot, 1.0f);
    
    return psIn;
}