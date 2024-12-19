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
{
    m_mapObj   = std::make_shared<HeightMapObj>();
    m_rootNode = MakeRoot();
    BuildTree(m_rootNode);
}

QuadTree::~QuadTree()
{
    delete m_rootNode;
}

QNode* QuadTree::MakeRoot()
{
    QNode* node = new QNode();

    node->depth = 0;

    /*
    0 1
    2 3
    코너 기준
    */
    node->cornerIdx[0] = 0;
    node->cornerIdx[1] = m_mapObj->m_mapDesc.numCols;
    node->cornerIdx[2] = (m_mapObj->m_mapDesc.numRows - 1) * m_mapObj->m_mapDesc.numCols;
    node->cornerIdx[3] = m_mapObj->m_mapDesc.numRows * m_mapObj->m_mapDesc.numCols - 1;

    // 인덱스 버퍼 강탈
    node->indexList   = std::move(m_mapObj->m_mesh->m_subMeshes[0]->indices);
    node->indexBuffer = m_mapObj->m_mesh->m_subMeshes[0]->indexBuffer;

    return node;
}

QNode* QuadTree::CreateNode(UINT depth, UINT TopLeft, UINT TopRight, UINT BottomLeft, UINT BottomRight)
{
    QNode* node = new QNode();

    node->depth = depth;

    node->cornerIdx[0] = TopLeft;
    node->cornerIdx[1] = TopRight;
    node->cornerIdx[2] = BottomLeft;
    node->cornerIdx[3] = BottomRight;

    /*
    0  1  2  3  4  5
    6  7  8  9  10 11
    12 13 14 15 16 17
    18 19 20 21 22 23
    24 25 26 27 28 29
    */

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

void QuadTree::SetCamera(std::shared_ptr<Camera> camera)
{
    m_mapObj->SetCamera(camera);
}

void QuadTree::Init() {}

void QuadTree::Release() {}

void QuadTree::Update(const float deltaTime)
{
    m_mapObj->Update(deltaTime);
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

    HDEVICE->m_context->IASetIndexBuffer(m_rootNode->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    HDEVICE->m_context->DrawIndexed((UINT)m_rootNode->indexList.size(), 0, 0);
    // m_mapObj->m_easyRender.SetNormalState();
    // HDEVICE->m_context->DrawIndexed((UINT)m_rootNode->indexList.size(), 0, 0);
}
