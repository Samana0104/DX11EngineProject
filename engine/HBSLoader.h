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
        // int

        /*
            Animation Track
        */
        int startFrame  = 0;
        int lastFrame   = 0;
        int numKeyFrame = 0;
    };

    class HBSLoader
    {};

}  // namespace HBSoft
