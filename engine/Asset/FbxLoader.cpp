/*
author : 변한빛
description : fbx load를 위한 클래스 소스 파일

version: 1.0.0
date: 2024-11-25
*/

#include "pch.h"
#include "FbxLoader.h"
using namespace HBSoft;

FbxLoader::FbxLoader()
    : m_fbxManager(nullptr), m_fbxImporter(nullptr), m_fbxScene(nullptr)
{}

void FbxLoader::InitFbxManager()
{
    if (m_fbxManager == nullptr)
        m_fbxManager = FbxManager::Create();

    if (m_fbxImporter == nullptr)
        m_fbxImporter = FbxImporter::Create(m_fbxManager, "");

    if (m_fbxScene == nullptr)
        m_fbxScene = FbxScene::Create(m_fbxManager, "");
}

void FbxLoader::ReleaseFbxManager()
{
    if (m_fbxImporter != nullptr)
    {
        m_fbxImporter->Destroy();
        m_fbxImporter = nullptr;
    }

    if (m_fbxScene != nullptr)
    {
        m_fbxScene->Destroy();
        m_fbxScene = nullptr;
    }

    if (m_fbxManager != nullptr)
    {
        m_fbxManager->Destroy();
        m_fbxManager = nullptr;
    }
}

std::shared_ptr<Mesh> FbxLoader::Load(std::shared_ptr<D3Device> device, const wstringV filePath)
{
    FbxNode*              fbxRootNode = nullptr;
    std::vector<FbxMesh*> meshSet;

    std::shared_ptr<Mesh> mesh  = std::make_shared<Mesh>();
    std::string           sPath = HBSoft::ToMultiByte(filePath);

    InitFbxManager();

    if (!m_fbxImporter->Initialize(sPath.c_str()))
    {
        MessageBoxA(NULL, m_fbxImporter->GetStatus().GetErrorString(), "import error", MB_OK);
        return nullptr;
    }

    if (!m_fbxImporter->Import(m_fbxScene))
    {
        MessageBoxA(NULL, m_fbxImporter->GetStatus().GetErrorString(), "import error", MB_OK);
        return nullptr;
    }

    FbxAxisSystem::MayaZUp.ConvertScene(m_fbxScene);
    fbxRootNode = m_fbxScene->GetRootNode();
    m_subMeshes.clear();
    m_subNodes.clear();

    ProcessNode(fbxRootNode);
    InitMesh(mesh);

    for (UINT i = 0; i < m_subMeshes.size(); i++)
        ProcessMesh(m_subMeshes[i], m_subNodes[i], mesh);

    ReleaseFbxManager();

    device->CreateVertexBuffer(mesh->m_vertices, mesh->m_vertexBuffer);

    for (UINT i = 0; i < mesh->m_subMeshes.size(); i++)
        device->CreateIndexBuffer(mesh->m_subMeshes[i]->indices, mesh->m_subMeshes[i]->indexBuffer);

    return mesh;
}

void FbxLoader::ProcessNode(FbxNode* fNode)
{
    if (fNode == nullptr)
        return;

    FbxMesh* fMesh = fNode->GetMesh();

    if (fMesh != nullptr)
    {
        m_subMeshes.push_back(fMesh);
        m_subNodes.push_back(fNode);
    }

    int numChild = fNode->GetChildCount();

    for (int childIdx = 0; childIdx < numChild; childIdx++)
        ProcessNode(fNode->GetChild(childIdx));
}

int FbxLoader::GetSubMaterialPolygonIndex(int polyIdx, FbxLayerElementMaterial* fMaterial)
{
    int ret = -1;
    switch (fMaterial->GetMappingMode())
    {
    case FbxLayerElement::eByPolygon:
        {
            // 어떤 곳에 저장된 파악
            switch (fMaterial->GetReferenceMode())
            {
            case FbxLayerElement::eIndex:
                {
                    ret = polyIdx;
                }
                break;
            case FbxLayerElement::eIndexToDirect:
                {
                    ret = fMaterial->GetIndexArray().GetAt(polyIdx);
                }
                break;
            }
        }
    }
    return ret;
}

