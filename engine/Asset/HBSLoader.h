/*
author : ���Ѻ�
description : HBS ���� ������ import/export�� ���� Ŭ���� �������

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
        UINT version;  // ����
        /*
            Mesh
        */
        size_t numVertex;  // �޽� ���ؽ�

        /*
            SubMesh
        */
        size_t numSubMesh;  // ����޽� ��

        // std::vector<UINT>    indices;
        // std::string          meshName;
        // std::wstring         textureName;
        // bool                 hasTexture;

        /*
            Born
        */
        size_t numBornObject;  // ���� ������Ʈ �ִϸ��̼��� ��
        size_t numBorn;        // ��

        // std::map<std::string, int> objectIndex;  // ������Ʈ(�� ����)�ε���
        // std::map<std::string, int> parentIndex;  // ������Ʈ(�� ����)�θ� �ε���
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
