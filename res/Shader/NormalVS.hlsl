/*
author : ���Ѻ�
description : �븻 ���͸� ǥ���ϱ� ���� ���ؽ� ����

version: 1.0.0
date: 2024-12-19
*/

#include "HBStd.hlsli"

NormalGSInput main(VSInput vsIn)
{
    NormalGSInput geoIn;

    geoIn.p = float4(vsIn.p, 1.f);
    geoIn.n = vsIn.n;
    geoIn.c = float4(0.f, 1.f, 0.f, 1.f);

    return geoIn;
}
