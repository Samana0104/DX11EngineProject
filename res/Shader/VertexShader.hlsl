// 정점쉐이더 반환값이 무조건 float4 형 이어야 한다.
// 시멘틱(의미구조) : SV_POSITION, POSITION) 
struct VS_In
{
    float2 p : POSITION;
    float4 c : COLOR;
    float2 t : TEX;
};

struct VS_Out
{
    float4 p : SV_POSITION; // 반드시 float4
    float4 c : COLOR0; //COLOR1;
    float2 t : TEXCOORD0; // ~ TEXCOORD15
    float2 v : VPOS;
};

VS_Out VSMain(VS_In vsIn)
{
    VS_Out vsOut = (VS_Out) 0;
    vsOut.p = float4(vsIn.p.x, vsIn.p.y, 0, 1);
    vsOut.c = vsIn.c;
    vsOut.t = vsIn.t;
    vsOut.v.xy = vsIn.p.xy;
    return vsOut;
}
/*float4 VSMain( float2 p : POS, float4 c:COLOR) : SV_POSITION
{
  return float4(p.x,p.y,0.5f,1.0f);
}*/