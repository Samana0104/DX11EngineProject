/*
author : 변한빛
description : 쿼드 트리 소스파일

version: 1.0.1
date: 2024-12-13
*/
#include "pch.h"
#include "QuadTree.h"
using namespace HBSoft;

QuadTree::QuadTree(UINT depth)
    : m_maxDepth(depth)
{}

QuadTree::~QuadTree()
{
    delete m_rootNode;
}

QNode* QuadTree::CreateNode(UINT depth, UINT TopLeft, UINT TopRight, UINT BottomLeft, UINT BottomRight)
{
    QNode* node = new QNode();

    node->depth = depth;

    node->cornerIdx[0] = TopLeft;
    node->cornerIdx[1] = TopRight;
    node->cornerIdx[2] = BottomLeft;
    node->cornerIdx[3] = BottomRight;

    UINT numCol    = TopRight - TopLeft;
    UINT numHeight = m_mapObj->m_mapDesc.numRows;
    UINT numWidth  = m_mapObj->m_mapDesc.numCols;
    UINT numFace   = numCol * ((BottomLeft - TopLeft) / numHeight) * 2;
    UINT numIndex  = numFace * 3;

    node->indexList.resize(numIndex);

    // vb->map,  node->ib

    UINT startRow = TopLeft / numHeight;
    UINT endRow   = BottomLeft / numHeight;
    UINT startCol = TopLeft % numWidth;
    UINT endCol   = TopRight % numWidth;

    UINT index = 0;

    for (UINT row = startRow; row < endRow; row++)
    {
        for (UINT col = startCol; col < endCol; col++)
        {
            UINT nextRow = row + 1;
            UINT nextCol = col + 1;

            node->indexList[index]     = row * numWidth + col;
            node->indexList[index + 1] = row * numWidth + nextCol;
            node->indexList[index + 2] = nextRow * numWidth + nextCol;

            node->indexList[index + 3] = node->indexList[index];
            node->indexList[index + 4] = node->indexList[index + 2];
            node->indexList[index + 5] = nextRow * numWidth + col;

            index += 6;
        }
    }

    assert(HDEVICE->CreateIndexBuffer(node->indexList, node->indexBuffer));

    node->box.aabb.min = {99999.0f, 99999.0f, 99999.0f};
    node->box.aabb.max = {-99999.0f, -99999.0f, -99999.0f};

    for (size_t i = 0; i < node->indexList.size(); i++)
    {
        vec3 v = m_mapObj->m_mesh->m_vertices[node->indexList[i]].p;

        if (v.x > node->box.aabb.max.x)
            node->box.aabb.max.x = v.x;

        if (v.y > node->box.aabb.max.y)
            node->box.aabb.max.y = v.y;

        if (v.z > node->box.aabb.max.z)
            node->box.aabb.max.z = v.z;

        if (v.x < node->box.aabb.min.x)
            node->box.aabb.min.x = v.x;

        if (v.y < node->box.aabb.min.y)
            node->box.aabb.min.y = v.y;

        if (v.z < node->box.aabb.min.z)
            node->box.aabb.min.z = v.z;
    }

    node->box.obb.center      = (node->box.aabb.max + node->box.aabb.min) * 0.5f;
    node->box.obb.axis[0]     = {1.0f, 0.0f, 0.0f};
    node->box.obb.axis[1]     = {0.0f, 1.0f, 0.0f};
    node->box.obb.axis[2]     = {0.0f, 0.0f, 1.0f};
    node->box.obb.distance[0] = (node->box.aabb.max.x - node->box.aabb.min.x) * 0.5f;
    node->box.obb.distance[1] = (node->box.aabb.max.y - node->box.aabb.min.y) * 0.5f;
    node->box.obb.distance[2] = (node->box.aabb.max.z - node->box.aabb.min.z) * 0.5f;

    return node;
}

std::shared_ptr<HeightMapObj> QuadTree::GetMapObj()
{
    return m_mapObj;
}

void QuadTree::BuildTree(QNode* node)
{
    if (SubDivide(node))
    {
        for (int i = 0; i < 4; i++)
            BuildTree(node->child[i]);
    }
}

