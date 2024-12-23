/*
author : 변한빛
description : HBS 파일 포맷의 import/export를 위한 클래스 헤더파일

version: 1.1
date: 2024-12-23
*/

#pragma once

#include "Mesh\Mesh.h"

namespace HBSoft
{
#define HBS_VERSION 103

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
        void WriteHBSFile(HBSFileHeader& hbsHeader, std::shared_ptr<Mesh> mesh);

    public:
        bool                  Export(std::shared_ptr<Mesh> mesh, const wstringV filePath);
        std::shared_ptr<Mesh> Load(std::shared_ptr<D3Device> device, const wstringV filePath);
    };
}  // namespace HBSoft
