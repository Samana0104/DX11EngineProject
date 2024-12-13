/*
author : ���Ѻ�
description : HBS ���� ������ import/export�� ���� Ŭ���� �ҽ�����

version: 1.0.4
date: 2024-12-10
*/

#include "pch.h"
#include "HBSLoader.h"
using namespace HBSoft;

void HBSLoader::WriteHBSHeader(HBSFileHeader& hbsHeader, std::shared_ptr<Mesh> mesh)
{
    hbsHeader.version       = HBS_VERSION;
    hbsHeader.numVertex     = mesh->m_vertices.size();
    hbsHeader.numSubMesh    = mesh->m_subMeshes.size();
    hbsHeader.numAnimtion   = mesh->m_animations.size();
    hbsHeader.numBornObject = mesh->m_born.objectIndex.size();
    hbsHeader.numBorn       = mesh->m_born.bornIndex.size();
}

void HBSLoader::WriteHBSAsciiFile(HBSFileHeader& hbsHeader, std::shared_ptr<Mesh> mesh)
{
    m_outputAsciiFile << "hbs version: " << hbsHeader.version << std::endl;
    m_outputAsciiFile << "hbs numVertex : " << hbsHeader.numVertex << std::endl;
    m_outputAsciiFile << "hbs numSubMesh : " << hbsHeader.numSubMesh << std::endl;
    m_outputAsciiFile << "hbs bornObject : " << hbsHeader.numBornObject << std::endl;
    m_outputAsciiFile << "hbs born : " << hbsHeader.numBorn << std::endl;
    m_outputAsciiFile << "hbs numAnimation : " << hbsHeader.numAnimtion << std::endl;

    WriteHBSAsciiFileFromVertex(mesh);
    WriteHBSAsciiFileFromBorn(mesh);
    WriteHBSAsciiFileFromAnimation(mesh);
}

void HBSLoader::WriteHBSAsciiFileFromVertex(std::shared_ptr<Mesh> mesh)
{
    for (size_t i = 0; i < mesh->m_vertices.size(); i++)
    {
        m_outputAsciiFile << "Vertex[index : " << i << "]" << std::endl;

        m_outputAsciiFile << " [P] :" << mesh->m_vertices[i].p.x << ", " << mesh->m_vertices[i].p.y
                          << ", " << mesh->m_vertices[i].p.z;
        m_outputAsciiFile << " [N] :" << mesh->m_vertices[i].n.x << ", " << mesh->m_vertices[i].n.y
                          << ", " << mesh->m_vertices[i].n.z;
        m_outputAsciiFile << " [C] :" << mesh->m_vertices[i].c.r << ", " << mesh->m_vertices[i].c.g
                          << ", " << mesh->m_vertices[i].c.b << ", " << mesh->m_vertices[i].c.a;
        m_outputAsciiFile << " [T] :" << mesh->m_vertices[i].t.x << ", " << mesh->m_vertices[i].t.y;
        m_outputAsciiFile << std::endl;

        // born idx, weight
        for (size_t j = 0; j < 8; j++)
        {
            m_outputAsciiFile << " [I, W][" << j << "]" << mesh->m_vertices[i].i[j] << ", "
                              << mesh->m_vertices[i].w[j];
            m_outputAsciiFile << std::endl;
        }
        m_outputAsciiFile << std::endl;
    }


    for (size_t i = 0; i < mesh->m_subMeshes.size(); i++)
    {
        m_outputAsciiFile << std::endl << std::endl;
        m_outputAsciiFile << "-----------------------------------------------";
        m_outputAsciiFile << std::endl << std::endl;

        m_outputAsciiFile << "submesh number : " << i << std::endl;
        m_outputAsciiFile << "submesh index : " << mesh->m_subMeshes[i]->indices.size() << std::endl;
        m_outputAsciiFile << "meshName : " << mesh->m_subMeshes[i]->meshName << std::endl;
        m_outputAsciiFile << "textureName : " << HBSoft::ToMultiByte(mesh->m_subMeshes[i]->textureName)
                          << std::endl;
        m_outputAsciiFile << "hasTexture : " << mesh->m_subMeshes[i]->hasTexture << std::endl
                          << std::endl;

        m_outputAsciiFile << "index" << std::endl;
        for (size_t j = 0; j < mesh->m_subMeshes[i]->indices.size(); j++)
            m_outputAsciiFile << " i[" << j << "] : v[" << mesh->m_subMeshes[i]->indices[j] << "]";

        m_outputAsciiFile << std::endl;
    }

    m_outputAsciiFile << std::endl << std::endl;
    m_outputAsciiFile << "-----------------------------------------------";
    m_outputAsciiFile << std::endl << std::endl;
}

