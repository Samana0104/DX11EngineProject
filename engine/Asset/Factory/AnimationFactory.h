/*
author : ���Ѻ�
description : �ܺ� �ִϸ��̼��� �����ϴ� �������

version: 1.0.0
date: 2024-12-23
*/
#pragma once

#include "pch.h"
#include "SkmLoader.h"

namespace HBSoft
{
    class AnimationFactory
    {
    public:
        static std::shared_ptr<AnimationClip> Create(const wstringV path);

        static bool IsAnimationFormat(const wstringV ext);
    };
}  // namespace HBSoft
