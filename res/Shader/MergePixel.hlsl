/*
author : ���Ѻ�
description : ����Ÿ���� �ռ���Ű�� ���� �ȼ� ���̴� ����

version: 1.0.0
date: 2024-12-16
*/

#include "HBStd.hlsli"

Texture2D g_txTexture : register(t0);
SamplerState sampler0 : register(s0);

float4 main(ImagePSInput psIn) : SV_Target0
{
    float4 pixel = g_txTexture.Sample(sampler0, psIn.t);

    return pixel;
}