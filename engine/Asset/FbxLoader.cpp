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

std::shared_ptr<Mesh> FbxLoader::Load(std::shared_ptr<D3Device> device, const wstringV filePath)
{
    FbxNode*              fbxRootNode = nullptr;
    std::vector<FbxMesh*> meshSet;

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

    if (!InitFbxLoader(filePath))
        return nullptr;

    FbxAxisSystem::MayaZUp.ConvertScene(m_fbxScene);
    fbxRootNode = m_fbxScene->GetRootNode();

    ProcessNode(fbxRootNode, mesh, 0, -1);
    InitMesh(mesh);

    LoadAnimation(mesh);

    for (size_t i = 0; i < m_fbxMeshes.size(); i++)
        ProcessMesh(m_fbxMeshes[i], mesh);

    ReleaseFbxManager();

    for ()
        device->CreateVertexBuffer(mesh->m_vertices, mesh->m_vertexBuffer);

    for (UINT i = 0; i < mesh->m_subMeshes.size(); i++)
        device->CreateIndexBuffer(mesh->m_subMeshes[i]->indices, mesh->m_subMeshes[i]->indexBuffer);

    return mesh;
}

bool FbxLoader::InitFbxLoader(const wstringV filePath)
{
    if (m_fbxManager == nullptr)
    {
        m_fbxManager              = FbxManager::Create();
        FbxIOSettings* ioSettings = FbxIOSettings::Create(m_fbxManager, IOSROOT);
        m_fbxManager->SetIOSettings(ioSettings);
    }

    if (m_fbxImporter == nullptr)
        m_fbxImporter = FbxImporter::Create(m_fbxManager, "");

    if (m_fbxScene == nullptr)
        m_fbxScene = FbxScene::Create(m_fbxManager, "");

    std::string sPath = HBSoft::ToMultiByte(filePath);

    if (!m_fbxImporter->Initialize(sPath.c_str()))
    {
        MessageBoxA(NULL, m_fbxImporter->GetStatus().GetErrorString(), "import error", MB_OK);
        return false;
    }

    if (!m_fbxImporter->Import(m_fbxScene))
    {
        MessageBoxA(NULL, m_fbxImporter->GetStatus().GetErrorString(), "import error", MB_OK);
        return false;
    }

    m_fbxNodes.clear();
    m_fbxBornNodes.clear();
    m_fbxMeshes.clear();

    return true;
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

void FbxLoader::ProcessNode(FbxNode* fNode, std::shared_ptr<Mesh> mesh, int curIdx, int parentIdx)
{
    if (fNode == nullptr)
        return;

    FbxMesh*    fMesh    = fNode->GetMesh();
    std::string nodeName = fNode->GetName();

    if (fMesh != nullptr)
        m_fbxMeshes.push_back(fMesh);


    if (fNode->GetSkeleton() != nullptr)
    {
        if (!mesh->m_born.bornIndex.contains(nodeName))
        {
            mesh->m_born.bornIndex[nodeName]   = curIdx;
            mesh->m_born.parentIndex[nodeName] = parentIdx;
            m_fbxBornNodes.push_back(fNode);
        }
    }

    if (!mesh->m_born.objectIndex.contains(nodeName))
    {
        mesh->m_born.objectIndex[nodeName] = curIdx;
        mesh->m_born.parentIndex[nodeName] = parentIdx;
        m_fbxNodes.push_back(fNode);
    }


    int numChild = fNode->GetChildCount();
    for (int childIdx = 0; childIdx < numChild; childIdx++)
        ProcessNode(fNode->GetChild(childIdx), mesh, (int)(mesh->m_born.objectIndex.size()), curIdx);
}

bool FbxLoader::ProcessBorn(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh)
{
    FbxCluster* fCluster;
    FbxSkin*    fSkin;
    FbxNode*    clusterNode;
    FbxAMatrix  globalInitPosMat;
    FbxAMatrix  bindPoseMat;
    FbxAMatrix  offsetMat;

    int     deformerCount;
    int     clusterCount;
    int     clusterSize;
    int*    fbxNodeIdices;
    double* weightList;
    UINT    boneIdx;


    deformerCount = fMesh->GetDeformerCount(FbxDeformer::eSkin);

    if (deformerCount <= 0)
        return false;

    m_skinningData.clear();
    m_skinningData.resize(fMesh->GetControlPointsCount());

    for (int deformerIdx = 0; deformerIdx < deformerCount; deformerIdx++)
    {
        fSkin = reinterpret_cast<FbxSkin*>(fMesh->GetDeformer(deformerIdx, FbxDeformer::eSkin));

        clusterCount = fSkin->GetClusterCount();

        for (int clusterIdx = 0; clusterIdx < clusterCount; clusterIdx++)
        {
            fCluster         = fSkin->GetCluster(clusterIdx);
            clusterNode      = fCluster->GetLink();
            std::string name = clusterNode->GetName();
            boneIdx          = mesh->m_born.bornIndex[name];

            fCluster->GetTransformLinkMatrix(bindPoseMat);
            fCluster->GetTransformMatrix(globalInitPosMat);

            offsetMat = bindPoseMat.Inverse() * globalInitPosMat;

            for (size_t i = 0; i < mesh->m_animations.size(); i++)
            {
                for (size_t j = 0; j < mesh->m_animations[i]->m_aniMat[boneIdx].size(); j++)
                {
                    mesh->m_animations[i]->m_aniMat[boneIdx][j] *= ConvertFbxMatToGlmMat(offsetMat);
                }
            }

            clusterSize   = fCluster->GetControlPointIndicesCount();
            fbxNodeIdices = fCluster->GetControlPointIndices();
            weightList    = fCluster->GetControlPointWeights();

            for (int v = 0; v < clusterSize; v++)
            {
                int   vertexIdx = fbxNodeIdices[v];
                float weight    = static_cast<float>(weightList[v]);
                m_skinningData[vertexIdx].weights.push_back(weight);
                m_skinningData[vertexIdx].boneIdx.push_back(boneIdx);
            }
        }
    }

    return true;
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
        case FbxLayerElementUV::eDirect:
        case FbxLayerElementUV::eIndexToDirect:
            ret = uvSet->GetDirectArray().GetAt(vertexUVIdx);
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

void FbxLoader::LoadAnimation(std::shared_ptr<Mesh> mesh)
{
    FbxAnimStack*        aniStack;
    FbxString            TakeName;
    FbxTakeInfo*         TakeInfo;
    FbxTime              startTime, endTime;
    FbxTime::EMode       timeMode;
    int                  startFrame, lastFrame;
    FbxArray<FbxString*> animStackNameArray;
    FbxAMatrix           localMat, rootMat, matWorld;

    std::vector<FbxTime>           animationTimes;
    std::shared_ptr<AnimationClip> clip;

    m_fbxScene->FillAnimStackNameArray(animStackNameArray);
    int stackCount = animStackNameArray.GetCount();

    if (stackCount <= 0)
        return;

    for (int i = 0; i < 2; i++)
    {
        aniStack = m_fbxScene->FindMember<FbxAnimStack>(animStackNameArray[i]->Buffer());
        m_fbxScene->SetCurrentAnimationStack(aniStack);

        if (aniStack == nullptr)
            break;

        TakeName = aniStack->GetName();
        TakeInfo = m_fbxScene->GetTakeInfo(TakeName);

        if (TakeInfo == nullptr)
            continue;

        clip            = std::make_shared<AnimationClip>();
        clip->m_aniName = TakeName.Buffer();

        for (int nodeIdx = 0; nodeIdx < m_fbxNodes.size(); nodeIdx++)
        {
            std::string name = m_fbxNodes[nodeIdx]->GetName();

            UINT boneIdx = mesh->m_born.objectIndex[name];

            startTime = TakeInfo->mLocalTimeSpan.GetStart();
            endTime   = TakeInfo->mLocalTimeSpan.GetStop();

            FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);

            timeMode   = FbxTime::GetGlobalTimeMode();
            startFrame = static_cast<int>(startTime.GetFrameCount(timeMode));
            lastFrame  = static_cast<int>(endTime.GetFrameCount(timeMode)) - startFrame;


            animationTimes.resize(lastFrame);
            for (int frame = 0; frame < lastFrame; frame++)
                animationTimes[frame].SetFrame(frame, timeMode);

            clip->m_aniMat.resize(m_fbxNodes.size());
            clip->m_aniName    = TakeName.Buffer();
            clip->m_startFrame = 0;
            clip->m_lastFrame  = lastFrame;
            clip->m_aniMat[boneIdx].resize(lastFrame);

            if (mesh->m_born.bornIndex.contains(name))
            {
                for (int frame = 0; frame < lastFrame; frame++)
                {
                    localMat      = m_fbxNodes[boneIdx]->EvaluateGlobalTransform(animationTimes[frame]);
                    rootMat       = m_fbxBornNodes[0]->EvaluateGlobalTransform(animationTimes[frame]);
                    matWorld      = rootMat.Inverse() * localMat;
                    mat4 matFrame = ConvertFbxMatToGlmMat(matWorld);

                    clip->m_aniMat[boneIdx][frame] = matFrame;
                }
            }
            else
            {
                for (int frame = 0; frame < lastFrame; frame++)
                {
                    localMat      = m_fbxNodes[boneIdx]->EvaluateGlobalTransform(animationTimes[frame]);
                    rootMat       = m_fbxNodes[boneIdx]->EvaluateGlobalTransform(animationTimes[0]);
                    matWorld      = rootMat.Inverse() * localMat;
                    mat4 matFrame = ConvertFbxMatToGlmMat(matWorld);

                    clip->m_aniMat[boneIdx][frame] = matFrame;
                }
            }
        }
        mesh->m_animations.push_back(clip);
    }
}

void FbxLoader::ProcessMesh(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh)
{
    FbxAMatrix geoMat;

    FbxNode*   fNode = fMesh->GetNode();
    FbxVector4 trans = fNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rot   = fNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = fNode->GetGeometricScaling(FbxNode::eSourcePivot);

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    bool isSkinned;

    subMesh->meshName = fMesh->GetName();
    isSkinned         = ProcessBorn(fMesh, mesh);

    geoMat.SetT(trans);
    geoMat.SetR(rot);
    geoMat.SetS(scale);
    // 노말 변환 행렬
    FbxAMatrix normalMatrix = geoMat;
    normalMatrix            = normalMatrix.Inverse();
    normalMatrix            = normalMatrix.Transpose();

    // Layer :  레이어 회수만큼 랜더링한다.
    std::vector<FbxLayerElementUV*>          vertexUVLayer;
    std::vector<FbxLayerElementVertexColor*> vertexColorLayer;
    std::vector<FbxLayerElementNormal*>      vertexNormalLayer;
    std::vector<FbxLayerElementTangent*>     vertexTangentLayer;
    std::vector<FbxLayerElementMaterial*>    vertexMaterialLayer;

    int layerCount = fMesh->GetLayerCount();

    for (int layer = 0; layer < layerCount; layer++)
    {
        FbxLayer* fbxLayer = fMesh->GetLayer(layer);

        if (fbxLayer->GetUVs())
            vertexUVLayer.emplace_back(fbxLayer->GetUVs());

        if (fbxLayer->GetVertexColors())
            vertexColorLayer.emplace_back(fbxLayer->GetVertexColors());

        if (fbxLayer->GetTangents())
            vertexTangentLayer.emplace_back(fbxLayer->GetTangents());

        if (fbxLayer->GetNormals())
            vertexNormalLayer.emplace_back(fbxLayer->GetNormals());

        if (fbxLayer->GetMaterials())
            vertexMaterialLayer.emplace_back(fbxLayer->GetMaterials());
    }

    // 정점노말 (재)계산
    if (vertexNormalLayer.size() > 0)
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

    for (int mtrlIdx = 0; mtrlIdx < numMtrl; mtrlIdx++)
    {
        FbxSurfaceMaterial* pSurfaceMtrl = fNode->GetMaterial(mtrlIdx);
        if (pSurfaceMtrl)
        {
            auto Property = pSurfaceMtrl->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (Property.IsValid())
            {
                FbxFileTexture* tex = Property.GetSrcObject<FbxFileTexture>(0);

                if (tex)
                {
                    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(ToUnicode(tex->GetFileName()));

                    subMesh->hasTexture  = true;
                    subMesh->textureName = fileName + fileExt;
                }
                else
                {
                    subMesh->hasTexture = false;
                }
            }
        }
    }

    // 삼각형 몇개
    // 폴리곤 = 사각형(삼각형2개) or 삼각형
    int numPolyCount = fMesh->GetPolygonCount();
    // 정점의 위치가 저장된 배열의 시작주소를 반환.
    FbxVector4* vertexPosition = fMesh->GetControlPoints();

    int numIndices = 0;

    for (int i = 0; i < fMesh->GetPolygonCount(); i++)
        numIndices += (fMesh->GetPolygonSize(i) - 2) * 3;

    subMesh->indices.resize(numIndices);

    int basePolyIdx = 0;
    int baseIndex   = 0;

    for (int polyIdx = 0; polyIdx < numPolyCount; polyIdx++)
    {
        int polySize = fMesh->GetPolygonSize(polyIdx);
        int numFace  = polySize - 2;  // 3-2=1, 4-2=2
        for (int face = 0; face < numFace; face++)
        {
            int iVertexIndex[3] = {0, face + 2, face + 1};

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

                if (vertexUVLayer.size() > 0)
                {
                    FbxVector2 uv =
                    GetUV(vertexUVLayer[0], iVertexPositionIndex[vertexIdx], iVertexUVIndex[vertexIdx]);
                    mesh->m_vertices[m_vertexIdx].t.x = static_cast<float>(uv.mData[0]);
                    mesh->m_vertices[m_vertexIdx].t.y = 1.f - static_cast<float>(uv.mData[1]);
                }

                if (vertexColorLayer.size())
                {
                    color = GetColor(vertexColorLayer[0],
                                     iVertexPositionIndex[vertexIdx],
                                     basePolyIdx + iVertexIndex[vertexIdx]);
                }

                mesh->m_vertices[m_vertexIdx].c.r = static_cast<float>(color.mRed);
                mesh->m_vertices[m_vertexIdx].c.g = static_cast<float>(color.mGreen);
                mesh->m_vertices[m_vertexIdx].c.b = static_cast<float>(color.mBlue);
                mesh->m_vertices[m_vertexIdx].c.a = static_cast<float>(color.mAlpha);

                if (vertexNormalLayer.size())
                {
                    vFbxNormal = GetNormal(vertexNormalLayer[0],
                                           iVertexPositionIndex[vertexIdx],
                                           basePolyIdx + iVertexIndex[vertexIdx]);
                    vFbxNormal = normalMatrix.MultT(vFbxNormal);
                    vFbxNormal.Normalize();
                }

                mesh->m_vertices[m_vertexIdx].n.x = static_cast<float>(vFbxNormal.mData[0]);
                mesh->m_vertices[m_vertexIdx].n.y = static_cast<float>(vFbxNormal.mData[2]);
                mesh->m_vertices[m_vertexIdx].n.z = static_cast<float>(vFbxNormal.mData[1]);


                if (isSkinned)
                {
                    size_t iwSize = m_skinningData[iVertexPositionIndex[vertexIdx]].boneIdx.size();
                    for (size_t iwIdx = 0; iwIdx < iwSize; iwIdx++)
                    {
                        mesh->m_vertices[m_vertexIdx].i[iwIdx] =
                        m_skinningData[iVertexPositionIndex[vertexIdx]].boneIdx[iwIdx];

                        mesh->m_vertices[m_vertexIdx].w[iwIdx] =
                        m_skinningData[iVertexPositionIndex[vertexIdx]].weights[iwIdx];
                    }
                }
                else
                {
                    mesh->m_vertices[m_vertexIdx].i[0] = mesh->m_born.objectIndex[fNode->GetName()];
                    mesh->m_vertices[m_vertexIdx].w[0] = 1.f;
                }

                subMesh->indices[baseIndex] = m_vertexIdx;

                baseIndex++;
                m_vertexIdx++;
            }
        }
        basePolyIdx += polySize;
    }

    mesh->m_subMeshes.push_back(subMesh);
}

