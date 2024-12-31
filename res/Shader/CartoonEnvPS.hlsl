/*
Author: 변한빛 & 이지혁
Description: 통합 픽셀 쉐이더 - 환경 매핑 및 카툰 렌더링 지원
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

    // 반사 벡터 계산
    float3 reflectVec = reflect(-eyeDir, normal);

    // 큐브맵 텍스처 샘플링
    float4 envColor = g_textureCube0.Sample(sampler0, reflectVec) * 0.5f;

    // Lambert 조명 계산
    BlinnInfo info;
    info.ambientColor = ambient.xyz;
    info.diffuseColor = diffuse.xyz;
    info.specularColor = specular.xyz;
    info.ambientFactor = ambientFactor;
    info.diffuseFactor = diffuseFactor;
    info.specularFactor = specularFactor;
    info.shininess = shininess;

    // ComputeBlinnPhong를 사용한 조명 계산
    float3 lightColor = ComputeBlinnPhong(lightDir, normal, eyeDir, info);

    // 카툰 셰이딩 단계화
    float NdotL = max(dot(normal, normalize(-lightDir)), 0);
    float toonShade = step(0.5, NdotL) * 0.5 + step(0.75, NdotL) * 0.5;

    // 카툰 색상 계산
    float3 cartoonColor = psIn.c.rgb * lightColor * toonShade;

    // 카툰 색상과 환경 매핑 혼합
    float3 finalColor = lerp(cartoonColor, envColor.rgb, 0.1); // 환경 매핑 혼합 비율 10%

    // 경계선 효과
    float edge = saturate(1 - abs(dot(normal, eyeDir)) * 2);
    if (edge > 0.8)
    {
        finalColor = float3(0, 0, 0); // 경계선은 검은색
    }

    return float4(finalColor * lightPower, psIn.c.a);
}