void QuadTree::FindNode(QNode* node)
{
    if (node == nullptr)
        return;

    if (m_camera->m_frustum.IsFrustumInBox(node->box))
    {
        if (node->isLeaf == true)
            m_renderNode.push_back(node);
    }
    else
    {
        return;
    }

    for (int childIdx = 0; childIdx < 4; childIdx++)
        FindNode(node->child[childIdx]);
}

bool QuadTree::SubDivide(QNode* node)
{
    UINT halfCol = node->cornerIdx[1] - node->cornerIdx[0];
    UINT halfRow = (node->cornerIdx[2] - node->cornerIdx[0]) / m_mapObj->m_mapDesc.numCols;

    if (node->depth < m_maxDepth && halfRow > 1 && halfCol > 1)
    {
        // 0(TL)   1(CT)      2(TR)
        // 3(CL)   4(com)	  5(CR)
        // 6(BL)   7(CB)      8(BR)
        UINT topLeft      = node->cornerIdx[0];
        UINT topRight     = node->cornerIdx[1];
        UINT bottomLeft   = node->cornerIdx[2];
        UINT bottomRight  = node->cornerIdx[3];
        UINT com          = (topLeft + bottomRight) / 2;
        UINT centerTop    = (topRight + topLeft) / 2;
        UINT centerRight  = (topRight + bottomRight) / 2;
        UINT centerBottom = (bottomLeft + bottomRight) / 2;
        UINT centerLeft   = (topLeft + bottomLeft) / 2;

        node->child[0] = CreateNode(node->depth + 1, topLeft, centerTop, centerLeft, com);
        node->child[1] = CreateNode(node->depth + 1, centerTop, topRight, com, centerRight);
        node->child[2] = CreateNode(node->depth + 1, centerLeft, com, bottomLeft, centerBottom);
        node->child[3] = CreateNode(node->depth + 1, com, centerRight, centerBottom, bottomRight);
        return true;
    }
    else
    {
        node->isLeaf = true;
        return false;
    }
}

void QuadTree::SetMapObj(std::shared_ptr<HeightMapObj> heightMapObj)
{
    m_mapObj   = heightMapObj;
    m_rootNode = CreateNode(0,
                            0,
                            m_mapObj->m_mapDesc.numCols - 1,
                            (m_mapObj->m_mapDesc.numRows - 1) * m_mapObj->m_mapDesc.numCols,
                            m_mapObj->m_mapDesc.numRows * m_mapObj->m_mapDesc.numCols - 1);
    BuildTree(m_rootNode);
}

void QuadTree::SetCamera(std::shared_ptr<Camera> camera)
{
    m_camera = camera;
}

std::shared_ptr<HeightMapObj> QuadTree::GetHeightMapObj()
{
    return m_mapObj;
}

void QuadTree::Init() {}

void QuadTree::Release() {}

void QuadTree::Update(const float deltaTime)
{
    m_mapObj->Update(deltaTime);
    m_renderNode.clear();
    FindNode(m_rootNode);
}

void QuadTree::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    m_mapObj->m_easyRender.SetEntireState();
    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼

    HDEVICE->m_context->PSSetShaderResources(0, 1, m_mapObj->m_mapTexture->GetSRV().GetAddressOf());
    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mapObj->m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
    HDEVICE->m_context->PSSetConstantBuffers(
    1,
    1,
    m_mapObj->m_mesh->m_subMeshes[0]->materialBuffer.GetAddressOf());

    for (size_t i = 0; i < m_renderNode.size(); i++)
    {
        HDEVICE->m_context->IASetIndexBuffer(m_renderNode[i]->indexBuffer.Get(),
                                             DXGI_FORMAT_R32_UINT,
                                             0);
        HDEVICE->m_context->DrawIndexed((UINT)m_renderNode[i]->indexList.size(), 0, 0);
    }
    // m_mapObj->m_easyRender.SetNormalState();
    // HDEVICE->m_context->DrawIndexed((UINT)m_rootNode->indexList.size(), 0, 0);
}
