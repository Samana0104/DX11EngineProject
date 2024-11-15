#include "HBStd.hlsli"

float4 main(LinePsInput vsIn) : SV_Target0
{
    return vsIn.c;
}