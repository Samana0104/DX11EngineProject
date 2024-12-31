/*
Author: ���Ѻ� & ������
Description: ���� ���ؽ� ���̴� - ȯ�� ���� �� ī�� ������ ����
Version: 1.0.0
*/

#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // ���� ��� ����� �� ��ġ
    Matrix viewMat;
    Matrix projMat;
};

PSInput main(VSInput vsIn)
{
    PSInput psIn = (PSInput) 0;

    float4 localPos = float4(vsIn.p, 1);
    float4 worldPos = mul(worldMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);

    float4 normal = mul(normalMat, float4(vsIn.n, 0));

    psIn.p = projPos;
    psIn.n = normalize(normal.xyz);
    psIn.c = vsIn.c; // ���ؽ� �÷� ����
    psIn.t = vsIn.t;
    psIn.worldPos = worldPos.xyz;

    return psIn;
}
