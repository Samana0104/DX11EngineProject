/*
author : 변한빛
description : 애니메이션 노말벡터를 출력하기 위한 버텍스 쉐이더 파일

version: 1.0.0
date: 2024-12-19
*/

#include "HBStd.hlsli"

cbuffer AnimationMat : register(b0)
{
    matrix m_matBoneWorld[MAX_BONE_MAT];
};

NormalGeoInput main(AnimationInput vsIn)
{
    NormalGeoInput gsIn;
    
    float4 localPos = float4(vsIn.p.xyz, 1.f);
    float4 vAnimVertex = 0;
    float3 vAnimNormal = 0;

    for (uint bone1 = 0; bone1 < 4; bone1++)
    {
        uint iBoneIndex = vsIn.i1[bone1];
        float1 fWeight = vsIn.w1[bone1];
        float4x4 matBone = m_matBoneWorld[iBoneIndex];

        vAnimVertex += mul(matBone, localPos) * fWeight;
        vAnimNormal += normalize(mul((float3x3) matBone, vsIn.n) * fWeight);

    }

    for (uint bone2 = 0; bone2 < 4; bone2++)
    {
        uint iBoneIndex = vsIn.i2[bone2];
        float1 fWeight = vsIn.w2[bone2];
        Matrix matBone = m_matBoneWorld[iBoneIndex];

        vAnimVertex += mul(matBone, localPos) * fWeight;
        vAnimNormal += normalize(mul((float3x3) matBone, vsIn.n) * fWeight);

    }

    gsIn.p = float4(vAnimVertex.xyz, 1.f);
    gsIn.n = normalize(vAnimNormal);
    gsIn.c = float4(1.f, 0.f, 0.f, 1.f);
    return gsIn;
}
