#include "HBStd.hlsli"

cbuffer MVPMat : register(b0)
{
	Matrix modelMat;
	Matrix viewMat;
	Matrix projMat;
};

LinePsInput main(VSInput vsIn)
{
	LinePsInput psIn = (LinePsInput) 0;

	float4 localPos = float4(vsIn.p.xyz, 1);
	float4 worldPos = mul(modelMat, localPos);
	float4 viewPos = mul(viewMat, worldPos);
	float4 projPos = mul(projMat, viewPos);
    
	psIn.p = projPos;
	psIn.c = vsIn.c;

	return psIn;
}