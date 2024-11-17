/*
author : ���Ѻ�
description : ������ ������ ���� ��� ����

version: 1.0.4
date: 2024-11-15
*/

#pragma once

namespace HBSoft
{
    enum class EventList : uint16_t
    {
        WINDOW_RESIZE = 1,  // ������ �������� �̺�Ʈ entity�� nullptr�Ѿ
        DEVICE_CHANGE = 2,  // ����̽� ���õ� �� ����� �߰��� �� entity�� ����̽� �Ѿ
    };

    class Observer
    {
    protected:
        Observer()  = default;
        ~Observer() = default;

    public:
        virtual void OnNotice(EventList event, void* entity) = 0;
        // Update�� ���ӿ��� ���� ���̴� OnNotice�� ����
    };
}  // namespace HBSoft
