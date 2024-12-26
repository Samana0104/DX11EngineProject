/*
author : 변한빛
description : 쿼드트리 헤더파일

version: 1.0.1
date: 2024-12-13
*/
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
        UINT cornerIdx[4];

        QNode* child[4];

        std::vector<UINT>    indexList;
        ComPtr<ID3D11Buffer> indexBuffer;

        bool isLeaf;

        QNode()
        {
            depth    = 0;
            isLeaf   = false;
            child[0] = nullptr;
            child[1] = nullptr;
            child[2] = nullptr;
            child[3] = nullptr;
        }

        ~QNode()
        {
            for (int i = 0; i < 4; i++)
            {
                if (child[i] != nullptr)
                    delete child[i];
            }
        }
    };

    class QuadTree : public Renderable
    {
    private:
        std::shared_ptr<HeightMapObj> m_mapObj;

        QNode* m_rootNode;
        UINT   m_maxDepth;

    private:
        QNode* MakeRoot();

    public:
        QuadTree(UINT depth);
        ~QuadTree();

        std::shared_ptr<HeightMapObj> GetMapObj();
        QNode* CreateNode(UINT depth, UINT TopLeft, UINT TopRight, UINT BottomLeft, UINT BottomRight);

        void BuildTree(QNode* node);
        bool SubDivide(QNode* node);
        void SetHeightMapObj(std::shared_ptr<HeightMapObj> heightMapObj);

        std::shared_ptr<HeightMapObj> GetHeightMapObj();

        virtual void Init() override;
        virtual void Release() override;
        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
