#include "HBStd.hlsli"
// 정점쉐이더 반환값이 무조건 float4 형 이어야 한다.
// 시멘틱(의미구조) : SV_POSITION, POSITION) 

cbuffer ModelViewProj : register(b0)
{
    Matrix world;
    Matrix view;
    Matrix proj;
};

PSInput main(VSInput vsIn)
{
    PSInput psIn = (PSInput) 0;
    psIn.p = float4(vsIn.p.xy, 0, 1);
    psIn.n = float4(vsIn.n, 0);
    psIn.c = vsIn.c;
    psIn.t = vsIn.t;

    return psIn;
}