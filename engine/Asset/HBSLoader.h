#pragma once

#include "Mesh\Mesh.h"

#define HBS_VERSION 101

namespace HBSoft
{
    struct SubMeshHeader
    {
        size_t numSubMeshIndex;
        size_t meshNameSize;
        size_t textureNameSize;
    };

    struct BornHeader
    {
        size_t bornNameSize;
        int    bornIndex;
    };

    struct AnimationHeader
    {
        size_t aniNameSize;
        int    startFrame;
        int    lastFrame;
        int    numFrame;
    };

    struct HBSFileHeader
    {
        UINT version;  // 버전
        /*
            Mesh
        */
        size_t numVertex;  // 메쉬 버텍스

        /*
            SubMesh
        */
        size_t numSubMesh;  // 서브메쉬 수

        // std::vector<UINT>    indices;
        // std::string          meshName;
        // std::wstring         textureName;
        // bool                 hasTexture;

        /*
            Born
        */
        size_t numBornObject;  // 본과 오브젝트 애니메이션의 합
        size_t numBorn;        // 본

        // std::map<std::string, int> objectIndex;  // 오브젝트(뼈 포함)인덱스
        // std::map<std::string, int> parentIndex;  // 오브젝트(뼈 포함)부모 인덱스
        // std::map<std::string, int> bornIndex;

        /*
            Animation Track
        */
        size_t numAnimtion;

        // int startFrame  = 0;
        // int lastFrame   = 0;
        // int numKeyFrame = 0;

        // struct KeyFrame
        //{
        //     vec3 pos;
        //     quat rot;
        //     vec3 scale;
        // };

        // class AnimationClip
        //{
        // public:
        //     std::string m_aniName;
        //     int         m_startFrame;
        //     int         m_lastFrame;

        //    std::vector<std::vector<KeyFrame>> m_keyFrame;
        //};
    };

    class HBSLoader

    {
    private:
        std::ofstream m_outputAsciiFile;
        std::ofstream m_outputFile;
        std::ifstream m_inputFile;

    private:
        void WriteHBSHeader(HBSFileHeader& hbsHeader, std::shared_ptr<Mesh> mesh);
        void WriteHBSAsciiFile(HBSFileHeader& hbsHeader, std::shared_ptr<Mesh> mesh);
        void WriteHBSAsciiFileFromVertex(std::shared_ptr<Mesh> mesh);
        void WriteHBSAsciiFileFromBorn(std::shared_ptr<Mesh> mesh);
        void WriteHBSAsciiFileFromAnimation(std::shared_ptr<Mesh> mesh);
        void WriteHBSFile(HBSFileHeader& hbsHeader, std::shared_ptr<Mesh> mesh);

    public:
        bool                  Export(std::shared_ptr<Mesh> mesh, const wstringV filePath);
        std::shared_ptr<Mesh> Load(std::shared_ptr<D3Device> device, const wstringV filePath);
    };
}  // namespace HBSoft
