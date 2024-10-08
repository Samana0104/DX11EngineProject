// 픽셀쉐이더 , float1(x), float2(x,y), float3(x,y,z), float4(x,y,z,w)
// 반환값 = FLOAT4(R,G,B,A)로 반환되어야 한다.
// 시멘틱(의미구조) : SV_POSITION, SV_TARGET
// 쉐이더 입력 및 출력 데이터는 
// 지정된 레지스터에 저장 및 출력 되어야 한다.

Texture2D g_txTexture : register(t0);
SamplerState sampler0 : register(s0);

struct PS_In
{
    float4 p : SV_POSITION; // 반드시 float4
    float4 c : COLOR;
    float2 t : TEXCOORD0;
    float2 v : VPOS;
};

struct PS_Out
{
    float4 c : SV_Target;
};

PS_Out PSMain(PS_In psIn)
{
    PS_Out psOut = (PS_Out) 0;
    float4 pixel = g_txTexture.Sample(sampler0, psIn.t);
    psOut.c = pixel * psIn.c;
	//psOut.c = pixel;
 
    return psOut;
  //return float4(psIn.t.x, psIn.t.y, 0,1);
}