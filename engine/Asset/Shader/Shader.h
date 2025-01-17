/*
author : 변한빛
description : 쉐이더의 기본 정의를 하기 위해 만든 헤더 파일
모든 쉐이더는 이 파일을 상속한다

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    enum class ShaderType : uint8
    {
        VERTEX = 1,
        PIXEL,
        GEOMETRY
    };

    class Shader
    {
    protected:
        ComPtr<ID3DBlob>               m_shaderByteCode;
        std::vector<D3D11_BUFFER_DESC> m_cbDesc;

        std::wstring m_path;
        ShaderType   m_shaderType;

    protected:
        Shader(const wstringV path, const ShaderType& type);

    public:
        /*
           description :
               context에 쉐이더를 설정해준다. ( 상수, 쉐이더 코드 )
               vertex 쉐이더의 경우 IA까지 자동으로 설정해줌
       */
        virtual void SetUpToContext(std::shared_ptr<D3Device> device) = 0;

        std::vector<D3D11_BUFFER_DESC>& GetCBDescs();

        /*
            param : data -> 상수 버퍼에 넣을 void형 포인터 | dataSize -> 상수 버퍼에 넣을 데이터의 크기
                    constantIdx -> 상수 버퍼 레지스터 번호
            description :
               상수 버퍼를 갱신시켜준다.
        */
        const ShaderType& GetShaderType() const;
    };
}  // namespace HBSoft
