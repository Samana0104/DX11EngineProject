/*
author : ���Ѻ�
description : ������ ������ ���� ��� ����

version: 1.0.4
date: 2024-11-15
*/

#pragma once

class Observer
{
protected:
    Observer()  = default;
    ~Observer() = default;

public:
    virtual void OnNotice(void* entity) = 0;
    // Update�� ���ӿ��� ���� ���̴� OnNotice�� ����
};
