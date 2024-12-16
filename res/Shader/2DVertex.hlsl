/*
author : ���Ѻ�
description : �⺻���� 2D ���ؽ� ���̴� ���� �⺻���� ��ȯ�� �����Ѵ�.

version: 1.0.0
date: 2024-11-30
*/

#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // ���� ��� ����� ��Ű�� ��ġ��Ų��
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

