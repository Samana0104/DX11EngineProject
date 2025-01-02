/*
Author: ���Ѻ� & ������
Description: ���� �ȼ� ���̴� - ȯ�� ���� �� ī�� ������ ����
Version: 1.1.0
*/

#include "HBStd.hlsli"

cbuffer DefaultLight : register(b0)
{
    float3 lightDir;
    float1 lightPower;
    float3 eyePos;
    float1 dummy;
};

cbuffer Material : register(b1)
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float shininess;
    float ambientFactor;
    float diffuseFactor;
    float specularFactor;
};

TextureCube g_textureCube0 : register(t1);
SamplerState sampler0 : register(s0);

float4 main(PSInput psIn) : SV_Target0
{
    float3 normal = normalize(psIn.n);
    float3 eyeDir = normalize(eyePos - psIn.worldPos);

    // �ݻ� ���� ���
    float3 reflectVec = reflect(-eyeDir, normal);

    // ť��� �ؽ�ó ���ø�
    float4 envColor = g_textureCube0.Sample(sampler0, reflectVec) * 0.5f;

    // Lambert ���� ���
    BlinnInfo info;
    info.ambientColor = ambient.xyz;
    info.diffuseColor = diffuse.xyz;
    info.specularColor = specular.xyz;
    info.ambientFactor = ambientFactor;
    info.diffuseFactor = diffuseFactor;
    info.specularFactor = specularFactor;
    info.shininess = shininess;

    // ComputeBlinnPhong�� ����� ���� ���
    float3 lightColor = ComputeBlinnPhong(lightDir, normal, eyeDir, info);

    // ī�� ���̵� �ܰ�ȭ
    float NdotL = max(dot(normal, normalize(-lightDir)), 0);
    float toonShade = step(0.5, NdotL) * 0.5 + step(0.75, NdotL) * 0.5;

    // ī�� ���� ���
    float3 cartoonColor = psIn.c.rgb * lightColor * toonShade;

    // ī�� ����� ȯ�� ���� ȥ��
    float3 finalColor = lerp(cartoonColor, envColor.rgb, 0.1); // ȯ�� ���� ȥ�� ���� 10%

    // ��輱 ȿ��
    float edge = saturate(1 - abs(dot(normal, eyeDir)) * 2);
    if (edge > 0.8)
    {
        finalColor = float3(0, 0, 0); // ��輱�� ������
    }

    return float4(finalColor * lightPower, psIn.c.a);
}