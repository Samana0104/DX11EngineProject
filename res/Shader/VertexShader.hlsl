#include "HBStd.hlsli"
// �������̴� ��ȯ���� ������ float4 �� �̾�� �Ѵ�.
// �ø�ƽ(�ṉ̀���) : SV_POSITION, POSITION) 

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