FbxVector2 FbxLoader::GetUV(FbxLayerElementUV* uvSet, int vertexPosIdx, int vertexUVIdx)
{
    FbxVector2 ret;
    // 어떤 방식으로 적용
    switch (uvSet->GetMappingMode())
    {
    case FbxLayerElementUV::eByControlPoint:
        // 어떤 곳에 저장된 파악
        switch (uvSet->GetReferenceMode())
        {
        case FbxLayerElementVertexColor::eDirect:
            ret = uvSet->GetDirectArray().GetAt(vertexPosIdx);
            break;

        case FbxLayerElementVertexColor::eIndexToDirect:
            int colorIdx = uvSet->GetIndexArray().GetAt(vertexPosIdx);
            ret          = uvSet->GetDirectArray().GetAt(colorIdx);
            break;
        }
        break;

    case FbxLayerElementUV::eByPolygonVertex:
        switch (uvSet->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:  // fbx 5이하
            ret = uvSet->GetDirectArray().GetAt(vertexUVIdx);
            break;

        case FbxLayerElementUV::eIndexToDirect:
            int colorIdx = uvSet->GetIndexArray().GetAt(vertexUVIdx);
            ret          = uvSet->GetDirectArray().GetAt(colorIdx);
            break;
        }
        break;
    }
    return ret;
}

FbxColor FbxLoader::GetColor(FbxLayerElementVertexColor* vertexColorSet, int vertexPosIdx,
                             int vertexColorIdx)
{
    FbxColor ret;
    switch (vertexColorSet->GetMappingMode())
    {
    case FbxLayerElementVertexColor::eByControlPoint:
        switch (vertexColorSet->GetReferenceMode())
        {
        case FbxLayerElementVertexColor::eDirect:
            ret = vertexColorSet->GetDirectArray().GetAt(vertexPosIdx);
            break;

        case FbxLayerElementVertexColor::eIndexToDirect:
            int colorIdx = vertexColorSet->GetIndexArray().GetAt(vertexPosIdx);
            ret          = vertexColorSet->GetDirectArray().GetAt(colorIdx);
            break;
        }
        break;

    case FbxLayerElementVertexColor::eByPolygonVertex:
        switch (vertexColorSet->GetReferenceMode())
        {
        case FbxLayerElementVertexColor::eDirect:
            ret = vertexColorSet->GetDirectArray().GetAt(vertexColorIdx);
            break;

        case FbxLayerElementVertexColor::eIndexToDirect:
            int colorIdx = vertexColorSet->GetIndexArray().GetAt(vertexPosIdx);
            ret          = vertexColorSet->GetDirectArray().GetAt(colorIdx);
            break;
        }
        break;
    }
    return ret;
}

FbxVector4 FbxLoader::GetNormal(FbxLayerElementNormal* vertexNormalSet, int vertexPosIdx,
                                int vertexNormalIdx)
{
    FbxVector4 ret;
    switch (vertexNormalSet->GetMappingMode())
    {
        // 제어점 당 1개의 정보가 있다.
    case FbxLayerElementVertexColor::eByControlPoint:
        // 어떤 곳에 저장된 파악
        switch (vertexNormalSet->GetReferenceMode())
        {
        case FbxLayerElementVertexColor::eDirect:
            ret = vertexNormalSet->GetDirectArray().GetAt(vertexPosIdx);
            break;

        case FbxLayerElementVertexColor::eIndexToDirect:
            int normalIdx = vertexNormalSet->GetIndexArray().GetAt(vertexPosIdx);
            ret           = vertexNormalSet->GetDirectArray().GetAt(normalIdx);
            break;
        }
        break;
        // 정점 당 1개의 정보가 있다.

    case FbxLayerElementVertexColor::eByPolygonVertex:
        switch (vertexNormalSet->GetReferenceMode())
        {
        case FbxLayerElementVertexColor::eDirect:
            ret = vertexNormalSet->GetDirectArray().GetAt(vertexNormalIdx);
            break;

        case FbxLayerElementVertexColor::eIndexToDirect:
            int normalIdx = vertexNormalSet->GetIndexArray().GetAt(vertexNormalIdx);
            ret           = vertexNormalSet->GetDirectArray().GetAt(normalIdx);
            break;
        }
        break;
    }

    return ret;
}