void HBSLoader::WriteHBSAsciiFileFromBorn(std::shared_ptr<Mesh> mesh)
{
    m_outputAsciiFile << "born object(born index + object index)" << std::endl;

    for (auto bornObject : mesh->m_born.objectIndex)
        m_outputAsciiFile << "name : " << bornObject.first << " , index : " << bornObject.second
                          << std::endl;


    m_outputAsciiFile << std::endl << std::endl;
    m_outputAsciiFile << "-----------------------------------------------";
    m_outputAsciiFile << std::endl << std::endl;
    m_outputAsciiFile << "born(born index)" << std::endl;

    for (auto born : mesh->m_born.bornIndex)
        m_outputAsciiFile << "name : " << born.first << " , index : " << born.second << std::endl;

    m_outputAsciiFile << std::endl << std::endl;
    m_outputAsciiFile << "-----------------------------------------------";
    m_outputAsciiFile << std::endl << std::endl;
    m_outputAsciiFile << "born(parent index)" << std::endl;

    for (auto bornParent : mesh->m_born.parentIndex)
        m_outputAsciiFile << "name : " << bornParent.first << " , parent index : " << bornParent.second
                          << std::endl;
}

void HBSLoader::WriteHBSAsciiFileFromAnimation(std::shared_ptr<Mesh> mesh)
{
    for (size_t i = 0; i < mesh->m_animations.size(); i++)
    {
        m_outputAsciiFile << std::endl << std::endl;
        m_outputAsciiFile << "-----------------------------------------------";
        m_outputAsciiFile << std::endl << std::endl;

        m_outputAsciiFile << "animation name : " << mesh->m_animations[i]->m_aniName << std::endl;
        m_outputAsciiFile << "start frame : " << mesh->m_animations[i]->m_startFrame << std::endl;
        m_outputAsciiFile << "last frame : " << mesh->m_animations[i]->m_lastFrame << std::endl;
        m_outputAsciiFile << "frame count : " << mesh->m_animations[i]->m_numFrame << std::endl;

        m_outputAsciiFile << std::endl;

        for (size_t j = 0; j < mesh->m_animations[i]->m_keyFrame.size(); j++)
        {
            m_outputAsciiFile << "keyframe " << std::endl;
            m_outputAsciiFile << "born index : " << j << std::endl;
            for (size_t k = 0; k < mesh->m_animations[i]->m_keyFrame[j].size(); k++)
            {
                KeyFrame key = mesh->m_animations[i]->m_keyFrame[j][k];

                m_outputAsciiFile << " [Pos] : " << key.pos.x << ", " << key.pos.y << ", " << key.pos.z;
                m_outputAsciiFile << " [Rotation(quat wxyz)] : " << key.rot.w << ", " << key.rot.x
                                  << ", " << key.rot.y << ", " << key.rot.z;
                m_outputAsciiFile << " [Scale] : " << key.scale.x << ", " << key.scale.y << ", "
                                  << key.scale.z;
                m_outputAsciiFile << std::endl;
            }

            m_outputAsciiFile << std::endl;
        }
        m_outputAsciiFile << std::endl;
    }
}

