/*
author : ���Ѻ�
description : ���� ���� ������� ���������� �����Ӱ� ���� �����ϴ�

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "SystemTimer.h"
#include "SceneMgr.h"
#include "AssetsMgr.h"
#include "Input.h"

#define HENGINE HBSoft::Core::engine
#define HWINDOW HBSoft::Core::engine->m_window
#define HDEVICE HBSoft::Core::engine->m_device
#define HINPUT  HBSoft::Core::engine->m_input
#define HASSET  HBSoft::Core::engine->m_assets
#define HTIMER  HBSoft::Core::engine->m_timer

namespace HBSoft
{
    class Core
    {
    private:
        bool m_isRunning = false;

    public:
        inline static std::unique_ptr<Core> engine = nullptr;

        SceneMgr    m_sceneMgr;
        SystemTimer m_timer;

        std::unique_ptr<AssetsMgr> m_assets;
        std::unique_ptr<Input>     m_input;
        std::shared_ptr<D3Device>  m_device;
        std::shared_ptr<Window>    m_window;

    private:
        Core(Core&&)                 = delete;
        Core& operator=(const Core&) = delete;
        Core& operator=(Core&&)      = delete;

    protected:
        void Update();
        void Render();
        void Release();

    public:
        Core(HINSTANCE hInstance, HPoint windowSize);
        // ���� ���� �����ڰ� �ۺ��̶�� �ؼ� �ھ� �� ������ �ʰ���??
        // �Ϲ� �����ʹ� �ʹ� �Ҿ��ؼ� �ϴ� ����Ʈ �����ͷ� �ھ� ����
        ~Core() = default;

        void Run();

        static void Create(HINSTANCE hInstance, HPoint windowSize);
        // ���� ���� Ȯ���ϰ� �ϱ� ����Ʈ�����ͷ� �����ϰ� ����
        static void Delete();
    };
}  // namespace HBSoft