void FbxLoader::InitMesh(std::shared_ptr<Mesh> mesh)
{
    int meshVerticesNums = 0;
    int polyCount        = 0;

    // 버텍스 개수 구해서 하나의 버텍스 버퍼로 합치기 위해 버텍스 수 구함
    for (int i = 0; i < m_fbxMeshes.size(); i++)
    {
        polyCount = m_fbxMeshes[i]->GetPolygonCount();

        for (int j = 0; j < polyCount; j++)
            meshVerticesNums += (m_fbxMeshes[i]->GetPolygonSize(j) - 2) * 3;
    }

    mesh->m_vertices.resize(meshVerticesNums);
    m_vertexIdx = 0;
}

mat4 FbxLoader::ConvertFbxMatToGlmMat(FbxAMatrix& fMat)
{
    mat4 glmMat;
    mat4 copyGlmMat;

    double* a = reinterpret_cast<double*>(&fMat);

    for (UINT i = 0; i < 4; i++)
    {
        for (UINT j = 0; j < 4; j++)
            glmMat[i][j] = static_cast<float>(fMat.Get(i, j));
    }

    copyGlmMat = glmMat;

    glmMat[1] = copyGlmMat[2];
    glmMat[2] = copyGlmMat[1];

    glmMat[0][1] = copyGlmMat[0][2];
    glmMat[1][1] = copyGlmMat[2][2];
    glmMat[2][1] = copyGlmMat[1][2];
    glmMat[3][1] = copyGlmMat[3][2];

    glmMat[0][2] = copyGlmMat[0][1];
    glmMat[1][2] = copyGlmMat[2][1];
    glmMat[2][2] = copyGlmMat[1][1];
    glmMat[3][2] = copyGlmMat[3][1];


    return glmMat;
}
