/*
author : ���Ѻ�
description : ť���ؽ��� �������� ����ϱ� ���� ���ؽ� ���̴� ����

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