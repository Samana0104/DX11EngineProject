#include "HBStd.hlsli"

PSInput main(VSInput vsIn)
{
    PSInput psIn = (PSInput) 0;

    float4 localPos = float4(vsIn.p.xyz, 1);

    float4 worldPos = mul(worldMat, localPos);
    float4 viewPos = mul(viewMat, worldPos);
    float4 projPos = mul(projMat, viewPos);

    float4 normal = mul(invWorldMat, float4(vsIn.n.xyz, 0));
    
    psIn.p = projPos;
    psIn.n = normal;
    psIn.c = vsIn.c;
    psIn.t = vsIn.t;

    return psIn;
}