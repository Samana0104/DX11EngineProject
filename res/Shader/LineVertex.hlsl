/*
author : ���Ѻ�
description : 
    ������ ���� ��ȯ�� ���� ���ؽ� ����
    invMat�� ���°� Ư¡

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