void FbxLoader::ProcessMesh(FbxMesh* fMesh, FbxNode* fNode, std::shared_ptr<Mesh> mesh)
{
    FbxAMatrix geoMat;
    FbxVector4 trans = fNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rot   = fNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = fNode->GetGeometricScaling(FbxNode::eSourcePivot);

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    geoMat.SetT(trans);
    geoMat.SetR(rot);
    geoMat.SetS(scale);
    // 노말 변환 행렬
    FbxAMatrix normalMatrix = geoMat;
    normalMatrix            = normalMatrix.Inverse();
    normalMatrix            = normalMatrix.Transpose();

    //// 월드 변환 행렬
    FbxAMatrix matWorld = fNode->EvaluateGlobalTransform(0);

    // Layer :  레이어 회수만큼 랜더링한다.
    std::vector<FbxLayerElementUV*>          VertexUVLayer;
    std::vector<FbxLayerElementVertexColor*> VertexColorLayer;
    std::vector<FbxLayerElementNormal*>      VertexNormalLayer;
    std::vector<FbxLayerElementTangent*>     VertexTangentLayer;
    std::vector<FbxLayerElementMaterial*>    VertexMaterialLayer;

    int layerCount = fMesh->GetLayerCount();

    for (int layer = 0; layer < layerCount; layer++)
    {
        FbxLayer* fbxLayer = fMesh->GetLayer(layer);

        if (fbxLayer->GetUVs())
            VertexUVLayer.emplace_back(fbxLayer->GetUVs());

        if (fbxLayer->GetVertexColors())
            VertexColorLayer.emplace_back(fbxLayer->GetVertexColors());

        if (fbxLayer->GetTangents())
            VertexTangentLayer.emplace_back(fbxLayer->GetTangents());

        if (fbxLayer->GetNormals())
            VertexNormalLayer.emplace_back(fbxLayer->GetNormals());

        if (fbxLayer->GetMaterials())
            VertexMaterialLayer.emplace_back(fbxLayer->GetMaterials());
    }

    // 정점노말 (재)계산
    if (VertexNormalLayer.size() > 0)
    {
        fMesh->InitNormals();
#if (FBXSDK_VERSION_MAJOR >= 2015)
        fMesh->GenerateNormals();
#else
        fMesh->ComputeVertexNormals();
#endif
    }

    // material
    int numMtrl = fNode->GetMaterialCount();
    if (numMtrl > 1)
    {
        // pModel->m_vSubMeshVertexList.resize(iNumMtrl);
        // pModel->m_vSubMeshIndexList.resize(iNumMtrl);
    }

    for (int mtrlIdx = 0; mtrlIdx < numMtrl; mtrlIdx++)
    {
        FbxSurfaceMaterial* pSurfaceMtrl = fNode->GetMaterial(mtrlIdx);
        if (pSurfaceMtrl)
        {
            std::string texPathName;
            auto        Property = pSurfaceMtrl->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (Property.IsValid())
            {
                FbxFileTexture* tex = Property.GetSrcObject<FbxFileTexture>(0);
                if (tex)
                {
                    texPathName = tex->GetFileName();
                }
            }
        }
    }

    // 삼각형 몇개
    // 폴리곤 = 사각형(삼각형2개) or 삼각형
    int numPolyCount = fMesh->GetPolygonCount();
    // 정점의 위치가 저장된 배열의 시작주소를 반환.
    FbxVector4* vertexPosition = fMesh->GetControlPoints();

    subMesh->indices.resize(fMesh->GetPolygonCount() * fMesh->GetPolygonSize(0));
    // 이거 개선 필요할듯 버텍스 개수마냥 인덱스 돌아가네;;

    int basePolyIdx = 0;
    int subMtrlIdx  = 0;
    for (int polyIdx = 0; polyIdx < numPolyCount; polyIdx++)
    {
        int polySize = fMesh->GetPolygonSize(polyIdx);
        int numFace  = polySize - 2;  // 3-2=1, 4-2=2
        for (int face = 0; face < numFace; face++)
        {
            int iVertexIndex[3]               = {0, face + 2, face + 1};
            subMesh->indices[2 + m_vertexIdx] = iVertexIndex[0] + m_vertexIdx;
            subMesh->indices[1 + m_vertexIdx] = iVertexIndex[1] + m_vertexIdx;
            subMesh->indices[0 + m_vertexIdx] = iVertexIndex[2] + m_vertexIdx;
            // 왜 처음에 시계방향으로 되어있었냐...

            int iVertexPositionIndex[3];
            iVertexPositionIndex[0] = fMesh->GetPolygonVertex(polyIdx, iVertexIndex[0]);
            iVertexPositionIndex[1] = fMesh->GetPolygonVertex(polyIdx, iVertexIndex[1]);
            iVertexPositionIndex[2] = fMesh->GetPolygonVertex(polyIdx, iVertexIndex[2]);

            int iVertexUVIndex[3];
            iVertexUVIndex[0] = fMesh->GetTextureUVIndex(polyIdx, iVertexIndex[0]);
            iVertexUVIndex[1] = fMesh->GetTextureUVIndex(polyIdx, iVertexIndex[1]);
            iVertexUVIndex[2] = fMesh->GetTextureUVIndex(polyIdx, iVertexIndex[2]);

            for (int vertexIdx = 0; vertexIdx < 3; vertexIdx++)
            {
                FbxVector4 fbxV       = vertexPosition[iVertexPositionIndex[vertexIdx]];
                FbxColor   color      = FbxColor(1, 1, 1, 1);
                FbxVector4 vFbxNormal = {0, 0, 0};

                fbxV = geoMat.MultT(fbxV);

                mesh->m_vertices[m_vertexIdx].p.x = static_cast<float>(fbxV.mData[0]);
                mesh->m_vertices[m_vertexIdx].p.y = static_cast<float>(fbxV.mData[2]);
                mesh->m_vertices[m_vertexIdx].p.z = static_cast<float>(fbxV.mData[1]);

                if (VertexUVLayer.size() > 0)
                {
                    FbxVector2 uv =
                    GetUV(VertexUVLayer[0], iVertexPositionIndex[vertexIdx], iVertexUVIndex[vertexIdx]);
                    mesh->m_vertices[m_vertexIdx].t.x = static_cast<float>(uv.mData[0]);
                    mesh->m_vertices[m_vertexIdx].t.y = 1.0f - static_cast<float>(uv.mData[1]);
                }

                if (VertexColorLayer.size())
                {
                    color = GetColor(VertexColorLayer[0],
                                     iVertexPositionIndex[vertexIdx],
                                     basePolyIdx + iVertexIndex[vertexIdx]);
                }

                mesh->m_vertices[m_vertexIdx].c.r = static_cast<float>(color.mRed);
                mesh->m_vertices[m_vertexIdx].c.g = static_cast<float>(color.mGreen);
                mesh->m_vertices[m_vertexIdx].c.b = static_cast<float>(color.mBlue);
                mesh->m_vertices[m_vertexIdx].c.a = 1.f;

                if (VertexNormalLayer.size())
                {
                    vFbxNormal = GetNormal(VertexNormalLayer[0],
                                           iVertexPositionIndex[vertexIdx],
                                           basePolyIdx + iVertexIndex[vertexIdx]);
                    vFbxNormal = normalMatrix.MultT(vFbxNormal);
                    vFbxNormal.Normalize();
                }

                mesh->m_vertices[m_vertexIdx].n.x = static_cast<float>(vFbxNormal.mData[0]);
                mesh->m_vertices[m_vertexIdx].n.y = static_cast<float>(vFbxNormal.mData[2]);
                mesh->m_vertices[m_vertexIdx].n.z = static_cast<float>(vFbxNormal.mData[1]);

                m_vertexIdx++;
            }
        }
        basePolyIdx += polySize;
    }

    mesh->m_subMeshes[m_subMeshIdx] = subMesh;
    m_subMeshIdx++;
}

void FbxLoader::InitMesh(std::shared_ptr<Mesh> mesh)
{
    UINT meshVerticesNums = 0;
    m_vertexIdx           = 0;
    m_subMeshIdx          = 0;

    // 버텍스 개수 구해서 하나의 버텍스 버퍼로 합치기 위해 버텍스 수 구함
    for (UINT i = 0; i < m_subMeshes.size(); i++)
        meshVerticesNums += m_subMeshes[i]->GetPolygonVertexCount();

    mesh->m_subMeshes.resize(m_subMeshes.size());
    mesh->m_vertices.resize(meshVerticesNums);
}