void HBSLoader::WriteHBSFile(HBSFileHeader& hbsHeader, std::shared_ptr<Mesh> mesh)
{
    SubMeshHeader   subHeader;
    BornHeader      bornHeader;
    AnimationHeader aniHeader;

    // main header ����
    m_outputFile.write(reinterpret_cast<const char*>(&hbsHeader), sizeof(HBSFileHeader));
    m_outputFile.write(reinterpret_cast<const char*>(&mesh->m_vertices.at(0)),
                       sizeof(Vertex) * mesh->m_vertices.size());

    // submesh header ����
    for (size_t i = 0; i < hbsHeader.numSubMesh; i++)
    {
        subHeader.numSubMeshIndex = mesh->m_subMeshes[i]->indices.size();
        subHeader.textureNameSize = mesh->m_subMeshes[i]->textureName.size();
        subHeader.meshNameSize    = mesh->m_subMeshes[i]->meshName.size();

        m_outputFile.write(reinterpret_cast<const char*>(&subHeader), sizeof(subHeader));

        if (subHeader.numSubMeshIndex > 0)
            m_outputFile.write(reinterpret_cast<const char*>(&mesh->m_subMeshes[i]->indices.at(0)),
                               sizeof(UINT) * mesh->m_subMeshes[i]->indices.size());

        if (subHeader.meshNameSize > 0)
            m_outputFile.write(reinterpret_cast<const char*>(&mesh->m_subMeshes[i]->meshName.at(0)),
                               sizeof(char) * mesh->m_subMeshes[i]->meshName.size());

        if (subHeader.textureNameSize > 0)
            m_outputFile.write(reinterpret_cast<const char*>(&mesh->m_subMeshes[i]->textureName.at(0)),
                               sizeof(wchar_t) * mesh->m_subMeshes[i]->textureName.size());

        m_outputFile.write(reinterpret_cast<const char*>(&mesh->m_subMeshes[i]->hasTexture),
                           sizeof(bool));
    }

    // born header ����
    for (auto& bornObject : mesh->m_born.objectIndex)
    {
        bornHeader.bornNameSize = bornObject.first.size();
        bornHeader.bornIndex    = bornObject.second;

        m_outputFile.write(reinterpret_cast<const char*>(&bornHeader), sizeof(BornHeader));
        m_outputFile.write(reinterpret_cast<const char*>(&bornObject.first.at(0)),
                           sizeof(char) * bornObject.first.size());
    }

    for (auto& born : mesh->m_born.bornIndex)
    {
        bornHeader.bornNameSize = born.first.size();
        bornHeader.bornIndex    = born.second;

        m_outputFile.write(reinterpret_cast<const char*>(&bornHeader), sizeof(BornHeader));
        m_outputFile.write(reinterpret_cast<const char*>(&born.first.at(0)),
                           sizeof(char) * born.first.size());
    }

    for (auto& bornParent : mesh->m_born.parentIndex)
    {
        bornHeader.bornNameSize = bornParent.first.size();
        bornHeader.bornIndex    = bornParent.second;

        m_outputFile.write(reinterpret_cast<const char*>(&bornHeader), sizeof(BornHeader));
        m_outputFile.write(reinterpret_cast<const char*>(&bornParent.first.at(0)),
                           sizeof(char) * bornParent.first.size());
    }

    // animation header ����
    for (size_t i = 0; i < hbsHeader.numAnimtion; i++)
    {
        aniHeader.aniNameSize = mesh->m_animations[i]->m_aniName.size();
        aniHeader.startFrame  = mesh->m_animations[i]->m_startFrame;
        aniHeader.lastFrame   = mesh->m_animations[i]->m_lastFrame;
        aniHeader.numFrame    = mesh->m_animations[i]->m_numFrame;

        m_outputFile.write(reinterpret_cast<const char*>(&aniHeader), sizeof(AnimationHeader));
        m_outputFile.write(reinterpret_cast<const char*>(&mesh->m_animations[i]->m_aniName.at(0)),
                           sizeof(char) * mesh->m_animations[i]->m_aniName.size());

        for (size_t j = 0; j < hbsHeader.numBornObject; j++)
        {
            m_outputFile.write(
            reinterpret_cast<const char*>(&mesh->m_animations[i]->m_keyFrame[j].at(0)),
            sizeof(KeyFrame) * aniHeader.numFrame);
        }
    }
}

