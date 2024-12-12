#pragma once

#include "3D\LineObj.h"
#include "3D\HeightMapObj.h"
#include "Renderable.h"
#include "Camera.h"

namespace HBSoft
{
    struct QNode
    {
        UINT depth;
        bool isLeaf;

        std::unique_ptr<QNode> child[4];

        std::vector<UINT>    indexList;
        ComPtr<ID3D11Buffer> indexBuffer;

        QNode()
        {
            depth    = 0;
            isLeaf   = false;
            child[0] = nullptr;
            child[1] = nullptr;
            child[2] = nullptr;
            child[3] = nullptr;
        }
    };

    class QuadTree : public Renderable
    {
    private:
        std::shared_ptr<HeightMapObj> m_mapObj;
        std::unique_ptr<QNode>        m_rootNode;

        UINT m_maxDepth;

    private:
        // void SubDivide
        // void BuildTree()

    public:
        QuadTree(UINT depth);

        std::shared_ptr<HeightMapObj> GetMapObj();
        std::unique_ptr<QNode> CreateNode(UINT depth, UINT TopLeft, UINT TopRight, UINT BottomLeft,
                                          UINT BottonRight);

        virtual void Init() override;
        virtual void Release() override;
        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
