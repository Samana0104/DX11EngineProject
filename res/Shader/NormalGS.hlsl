/*
author : ���Ѻ�
description : �븻���͸� ����ϱ� ���� ���Ͻ��̴� ����

version: 1.0.0
date: 2024-12-19
*/

#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // ���� ��� ����� ��Ű�� ��ġ��Ų��
    Matrix viewMat;
    Matrix projMat;
};

[maxvertexcount(2)]
void main(point NormalGSInput input[1], uint primID : SV_PrimitiveID,
                              inout LineStream<LinePsInput> outputStream)
{
    float4 worldPos;
    float4 viewPos;
    float4 projPos;
    float4 normalWorld;
    float4 test;
    LinePsInput psIn;

    worldPos = mul(worldMat, input[0].p);
    viewPos = mul(viewMat, worldPos);
    projPos = mul(projMat, viewPos);
    psIn.p = projPos;
    psIn.c = input[0].c;

    outputStream.Append(psIn);

    normalWorld = mul(normalMat, float4(input[0].n, 0.f));
    normalWorld = float4(normalize(normalWorld.xyz), 0.f);
    viewPos = mul(viewMat, normalWorld * 0.1f + worldPos);
    projPos = mul(projMat, viewPos);
    psIn.p = projPos;
    psIn.c = input[0].c;

    outputStream.Append(psIn);

    outputStream.RestartStrip();
}

