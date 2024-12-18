#include "HBStd.hlsli"

cbuffer DefaultMat3D : register(b0)
{
    Matrix worldMat;
    Matrix normalMat; // 월드 행렬 역행렬 시키고 전치시킨거
    Matrix viewMat;
    Matrix projMat;
};

[maxvertexcount(2)]
void main(point NormalGeoInput input[1], uint primID : SV_PrimitiveID,
                              inout LineStream<LinePsInput> outputStream)
{
    float4 worldPos;
    float4 viewPos;
    float4 projPos;
    float4 normalWorld;
    LinePsInput psIn;
    
    normalWorld = mul(normalMat, float4(input[0].n, 0.f));
    normalWorld = normalize(normalWorld);

    worldPos = mul(worldMat, input[0].p);
    viewPos = mul(viewMat, worldPos);
    projPos = mul(projMat, viewPos);
    psIn.p = projPos;
    psIn.c = input[0].c;

    outputStream.Append(psIn);

    viewPos = mul(viewMat, normalWorld * 5.f + worldPos);
    projPos = mul(projMat, viewPos);
    psIn.p = projPos;
    psIn.c = input[0].c;

    outputStream.Append(psIn);

    outputStream.RestartStrip();
}

