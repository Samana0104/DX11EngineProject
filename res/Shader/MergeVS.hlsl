/*
author : ���Ѻ�
description : ����Ÿ���� �ռ���Ű�� ���� ���ؽ� ���̴� ����

version: 1.0.0
date: 2024-12-16
*/

#include "HBStd.hlsli"

ImagePSInput main(VSInput vsIn)
{
    ImagePSInput psIn = (ImagePSInput) 0;

    psIn.p = float4(vsIn.p.xyz, 1.f);
    psIn.c = vsIn.c;
    psIn.t = vsIn.t;
    return psIn;
}