/*
author : 변한빛
description : 옵저버 패턴을 위한 헤더 파일

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
    // Update는 게임에서 많이 쓰이니 OnNotice로 변경
};