bool HBSLoader::Export(std::shared_ptr<Mesh> mesh, const wstringV filePath)
{
    auto [fileDir, fileName]     = HBSoft::GetFileDirAndName(filePath);
    std::string   hbsAsciiFormat = HBSoft::ToMultiByte(fileDir + fileName + L".txt");
    std::string   hbsFormat      = HBSoft::ToMultiByte(fileDir + fileName + L".hbs");
    HBSFileHeader fileHeader;

    m_outputAsciiFile.open(hbsAsciiFormat.c_str(), std::ios::out);
    m_outputFile.open(hbsFormat.c_str(), std::ios::binary);

    if (!m_outputAsciiFile.is_open())
    {
        MessageBoxA(nullptr, "fbx���� -> hbs���� ��ȯ ����[txt ���� �Ұ�]", "Converter error", MB_OK);
        return false;
    }

    if (!m_outputFile.is_open())
    {
        MessageBoxA(nullptr, "fbx���� -> hbs���� ��ȯ ����[hbs ���� �Ұ�]", "Converter error", MB_OK);
        return false;
    }

    WriteHBSHeader(fileHeader, mesh);
    WriteHBSAsciiFile(fileHeader, mesh);
    WriteHBSFile(fileHeader, mesh);
    m_outputAsciiFile.close();
    m_outputFile.close();

    return true;
}

