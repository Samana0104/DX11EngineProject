/*
author : 변한빛
description : 
    노말 벡터 표시하기 위한 버텍스 파일

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

NormalGeoInput main(VSInput vsIn)
{
    NormalGeoInput geoIn;

    geoIn.p = float4(vsIn.p, 1.f);
    geoIn.n = vsIn.n;
    geoIn.c = float4(1.f, 1.f, 1.f, 1.f);

    return geoIn;
}
