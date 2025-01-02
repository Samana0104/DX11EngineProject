/*
author : 변한빛
description : collision 오브젝트 표기용 헤더파일

version: 1.0.0
date: 2025-01-02
*/

#pragma once

#include "3D/Object3D.h"
#include "CollisionComponent.h"

namespace HBSoft
{
    class CollisionObj : public Object3D
    {
    private:
        std::map<std::string, AABB> m_colIdList;

        std::ofstream m_outputFile;
        std::ifstream m_inputFile;

    public:
        CollisionObj() = default;
        ~CollisionObj();

        void SaveRange(const stringV filePath);
        void LoadRange(const stringV filePath);

        virtual void Init() override;
        virtual void Release() override;
        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
    };

}  // namespace HBSoft