std::shared_ptr<Mesh> HBSLoader::Load(std::shared_ptr<D3Device> device, const wstringV filePath)
{
    HBSFileHeader   hbsHeader;
    SubMeshHeader   subHeader;
    BornHeader      bornHeader;
    AnimationHeader aniHeader;

    std::pair<std ::string, int> bornNode;
    std::string                  fileDir = HBSoft::ToMultiByte(filePath);
    std::shared_ptr<Mesh>        mesh    = std::make_shared<Mesh>();


    m_inputFile.open(fileDir, std::ios::in | std::ios::binary);

    if (!m_inputFile.is_open())
    {
        MessageBoxA(nullptr, "hbs���� �ε� ����", "load error", MB_OK);
        return nullptr;
    }

    m_inputFile.read(reinterpret_cast<char*>(&hbsHeader), sizeof(HBSFileHeader));

    if (m_inputFile.fail())
    {
        MessageBoxA(nullptr, "hbs���� �ε� ����[����� ���� �� ����]", "load error", MB_OK);
        return nullptr;
    }

    if (hbsHeader.version != HBS_VERSION)
    {
        MessageBoxA(nullptr, "hbs���� �ε� ����[���� ����ġ �ֽ� hbs�� ������]", "load error", MB_OK);
        return nullptr;
    }

    mesh->m_vertices.resize(hbsHeader.numVertex);
    mesh->m_subMeshes.resize(hbsHeader.numSubMesh);

    m_inputFile.read(reinterpret_cast<char*>(&mesh->m_vertices.at(0)),
                     sizeof(Vertex) * hbsHeader.numVertex);

    for (size_t i = 0; i < hbsHeader.numSubMesh; i++)
    {
        m_inputFile.read(reinterpret_cast<char*>(&subHeader), sizeof(SubMeshHeader));

        mesh->m_subMeshes[i] = std::make_shared<SubMesh>();
        mesh->m_subMeshes[i]->indices.resize(subHeader.numSubMeshIndex);
        mesh->m_subMeshes[i]->meshName.resize(subHeader.meshNameSize);
        mesh->m_subMeshes[i]->textureName.resize(subHeader.textureNameSize);

        if (subHeader.numSubMeshIndex > 0)
            m_inputFile.read(reinterpret_cast<char*>(&mesh->m_subMeshes[i]->indices.at(0)),
                             sizeof(UINT) * mesh->m_subMeshes[i]->indices.size());

        if (subHeader.meshNameSize > 0)
            m_inputFile.read(reinterpret_cast<char*>(&mesh->m_subMeshes[i]->meshName.at(0)),
                             sizeof(char) * mesh->m_subMeshes[i]->meshName.size());

        if (subHeader.textureNameSize > 0)
            m_inputFile.read(reinterpret_cast<char*>(&mesh->m_subMeshes[i]->textureName.at(0)),
                             sizeof(wchar_t) * mesh->m_subMeshes[i]->textureName.size());

        m_inputFile.read(reinterpret_cast<char*>(&mesh->m_subMeshes[i]->hasTexture), sizeof(bool));
    }

    // born header ����
    for (size_t i = 0; i < hbsHeader.numBornObject; i++)
    {
        m_inputFile.read(reinterpret_cast<char*>(&bornHeader), sizeof(BornHeader));
        bornNode.first.resize(bornHeader.bornNameSize);
        bornNode.second = bornHeader.bornIndex;

        m_inputFile.read(reinterpret_cast<char*>(&bornNode.first.at(0)),
                         sizeof(char) * bornHeader.bornNameSize);

        mesh->m_born.objectIndex.insert(bornNode);
    }

    for (size_t i = 0; i < hbsHeader.numBorn; i++)
    {
        m_inputFile.read(reinterpret_cast<char*>(&bornHeader), sizeof(BornHeader));
        bornNode.first.resize(bornHeader.bornNameSize);
        bornNode.second = bornHeader.bornIndex;

        m_inputFile.read(reinterpret_cast<char*>(&bornNode.first.at(0)),
                         sizeof(char) * bornHeader.bornNameSize);

        mesh->m_born.bornIndex.insert(bornNode);
    }

    for (size_t i = 0; i < hbsHeader.numBornObject; i++)
    {
        m_inputFile.read(reinterpret_cast<char*>(&bornHeader), sizeof(BornHeader));
        bornNode.first.resize(bornHeader.bornNameSize);
        bornNode.second = bornHeader.bornIndex;

        m_inputFile.read(reinterpret_cast<char*>(&bornNode.first.at(0)),
                         sizeof(char) * bornHeader.bornNameSize);

        mesh->m_born.parentIndex.insert(bornNode);
    }

    mesh->m_animations.resize(hbsHeader.numAnimtion);

    for (size_t i = 0; i < hbsHeader.numAnimtion; i++)
    {
        mesh->m_animations[i] = std::make_shared<AnimationClip>();

        m_inputFile.read(reinterpret_cast<char*>(&aniHeader), sizeof(AnimationHeader));
        mesh->m_animations[i]->m_aniName.resize(aniHeader.aniNameSize);
        mesh->m_animations[i]->m_startFrame = aniHeader.startFrame;
        mesh->m_animations[i]->m_lastFrame  = aniHeader.lastFrame;
        mesh->m_animations[i]->m_numFrame   = aniHeader.numFrame;

        m_inputFile.read(reinterpret_cast<char*>(&mesh->m_animations[i]->m_aniName.at(0)),
                         sizeof(char) * mesh->m_animations[i]->m_aniName.size());

        mesh->m_animations[i]->m_keyFrame.resize(hbsHeader.numBornObject);
        for (size_t j = 0; j < hbsHeader.numBornObject; j++)
        {
            mesh->m_animations[i]->m_keyFrame[j].resize(aniHeader.numFrame);

            m_inputFile.read(reinterpret_cast<char*>(&mesh->m_animations[i]->m_keyFrame[j].at(0)),
                             sizeof(KeyFrame) * aniHeader.numFrame);
        }
    }

    m_inputFile.close();

    device->CreateVertexBuffer(mesh->m_vertices, mesh->m_vertexBuffer);

    for (UINT i = 0; i < mesh->m_subMeshes.size(); i++)
        device->CreateIndexBuffer(mesh->m_subMeshes[i]->indices, mesh->m_subMeshes[i]->indexBuffer);


    return mesh;
}