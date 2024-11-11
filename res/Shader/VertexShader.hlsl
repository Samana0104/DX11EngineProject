#include "HBStd.hlsli"

cbuffer ModelViewProj : register(b0)
{
    Matrix modelMat;
    Matrix viewMat;
    Matrix projMat;
};

PSInput main(VSInput vsIn)
{
    PSInput psIn = (PSInput) 0;

    float4 localPos = float4(vsIn.p.xyz, 1);

    float4 worldPos = mul(modelMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);
    
    psIn.p = projPos;
    psIn.n = float4(vsIn.n, 0);
    psIn.c = vsIn.c;
    psIn.t = vsIn.t;

    return psIn;
}