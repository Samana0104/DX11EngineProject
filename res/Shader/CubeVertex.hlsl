/*
author : ���Ѻ�
description : ť���ؽ��� �������� ����ϱ� ���� ���ؽ� ���̴� ����

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // ���� ��� ����� ��Ű�� ��ġ��Ų��
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