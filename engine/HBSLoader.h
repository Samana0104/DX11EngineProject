#pragma once

namespace HBSoft
{
    struct HBSFileHeader
    {
        int version;  // ����
        /*
            Mesh
        */
        int          numVertex;   // �޽� ���ؽ�
        int          numSubmesh;  // ����޽� ��
        int          numIndex;    // �ε��� ����
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
