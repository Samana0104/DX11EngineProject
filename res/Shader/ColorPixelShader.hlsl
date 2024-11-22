/*
author : 변한빛
description : 
    컬러값만 있는 메쉬의 픽셀을 출력하기 위한
    픽셀 쉐이더 파일

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

float4 main(PSInput psIn) : SV_Target0
{
    return psIn.c;
}