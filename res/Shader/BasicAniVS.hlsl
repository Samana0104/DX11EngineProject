/*
author : 변한빛
description : 애니메이션 전용 버텍스 쉐이더 파일

version: 1.0.0
date: 2024-11-17
*/

#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // 월드 행렬 역행렬 시키고 전치시킨거
    Matrix viewMat;
    Matrix projMat;
};

cbuffer AnimationMat : register(b1)
{
    matrix m_matBoneWorld[MAX_BONE_MAT];
};

PSInput main(AnimationInput vsIn)
{
    PSInput psIn = (PSInput) 0;
    
    float4 localPos = float4(vsIn.p.xyz, 1.f);
    float4 vAnimVertex = 0;
    float3 vAnimNormal = 0;

    //iNumWeight4 = 1.0f - w[0] + w[1] + w[2];
    for (uint bone1 = 0; bone1 < 4; bone1++)
    {
        uint iBoneIndex = vsIn.i1[bone1];
        float1 fWeight = vsIn.w1[bone1];
        Matrix matBone = m_matBoneWorld[iBoneIndex];

        vAnimVertex += mul(matBone, localPos) * fWeight;
        vAnimNormal += mul((float3x3) matBone, vsIn.n) * fWeight;
    }

    for (uint bone2 = 0; bone2 < 4; bone2++)
    {
        uint iBoneIndex = vsIn.i2[bone2];
        float1 fWeight = vsIn.w2[bone2];
        Matrix matBone = m_matBoneWorld[iBoneIndex];

        vAnimVertex += mul(matBone, localPos) * fWeight;
        vAnimNormal += mul((float3x3) matBone, vsIn.n) * fWeight;
    }

    float4 worldPos = mul(worldMat, vAnimVertex);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);

    float4 normal = mul(normalMat, float4(vsIn.n.xyz, 0));
    
    psIn.p = projPos;
    psIn.n = normalize(normal.xyz);
    psIn.c = vsIn.c;
    psIn.t = vsIn.t;
    return psIn;
}