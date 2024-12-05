#pragma once

namespace HBSoft
{
    struct HBSFileHeader
    {
        int version;  // 버전
        /*
            Mesh
        */
        int          numVertex;   // 메쉬 버텍스
        int          numSubmesh;  // 서브메쉬 수
        int          numIndex;    // 인덱스 버퍼
        std::string  meshName;
        std::wstring textureName;
        bool         hasTexture;

        /*
            Born
        */
        int

        /*
            Animation Track
        */
        int startFrame  = 0;
        int lastFrame   = 0;
        int numKeyFrame = 0;

        std::vector < std::vector int iSubVertexBufferCounter   = 0;
        int                           iSubIndexBufferCounter    = 0;
        int                           iSubIWVertexBufferCounter = 0;
        T::TMatrix                    matWorld;
    };

    class HBSLoader
    {};

}  // namespace HBSoft
