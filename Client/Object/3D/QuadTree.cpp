#include "pch.h"
#include "QuadTree.h"
using namespace HBSoft;

QuadTree::QuadTree(UINT depth)
    : m_maxDepth(depth)
{
    m_mapObj   = std::make_shared<HeightMapObj>();
    m_rootNode = std::move(CreateNode(0, ))
}

std::shared_ptr<HeightMapObj> QuadTree::GetMapObj()
{
    return m_mapObj;
}

std::unique_ptr<QNode> QuadTree::CreateNode(UINT depth, UINT TopLeft, UINT TopRight, UINT BottomLeft,
                                            UINT BottonRight)
{
    std::unique_ptr<QNode> node = std::make_unique<QNode>();
    node->depth =

    node->indexList[0] = TopLeft;


    return std::shared_ptr<QNode>();
}

void QuadTree::Init() {}

void QuadTree::Release() {}

void QuadTree::Update(const float deltaTime) {}

void QuadTree::Render() {}
