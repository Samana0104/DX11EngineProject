#include "pch.h"
#include "CollisionObj.h"
using namespace HBSoft;

CollisionObj::~CollisionObj()
{
    if (m_outputFile.is_open())
        m_outputFile.close();

    if (m_inputFile.is_open())
        m_inputFile.close();
}

void CollisionObj::SaveRange(const stringV filePath)
{
    size_t count = 0;

    if (m_outputFile.is_open())
        m_outputFile.close();

    m_outputFile.open(filePath.data(), std::ios::out);
    if (!m_outputFile.is_open())
    {
        MessageBoxA(nullptr, "It can't load the collision txt", "load error", MB_OK);
        return;
    }

    for (auto iter = m_colIdList.begin(); iter != m_colIdList.end(); ++iter)
    {
        m_outputFile << iter->first << std::endl;
        m_outputFile << iter->second.min.x << " " << iter->second.min.y << " " << iter->second.min.z
                     << " " << iter->second.max.x << " " << iter->second.max.y << " "
                     << iter->second.max.z;

        if (count < m_colIdList.size() - 1)  // 마지막 개행 지우려함
            m_outputFile << std::endl;

        count++;
    }

    m_outputFile.close();
}

void CollisionObj::LoadRange(const stringV filePath)
{
    std::string objId;
    AABB        aabbCol;

    if (m_inputFile.is_open())
        m_inputFile.close();

    m_inputFile.open(filePath.data(), std::ios::in);

    if (!m_inputFile.is_open())
    {
        MessageBoxA(nullptr, "It can't load the collision txt", "load error", MB_OK);
        return;
    }

    while (!m_inputFile.eof())
    {
        m_inputFile >> objId;

        m_inputFile >> aabbCol.min.x >> aabbCol.min.y >> aabbCol.min.z >> aabbCol.max.x >>
        aabbCol.max.y >> aabbCol.max.z;

        m_colIdList[objId] = aabbCol;
        m_component.AddAABBRange(aabbCol);
    }

    m_inputFile.close();
}

void CollisionObj::Init() {}

void CollisionObj::Release() {}

void CollisionObj::Update(const float deltaTime)
{
    static int   item_current = 0;
    static AABB  aabbTarget;
    static float imguiMinVec3[3];
    static float imguiMaxVec3[3];

    const char* items[100];
    int         idx = 0;

    for (auto& item : m_colIdList)
        items[idx++] = item.first.c_str();

    if (m_colIdList.size() > 0)
    {
        ImGui::ListBox("listbox", &item_current, items, idx, 4);
    }

    if (item_current < (int)m_colIdList.size() && item_current >= 0)
    {
        aabbTarget = m_colIdList[items[item_current]];

        for (int i = 0; i < 3; i++)
        {
            imguiMinVec3[i] = aabbTarget.min[i];
            imguiMaxVec3[i] = aabbTarget.max[i];
        }
        ImGui::InputFloat3("AABB Min", imguiMinVec3);
        ImGui::InputFloat3("AABB Max", imguiMaxVec3);
    }
}

void CollisionObj::Render() {}
