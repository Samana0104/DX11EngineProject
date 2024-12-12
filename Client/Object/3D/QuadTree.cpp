#include "pch.h"
#include "QuadTree.h"
using namespace HBSoft;

QuadTree::QuadTree(UINT depth)
    : m_maxDepth(depth)
{
    m_mapObj   = std::make_shared<HeightMapObj>();
    m_rootNode = std::move(CreateNode(0,
                                      0,
                                      m_mapObj->m_mapDesc.numCols,
                                      (m_mapObj->m_mapDesc.numRows - 1) * m_mapObj->m_mapDesc.numCols,
                                      m_mapObj->m_mapDesc.numRows * (m_mapObj->m_mapDesc.numCols - 1)));
}

std::shared_ptr<HeightMapObj> QuadTree::GetMapObj()
{
    return m_mapObj;
}

std::unique_ptr<QNode> QuadTree::CreateNode(UINT depth, UINT TopLeft, UINT TopRight, UINT BottomLeft,
                                            UINT BottomRight)
{
    std::unique_ptr<QNode> node = std::make_unique<QNode>();

    node->depth = depth;

    node->cornerIdx[0] = TopLeft;
    node->cornerIdx[1] = TopRight;
    node->cornerIdx[2] = BottomLeft;
    node->cornerIdx[3] = BottomRight;

    /*
    0  1  2  3  4
    5  6  7  8  9
    10 11 12 13 14
    15 16 17 18 19
    20 21 22 23 24
    */

    UINT numCol    = TopRight - TopLeft;
    UINT numHeight = m_mapObj->m_mapDesc.numRows;

    node->indexList.resize(6);

    // 노션 순서대로
    node->indexList[0] = TopLeft;
    node->indexList[1] = TopRight;
    node->indexList[2] = BottomRight;
    node->indexList[3] = TopLeft;
    node->indexList[4] = TopRight;
    node->indexList[5] = BottomLeft;

    assert(HDEVICE->CreateIndexBuffer(node->indexList, node->indexBuffer));

    return std::move(node);
}

void QuadTree::Init() {}

void QuadTree::Release() {}

void QuadTree::Update(const float deltaTime) {}

void QuadTree::Render() {}
