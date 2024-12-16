/*
author : 변한빛
description : 렌더타겟을 합성시키기 위한 픽셀 쉐이더 파일

version: 1.0.0
date: 2024-12-16
*/

#include "HBStd.hlsli"

float4 main(LinePsInput vsIn) : SV_Target0
{
    return vsIn.c;
}